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
 * @file parc_URISegment.h
 * @ingroup networking
 * @brief A Universal Resource Identifier (URI) Segment
 *
 * @author Christopher A. Wood, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef libparc_parc_URISegment_h
#define libparc_parc_URISegment_h

#include <parc/algol/parc_BufferComposer.h>

struct parc_uri_segment;
typedef struct parc_uri_segment PARCURISegment;

/**
 * Create a `PARCURISegment` instance copying data from the given pointer and length.
 *
 * A `PARCURISegment` is a tuple consisting of a pointer to arbitrary memory containing the first byte
 * of `length` bytes as the value of the segment.
 *
 * Since the input parameter `pointer` points to arbitrary memory,
 * this function makes a private copy of the data.
 *
 * @param [in] length The length of the given array pointed to by @p segment.
 * @param [in] segment A pointer to an array consisting of at least @p length bytes.
 *
 * @return A `PARCURISegment` instance referring to the given pointer and length.
 *
 * Example:
 * @code
 * {
 *     PARCURISegment *segment = parcURISegment_Create(5, "Hello");
 *     ...
 *     parcURISegment_Release(&segment);
 * }
 * @endcode
 */
PARCURISegment *parcURISegment_Create(size_t length, const unsigned char segment[length]);

/**
 * Create a `PARCURISegment` instance referencing the given {@link PARCBuffer}.
 *
 * A new reference to the given `PARCBuffer` is acquired.
 *
 * @param [in] buffer A pointer to a `PARCBuffer` instance.
 *
 * @return A `PARCURISegment` instance referring to the given `PARCBuffer`
 *
 * Example:
 * @code
 * {
 *     PARCBuffer *buffer = parcBuffer_Wrap("lci:/foo/bar", 12, 0, 12);
 *     PARCURISegment *segment = parcURISegment_CreateFromBuffer(buffer);
 *     ...
 *     parcURISegment_Release(&segment);
 * }
 * @endcode
 */
PARCURISegment *parcURISegment_CreateFromBuffer(PARCBuffer *buffer);

/**
 * Increase the number of references to a `PARCURISegment`.
 *
 * Note that new `PARCURISegment` is not created,
 * only that the given `PARCURISegment` reference count is incremented.
 * Discard the reference by invoking {@link parcURISegment_Release}.
 *
 * @param [in] segment A pointer to the original instance.
 *
 * @return The value of the input parameter @p instance.
 *
 * Example:
 * @code
 * {
 *     PARCURISegment *x = parcURISegment_Create(5, "Hello");
 *
 *     PARCURISegment *x2 = parcURISegment_Acquire(x);
 *
 *     parcURISegment_Release(&x);
 *     parcURISegment_Release(&x2);
 * }
 * @endcode
 *
 * @see {@link parcURISegment_Release}
 */
PARCURISegment *parcURISegment_Acquire(const PARCURISegment *segment);

/**
 * Release a previously acquired reference to the specified instance,
 * decrementing the reference count for the instance.
 *
 * The pointer to the instance is set to NULL as a side-effect of this function.
 *
 * If the invocation causes the last reference to the instance to be released,
 * the instance is deallocated and the instance's implementation will perform
 * additional cleanup and release other privately held references.
 *
 * @param [in,out] segmentPtr A pointer to a pointer to the instance to release.
 *
 * Example:
 * @code
 * {
 *     PARCURISegment *x = parcURISegment_Create(5, "Hello");
 *
 *     parcURISegment_Release(&x);
 * }
 * @endcode
 */
void parcURISegment_Release(PARCURISegment **segmentPtr);

/**
 * Compares two `PARCURISegment` instances for order.
 *
 * As strings, URI segments are compared in normal lexographical order. This
 * is analogous to strcmp(...).
 *
 * @param [in] a A `PARCURISegment` pointer, or NULL.
 * @param [in] b A `PARCURISegment` pointer, or NULL.
 *
 * @return A negative integer, zero, or a positive integer as a is less than, equal to, or greater than b, accordingly.
 *
 * Example:
 * @code
 * {
 *     PARCURISegment *segmentA = parcURISegment_Create(6, "HelloA");
 *     PARCURISegment *segmentB = parcURISegment_Create(6, "HelloB");
 *     int cmp = parcURISegment_Compare(segmentA, segmentB);
 *     // cmp will be a negative integer since "HelloA" < "HelloB"
 * }
 * @endcode
 */
