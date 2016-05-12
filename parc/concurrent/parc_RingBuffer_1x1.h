/*
 * Copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX OR PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * ################################################################################
 * #
 * # PATENT NOTICE
 * #
 * # This software is distributed under the BSD 2-clause License (see LICENSE
 * # file).  This BSD License does not make any patent claims and as such, does
 * # not act as a patent grant.  The purpose of this section is for each contributor
 * # to define their intentions with respect to intellectual property.
 * #
 * # Each contributor to this source code is encouraged to state their patent
 * # claims and licensing mechanisms for any contributions made. At the end of
 * # this section contributors may each make their own statements.  Contributor's
 * # claims and grants only apply to the pieces (source code, programs, text,
 * # media, etc) that they have contributed directly to this software.
 * #
 * # There is no guarantee that this section is complete, up to date or accurate. It
 * # is up to the contributors to maintain their portion of this section and up to
 * # the user of the software to verify any claims herein.
 * #
 * # Do not remove this header notification.  The contents of this section must be
 * # present in all distributions of the software.  You may only modify your own
 * # intellectual property statements.  Please provide contact information.
 * 
 * - Palo Alto Research Center, Inc
 * This software distribution does not grant any rights to patents owned by Palo
 * Alto Research Center, Inc (PARC). Rights to these patents are available via
 * various mechanisms. As of January 2016 PARC has committed to FRAND licensing any
 * intellectual property used by its contributions to this software. You may
 * contact PARC at cipo@parc.com for more information or visit http://www.ccnx.org
 */
/**
 * @file parc_RingBuffer_1x1.h
 * @ingroup threading
 * @brief A single producer, single consumer ring buffer
 *
 * This is useful for synchronizing two (and exactly two) threads in one direction.  The
 * implementation will use a lock-free algorithm.
 *
 * Complies with the PARCRingBuffer generic facade.
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */

#ifndef libparc_parc_RingBuffer_1x1_h
#define libparc_parc_RingBuffer_1x1_h

#include <stdbool.h>
#include <stdint.h>

struct parc_ringbuffer_1x1;
typedef struct parc_ringbuffer_1x1 PARCRingBuffer1x1;

/**< Will be called for each data item on destroy */
typedef void (RingBufferEntryDestroyer)(void **entryPtr);

/**
 * Creates a ring buffer of the given size, which must be a power of 2.
 *
 * The ring buffer can store up to (elements-1) items in the buffer.  The buffer can
 * be shared between multiple producers and consumers.  Each of them should be
 * given out from a call to {@link parcRingBuffer_Acquire} to create reference counted
 * copies.
 *
 * The reference count is "1" on return.
 *
 * @param [in] elements A power of 2, indicating the maximum size of the buffer.
 * @param [in] destroyer Will be called for each ring entry when when the ring is destroyed.  May be null.
 *
 * @return non-null An allocated ring buffer.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCRingBuffer1x1 *parcRingBuffer1x1_Create(uint32_t elements, RingBufferEntryDestroyer *destroyer);

/**
 * A reference counted copy of the buffer.
 *
 * A RING WITHOUT LOCKS CAN ONLY HAVE 2 REFERENCES.
 *
 * @param [in] ring The instance of `PARCRingBuffer1x1` to acquire.
 *
 * @return non-null A reference counted copy of the ring buffer.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCRingBuffer1x1 *parcRingBuffer1x1_Acquire(const PARCRingBuffer1x1 *ring);

/**
 * Releases a reference.  The buffer will be destroyed after the last release.
 *
 * If the destroyer was specified on create, it will be called on each entry in the buffer
 * when the buffer is destroyed.
 *
 * @param [in,out] ringPtr The pointer to the pointer of the `PARCRingBuffer1x1` to be released.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
void parcRingBuffer1x1_Release(PARCRingBuffer1x1 **ringPtr);

/**
 * Non-blocking attempt to put item on ring.  May return `false` if ring is full.
 *
 * @param [in,out] ring The instance of `PARCRingBuffer1x1` on which to put the @p data.
 * @param [in] data The data to put on the @p ring.
 *
 * @return `true` Data was put on the queue
 * @return `false` Would have blocked, the queue was full
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool parcRingBuffer1x1_Put(PARCRingBuffer1x1 *ring, void *data);

/**
 * Gets the next item off the ring, or returns false if would have blocked.
 *
 * Non-blocking, gets an item off the ring, or returns false if would block
 *
 * @param [in] ring The ring buffer
 * @param [out] outputDataPtr The output pointer
 *
 * @return true Data returned in the output argument
 * @return false Ring is empty, no data returned.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool parcRingBuffer1x1_Get(PARCRingBuffer1x1 *ring, void **outputDataPtr);

/**
 * Returns the remaining capacity of the ring
 *
 * Returns the remaining capacity of the ring.  This does not guarantee the next
 * Put will not block, as other producers might consumer the space between calls.
 *
 * @param [in] ring The instance of `PARCRingBuffer1x1` .
 *
 * @return The remaining capacity on the ring.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
uint32_t parcRingBuffer1x1_Remaining(PARCRingBuffer1x1 *ring);
#endif // libparc_parc_RingBuffer_1x1_h
