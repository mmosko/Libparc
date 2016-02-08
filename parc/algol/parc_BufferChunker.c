/*
 * Copyright (c) 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Patent rights are not granted under this agreement. Patent rights are
 *       available under FRAND terms.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @author Christopher Wood, Palo Alto Research Center (Xerox PARC)
 * @copyright 2015-2016, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#include <config.h>

#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <parc/algol/parc_Object.h>
#include <parc/algol/parc_Buffer.h>
#include <parc/algol/parc_Memory.h>

#include <parc/algol/parc_BufferChunker.h>

PARCChunkerInterface *PARCBufferChunkerAsBunker = &(PARCChunkerInterface) {
    .ForwardIterator = (void *(*)(const void *))parcBufferChunker_ForwardIterator,
    .ReverseIterator = (void *(*)(const void *))parcBufferChunker_ReverseIterator,
    .Release = (void (*)(void **))parcBufferChunker_Release
};

struct _parc_chunker_state {
    size_t chunkNumber;
    int direction;
    bool atEnd;
    size_t position;
    size_t nextChunkSize;
};

typedef struct _parc_chunker_state _ChunkerState;

struct parc_buffer_chunker {
    // State
    size_t chunkSize;

    // Container for the data to be parsed
    PARCBuffer *data;

    // The current element of the iterator
    PARCBuffer *currentElement;
};

static void
_destroy(PARCBufferChunker **chunkerP)
{
    if ((*chunkerP)->data != NULL) {
        parcBuffer_Release(&(*chunkerP)->data);
    }

    if ((*chunkerP)->currentElement != NULL) {
        parcBuffer_Release(&(*chunkerP)->currentElement);
    }
}

static void *
_InitForward(PARCBufferChunker *chunker)
{
    _ChunkerState *state = parcMemory_Allocate(sizeof(_ChunkerState));

    state->chunkNumber = 0;
    state->direction = 0;
    state->position = 0;
    state->atEnd = false;

    if (parcBuffer_Remaining(chunker->data) < chunker->chunkSize) {
        state->nextChunkSize = parcBuffer_Remaining(chunker->data);
    } else {
        state->nextChunkSize = chunker->chunkSize;
    }

    return state;
}

static void *
_InitReverse(PARCBufferChunker *chunker)
{
    _ChunkerState *state = parcMemory_Allocate(sizeof(_ChunkerState));

    state->chunkNumber = 0;
    state->direction = 1;
    state->atEnd = false;

    if (parcBuffer_Remaining(chunker->data) < chunker->chunkSize) {
        state->position = 0;
        state->nextChunkSize = parcBuffer_Remaining(chunker->data);
    } else {
        state->position = parcBuffer_Remaining(chunker->data) - chunker->chunkSize;
        state->nextChunkSize = chunker->chunkSize;
    }

    return state;
}

static bool
_ccnxChunker_HasNext(PARCBufferChunker *chunker, void *voidstate)
{
    _ChunkerState *state = (_ChunkerState *) voidstate;
    return !state->atEnd;
}

static void
_advanceStateForward(PARCBufferChunker *chunker, _ChunkerState *state)
{
    state->position += state->nextChunkSize;

    size_t remaining = parcBuffer_Remaining(chunker->data);

    if (remaining == 0) {
        state->atEnd = true;
    } else if (remaining > chunker->chunkSize) {
        state->nextChunkSize = chunker->chunkSize;
    } else {
        state->nextChunkSize = remaining;
    }
}

static void
_advanceStateBackward(PARCBufferChunker *chunker, _ChunkerState *state)
{
    // Previous chunk size
    size_t chunkSize = state->nextChunkSize;
    if (chunkSize != chunker->chunkSize || state->position == 0) {
        state->atEnd = true;
    } else {
        if (state->position < chunkSize) {
            state->nextChunkSize = state->position; // on next read, go to the current position
            state->position = 0; // we reached the beginning
        } else {
            state->position -= chunkSize;
        }
    }
}

static void
_advanceState(PARCBufferChunker *chunker, _ChunkerState *state)
{
    state->chunkNumber++;

    if (state->direction == 0) {
        _advanceStateForward(chunker, state);
    } else {
        _advanceStateBackward(chunker, state);
    }
}

static void *
_ccnxChunker_NextFromBuffer(PARCBufferChunker *chunker, _ChunkerState *state)
{
    size_t chunkSize = state->nextChunkSize;

    parcBuffer_SetPosition(chunker->data, state->position);
    PARCBuffer *slice = parcBuffer_CreateFromArray(parcBuffer_Overlay(chunker->data, chunkSize), chunkSize);
    slice = parcBuffer_Flip(slice);

    _advanceState(chunker, state);

    return slice;
}

static void *
_ccnxChunker_Next(PARCBufferChunker *chunker, void *state)
{
    PARCBuffer *buffer = _ccnxChunker_NextFromBuffer(chunker, state);

    if (chunker->currentElement != NULL) {
        parcBuffer_Release(&chunker->currentElement);
    }
    if (buffer != NULL) {
        chunker->currentElement = parcBuffer_Acquire(buffer);
    }

    return state;
}

static void *
_ccnxChunker_GetElement(PARCBufferChunker *chunker, void *state)
{
    return chunker->currentElement;
}

static void
_ccnxChunker_Finish(PARCBufferChunker *chunker, void *state)
{
    _ChunkerState *thestate = (_ChunkerState *) state;
    parcMemory_Deallocate(&thestate);
}

static void
_ccnxChunker_AssertValid(const void *state)
{
    // pass
}

parcObject_ExtendPARCObject(PARCBufferChunker, _destroy, NULL, NULL, NULL, NULL, NULL, NULL);
parcObject_ImplementAcquire(parcBufferChunker, PARCBufferChunker);
parcObject_ImplementRelease(parcBufferChunker, PARCBufferChunker);

PARCBufferChunker *
parcBufferChunker_Create(PARCBuffer *data, size_t chunkSize)
{
    PARCBufferChunker *chunker = parcObject_CreateInstance(PARCBufferChunker);

    if (chunker != NULL) {
        chunker->chunkSize = chunkSize;
        chunker->data = parcBuffer_Acquire(data);
        chunker->currentElement = NULL;
    }

    return chunker;
}

PARCIterator *
parcBufferChunker_ForwardIterator(const PARCBufferChunker *chunker)
{
    PARCIterator *iterator = parcIterator_Create((void *) chunker,
                                                 (void *(*)(PARCObject *))_InitForward,
                                                 (bool (*)(PARCObject *, void *))_ccnxChunker_HasNext,
                                                 (void *(*)(PARCObject *, void *))_ccnxChunker_Next,
                                                 NULL,
                                                 (void *(*)(PARCObject *, void *))_ccnxChunker_GetElement,
                                                 (void (*)(PARCObject *, void *))_ccnxChunker_Finish,
                                                 (void (*)(const void *))_ccnxChunker_AssertValid);

    return iterator;
}

PARCIterator *
parcBufferChunker_ReverseIterator(const PARCBufferChunker *chunker)
{
    PARCIterator *iterator = parcIterator_Create((void *) chunker,
                                                 (void *(*)(PARCObject *))_InitReverse,
                                                 (bool (*)(PARCObject *, void *))_ccnxChunker_HasNext,
                                                 (void *(*)(PARCObject *, void *))_ccnxChunker_Next,
                                                 NULL,
                                                 (void *(*)(PARCObject *, void *))_ccnxChunker_GetElement,
                                                 (void (*)(PARCObject *, void *))_ccnxChunker_Finish,
                                                 (void (*)(const void *))_ccnxChunker_AssertValid);

    return iterator;
}