int parcURISegment_Compare(const PARCURISegment *a, const PARCURISegment *b);

/**
 * Create an independant copy the given `PARCURISegment`
 *
 * A new URI segment is created as a complete copy of the original.
 *
 * @param [in] segment A pointer to a `PARCURISegment` instance.
 *
 * @return NULL Memory could not be allocated.
 * @return non-NULL A pointer to a new `PARCURISegment` instance.
 *
 * Example:
 * @code
 * {
 *     PARCURISegment *segment = parcURISegment_Create(5, "Hello");
 *     PARCURISegment *copy = parcURISegment_Clone(segment);
 *
 *     // use either segment or copy as needed
 *
 *     parcBuffer_Release(&copy);
 *     parcBuffer_Release(&segment);
 * }
 * @endcode
 *
 */
PARCURISegment *parcURISegment_Clone(const PARCURISegment *segment);

/**
 * Determine if two `PARCURISegment` instances are equal.
 *
 * The following equivalence relations on non-null `PARCURISegment` instances are maintained
 *
 *   * It is reflexive: for any non-null reference value x, `parcURISegment_Equals(x, x)` must return true.
 *
 *   * It is symmetric: for any non-null reference values x and y, `parcURISegment_Equals(x, y)` must return true if and only if
 *        `parcURISegment_Equals(y x)` returns true.
 *
 *   * It is transitive: for any non-null reference values x, y, and z, if
 *        `parcURISegment_Equals(x, y)` returns true and
 *        `parcURISegment_Equals(y, z)` returns true,
 *        then `parcURISegment_Equals(x, z)` must return true.
 *
 *   * It is consistent: for any non-null reference values x and y, multiple invocations of `parcURISegment_Equals(x, y)`
 *         consistently return true or consistently return false.
 *
 *   * For any non-null reference value x, `parcURISegment_Equals(x, NULL)` must return false.
 *
 *
 * @param [in] x A pointer to a `PARCURISegment` instance.
 * @param [in] y A pointer to a `PARCURISegment` instance.
 *
 * @return true `PARCURISegment` x and y are equal.
 * @return false `PARCURISegment` x and y are not equal.
 *
 * Example:
 * @code
 * {
 *     PARCURISegment *segmentA = parcURISegment_Create(5, "Hello");
 *     PARCURISegment *segmentB = parcURISegment_Create(5, "Hello");
 *
 *     if (parcURISegment_Equals(segmentA, segmentB)) {
 *          printf("The URI segments are equal\n");
 *     } else {
 *          printf("The URI segments are NOT equal\n");
 *     }
 *
 *     parcURISegment_Equals(&segmentA);
 *     parcURISegment_Equals(&segmentB);
 * }
 * @endcode
 */
bool parcURISegment_Equals(const PARCURISegment *x, const PARCURISegment *y);

/**
 * Parse a single URI segment.
 *
 * The input parameter string must point to a '/' which indicates the beginning of a segment.
 * The segment is terminated by a null byte or a '?' or '#' character and may may be zero length.
 * The output parameter pointer will be assigned the address of the first character that is not part of the parsed segment.
 *
 * The returned value must be deallocated via {@link parcMemory_Deallocate}.
 *
 * @param [in] string Pointer to the beginning of the segment
 * @param [in,out] pointer Will be assigned the address of the first character that is not part of the parsed segment.
 *
 * @return An allocated `PARCURISegment` the must be deallocated via `parcMemory_Deallocate`.
 *
 * Example:
 * @code
 * {
 *     char *pointer;
 *     PARCURISegment *segment = parcURISegment_Parse("lci:/a/b/", &pointer);
 *     ...
 *     parcBuffer_Release(&segment);
 * }
 * @endcode
 */
PARCURISegment *parcURISegment_Parse(const char *string, const char **pointer);

/**
 * Get the {@link PARCBuffer} containing the content of the given URI segment.
 *
 * The PARCBuffer is always rewound (see {@link parcBuffer_Rewind}).
 *
 * @param [in] segment A `PARCURISegment` instance from which the buffer will be extracted.
 *
 * @return A `PARCBuffer` instance containing the URI segment bytes that must be freed via {@link parcBuffer_Release()}
 *
 * Example:
 * @code
 * {
 *     PARCURISegment *segment = parcURISegment_Create(5, "Hello");
 *     PARCBuffer *segBuffer = parcURISegment_GetBuffer(segment);
 *     // use or display the segment buffer as needed...
 *
 *     parcURISegment(&segment);
 * }
 * @endcode
 */
PARCBuffer *parcURISegment_GetBuffer(const PARCURISegment *segment);

/**
 * Append a representation of the specified instance to the given {@link PARCBufferComposer}.
 *
 * The URI representation is escape-encoded for all characters specified
 *
 * @param [in] component A pointer to the instance to be appended to @p composer.
 * @param [in,out] composer A `PARCBufferComposer` to which this URI segment is appended.
 *
 * @return NULL Cannot allocate memory.
 * @return non-NULL The given `PARCBufferComposer`.
 *
 * Example:
 * @code
 * {
 *     PARCBufferComposer *result = parcBufferComposer_Create();
 *
 *     parcURISegment_BuildString(instance, result);
 *
 *     PARCBuffer *string = parcBufferComposer_FinalizeBuffer(result);
 *     printf("URI: %s\n", parcBuffer_ToString(string));
 *     parcBuffer_Release(&string);
 *
 *     parcBufferComposer_Release(&result);
 * }
 * @endcode
 */
PARCBufferComposer *parcURISegment_BuildString(const PARCURISegment *component, PARCBufferComposer *composer);

/**
 * Produce a null-terminated string representation of the specified `PARCURISegment` instance.
 *
 * The result must be freed by the caller via {@link parcMemory_Deallocate}.
 *
 * The result is percent-encoding if necessary.
 * A `PARCURISegment` may contain characters that are not permitted in the path in their native form.
 * These characters must be 'percent encoded' using the '%' followed by the hexadecimal value of the character.
 * For consistency, percent-encoded octets in the ranges of
 * ALPHA (%41-%5A and %61-%7A),
 * DIGIT (%30-%39),
 * hyphen (%2D),
 * period (%2E),
 * underscore (%5F),
 * or tilde (%7E)
 * should not be created by URI producers and,
 * when found in a URI,
 * should be decoded to their corresponding unreserved characters by URI normalizers.
 *
 * @param [in] segment A pointer to the instance.
 *
 * @return An allocated, null-terminated C string that must be deallocated via {@link parcMemory_Deallocate}.
 *
 * Example:
 * @code
 * {
 *     PARCURISegment *instance = parcURISegment_Create(5, "Hello");
 *
 *     char *string = parcURISegment_ToString(instance);
 *
 *     printf("Hello: %s\n", string);
 *     parcMemory_Deallocate((void **)&string);
 *
 *     parcURISegment_Release(&instance);
 * }
 * @endcode
 *
 * @see parcURISegment_Parse
 */
char *parcURISegment_ToString(const PARCURISegment *segment);

/**
 * Get the length, in bytes, of the given `PARCURISegment`.
 *
 * @param [in] segment A pointer to the segment to inspect.
 *
 * @return The length, in bytes, of the given `PARCURISegment`.
 *
 * Example:
 * @code
 * {
 *     PARCURISegment *instance = parcURISegment_Create(5, "Hello");
 *     size_t length = parcURISegment_Length(instance);
 *     // length will be 5
 * }
 * @endcode
 */
size_t parcURISegment_Length(const PARCURISegment *segment);
#endif // libparc_parc_URISegment_h
