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
 * @file parc_Varint.h
 * @ingroup datastructures
 * @brief A Variable Length Integer.
 *
 * A variable length integer.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
#ifndef libparc_parc_VarInt_h
#define libparc_parc_VarInt_h

#include <stdint.h>

#include <parc/algol/parc_Buffer.h>

/**
 * A variable length integer value.
 * <em>
 * This particular implementation is limited to a 64 bit value.
 * </em>
 */
struct parc_varint;
typedef struct parc_varint PARCVarint;


#define PARC_VARINT_INIT { 0 }

/**
 * Create a new instance of `PARCVarint`
 *
 * @return A `PARCVarint` pointer, which must be deallocated via {@link parcVarint_Destroy()}.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCVarint *parcVarint_Create(void);

/**
 * Decode an instance of {@link PARCBuffer} of length @p length into a new instance of `PARCVarInt`
 *
 * @param [in] buffer A pointer to a `PARCBuffer`.
 * @param [in] length The number of bytes to decode.
 * @return A `PARCVarint` pointer, which must be deallocated via {@link parcVarint_Destroy()}.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode */
PARCVarint *parcVarint_DecodeBuffer(PARCBuffer *buffer, size_t length);

/**
 * Decode an instance of {@link PARCBuffer} of length @p length into a new instance of `PARCVarInt`
 *
 * @param [in] buffer A pointer to a `PARCBuffer`.
 * @param [in] length The number of bytes to decode.
 * @return A `PARCVarint` pointer, which must be deallocated via {@link parcVarint_Destroy()}.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCVarint *parcVarint_DecodeElasticByteBuffer(const PARCBuffer *buffer, size_t length);

/**
 * Create a new `PARCVarint` from bytes in a {@link PARCBuffer}.
 *
 * @param [in] buffer A pointer to a `PARCBuffer`.
 * @return A `PARCVarint` pointer, which must be deallocated via {@link parcVarint_Destroy()}.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCVarint *parcVarint_FromElasticByteBuffer(const PARCBuffer *buffer);

/**
 * Create a `PARCVarint` with the value decoded from the given {@link PARCBuffer}
 * containing a UTF-8 string encoded number.
 *
 * @param [in] buffer A pointer to a `PARCBuffer` containing a UTF-8 string encoded number.
 * @return A `PARCVarint` pointer, which must be deallocated via {@link parcVarint_Destroy()}.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCVarint *parcVarint_FromUTF8Buffer(PARCBuffer *buffer);

/**
 * Create a `PARCVarint` with the value decoded from the given {@link PARCBuffer}
 * containing a UTF-8 string encoded number.
 *
 * @param [in] buffer A pointer to a `PARCBuffer` containing a UTF-8 string encoded number.
 * @return A `PARCVarint` pointer, which must be deallocated via {@link parcVarint_Destroy()}.
 *
 */
PARCVarint *parcVarint_FromUTF8ByteBuffer(const PARCBuffer *buffer);


extern PARCVarint *parcVarint_FromUint8(uint8_t uint);

extern PARCVarint *parcVarint_FromUint32(uint32_t uint);

extern PARCVarint *parcVarint_FromUint64(uint64_t uint);

extern PARCVarint *parcVarint_ShiftLeft(PARCVarint *varint, int bits);

extern PARCVarint *parcVarint_ShiftRight(PARCVarint *varint, int bits);

extern PARCVarint *parcVarint_And(PARCVarint *varint, PARCVarint *operand);

extern PARCVarint *parcVarint_AndUint8(PARCVarint *varint, uint8_t operand);

extern PARCVarint *parcVarint_AndUint16(PARCVarint *varint, uint16_t operand);

extern PARCVarint *parcVarint_AndUint32(PARCVarint *varint, uint32_t operand);

extern PARCVarint *parcVarint_AndUint64(PARCVarint *varint, uint64_t operand);

extern PARCVarint *parcVarint_Or(PARCVarint *varint, PARCVarint *operand);

extern PARCVarint *parcVarint_OrUint8(PARCVarint *varint, uint8_t operand);

extern PARCVarint *parcVarint_OrUint16(PARCVarint *varint, uint16_t operand);

extern PARCVarint *parcVarint_OrUint32(PARCVarint *varint, uint32_t operand);

extern PARCVarint *parcVarint_OrUint64(PARCVarint *varint, uint64_t operand);

/**
 * Determine if two `PARCVarint` instances are equal.
 *
 * The following equivalence relations on non-null `PARCVarint` instances are maintained:
 *
 *  * It is reflexive: for any non-null reference value x, `PARCVarint_Equals(x, x)`
 *      must return true.
 *
 *  * It is symmetric: for any non-null reference values x and y,
 *    `parcVarint_Equals(x, y)` must return true if and only if
 *        `parcVarint_Equals(y, x)` returns true.
 *
 *  * It is transitive: for any non-null reference values x, y, and z, if
 *        `parcVarint_Equals(x, y)` returns true and
 *        `parcVarint_Equals(y, z)` returns true,
 *        then  `parcVarint_Equals(x, z)` must return true.
 *
 *  * It is consistent: for any non-null reference values x and y, multiple
 *      invocations of `parcVarint_Equals(x, y)` consistently return true or
 *      consistently return false.
 *
 *  * For any non-null reference value x, `parcVarint_Equals(x, NULL)` must
 *      return false.
 *
 * @param varint A pointer to a `PARCVarint` instance.
 * @param operand A pointer to a `PARCVarint` instance.
 * @return true if the two `PARCVarint` instances are equal.
 *
 * Example:
 * @code
 * {
 *    PARCVarint *a = parcVarint_Create();
 *    PARCVarint *b = parcVarint_Create();
 *
 *    if (parcVarint_Equals(a, b)) {
 *        // true
 *    } else {
 *        // false
 *    }
 * }
 * @endcode
 */

extern int parcVarint_Equals(PARCVarint *varint, PARCVarint *operand);

/**
 * Determine if a `PARCVarint` instance is equal to a 64bit integer.
 *
 * The following equivalence relations on non-null `PARCVarint` instances are maintained:
 *
 *  * It is reflexive: for any non-null reference value x, `PARCVarint_Uint64Equals(x, x)`
 *      must return true.
 *
 *  * It is NOT symmetric: for any non-null reference values x and y,
 *    `parcVarint_Uint64Equals(x, y)` may not return true even if
 *        `parcVarint_Uint64Equals(y, x)` returns true.
 *
 *  * It is transitive: for any non-null reference values x, y, and z, if
 *        `parcVarint_Uint64Equals(x, y)` returns true and
 *        `parcVarint_Uint64Equals(y, z)` returns true,
 *        then  `parcVarint_Uint64Equals(x, z)` must return true.
 *
 *  * It is consistent: for any non-null reference values x and y, multiple
 *      invocations of `parcVarint_Uint64Equals(x, y)` consistently return true or
 *      consistently return false.
 *
 *  * For any non-null reference value x, `parcVarint_Uint64Equals(x, NULL)` must
 *      return false.
 *
 * @param [in] varint A pointer to a `PARCVarint` instance.
 * @param [in] value A pointer to a `uint64_t` instance.
 * @return true if the two instances are equal.
 *
 * Example:
 * @code
 * {
 *    PARCVarint *a = parcVarint_Create();
 *    uint64_t *b = 10; // some integer value
 *
 *    if (parcVarint_Uint64Equals(a, b)) {
 *        // true
 *    } else {
 *        // false
 *    }
 * }
 * @endcode
 */
extern int parcVarint_EqualsUint64(PARCVarint *varint, uint64_t value);

/**
 * Determine if a `PARCVarint` instance is equal to a 32 bit integer.
 *
 * The following equivalence relations on non-null `PARCVarint` instances are maintained:
 *
 *  * It is reflexive: for any non-null reference value x, `PARCVarint_Uint32Equals(x, x)`
 *      must return true.
 *
 *  * It is NOT symmetric: for any non-null reference values x and y,
 *    `parcVarint_Uint32Equals(x, y)` may not return true even if
 *        `parcVarint_Uint32Equals(y, x)` returns true.
 *
 *  * It is transitive: for any non-null reference values x, y, and z, if
 *        `parcVarint_Uint32Equals(x, y)` returns true and
 *        `parcVarint_Uint32Equals(y, z)` returns true,
 *        then  `parcVarint_Uint32Equals(x, z)` must return true.
 *
 *  * It is consistent: for any non-null reference values x and y, multiple
 *      invocations of `parcVarint_Uint32Equals(x, y)` consistently return true or
 *      consistently return false.
 *
 *  * For any non-null reference value x, `parcVarint_Uint32Equals(x, NULL)` must
 *      return false.
 *
 * @param [in] varint A pointer to a `PARCVarint` instance.
 * @param [in] value A pointer to a `uint32_t` instance.
 * @return true if the two instances are equal.
 *
 * Example:
 * @code
 * {
 *    PARCVarint *a = parcVarint_Create();
 *    uint32_t *b = 10; // some integer value
 *
 *    if (parcVarint_Uint32Equals(a, b)) {
 *        // true
 *    } else {
 *        // false
 *    }
 * }
 * @endcode
 */
extern int parcVarint_EqualsUint32(PARCVarint *varint, uint32_t value);

/**
 * Determine if a `PARCVarint` instance is equal to a 16 bit integer.
 *
 * The following equivalence relations on non-null `PARCVarint` instances are maintained:
 *
 *  * It is reflexive: for any non-null reference value x, `PARCVarint_Uint16Equals(x, x)`
 *      must return true.
 *
 *  * It is NOT symmetric: for any non-null reference values x and y,
 *    `parcVarint_Uint16Equals(x, y)` may not return true even if
 *        `parcVarint_Uint16Equals(y, x)` returns true.
 *
 *  * It is transitive: for any non-null reference values x, y, and z, if
 *        `parcVarint_Uint16Equals(x, y)` returns true and
 *        `parcVarint_Uint16Equals(y, z)` returns true,
 *        then  `parcVarint_Uint16Equals(x, z)` must return true.
 *
 *  * It is consistent: for any non-null reference values x and y, multiple
 *      invocations of `parcVarint_Uint16Equals(x, y)` consistently return true or
 *      consistently return false.
 *
 *  * For any non-null reference value x, `parcVarint_Uint16Equals(x, NULL)` must
 *      return false.
 *
 * @param [in] varint A pointer to a `PARCVarint` instance.
 * @param [in] value A pointer to a `uint16_t` instance.
 * @return true if the two instances are equal.
 *
 * Example:
 * @code
 * {
 *    PARCVarint *a = parcVarint_Create();
 *    uint16_t *b = 10; // some integer value
 *
 *    if (parcVarint_Uint16Equals(a, b)) {
 *        // true
 *    } else {
 *        // false
 *    }
 * }
 * @endcode
 */
extern int parcVarint_EqualsUint16(PARCVarint *varint, uint16_t value);

/**
 * Determine if a `PARCVarint` instance is equal to an 8 bit integer.
 *
 * The following equivalence relations on non-null `PARCVarint` instances are maintained:
 *
 *  * It is reflexive: for any non-null reference value x, `PARCVarint_Uint8Equals(x, x)`
 *      must return true.
 *
 *  * It is NOT symmetric: for any non-null reference values x and y,
 *    `parcVarint_Uint8Equals(x, y)` may not return true even if
 *        `parcVarint_Uint8Equals(y, x)` returns true.
 *
 *  * It is transitive: for any non-null reference values x, y, and z, if
 *        `parcVarint_Uint8Equals(x, y)` returns true and
 *        `parcVarint_Uint8Equals(y, z)` returns true,
 *        then  `parcVarint_Uint8Equals(x, z)` must return true.
 *
 *  * It is consistent: for any non-null reference values x and y, multiple
 *      invocations of `parcVarint_Uint8Equals(x, y)` consistently return true or
 *      consistently return false.
 *
 *  * For any non-null reference value x, `parcVarint_Uint8Equals(x, NULL)` must
 *      return false.
 *
 * @param [in] varint A pointer to a `PARCVarint` instance.
 * @param [in] value A pointer to a `uint8_t` instance.
 * @return true if the two instances are equal.
 *
 * Example:
 * @code
 * {
 *    PARCVarint *a = parcVarint_Create();
 *    uint8_t *b = 10; // some integer value
 *
 *    if (parcVarint_Uint8Equals(a, b)) {
 *        // true
 *    } else {
 *        // false
 *    }
 * }
 * @endcode
 */
extern int parcVarint_EqualsUint8(PARCVarint *varint, uint8_t value);

extern void parcVarint_Destroy(PARCVarint **varintP);

extern char *parcVarint_ToString(char **string, PARCVarint *varint);

extern uint8_t parcVarint_AsUint8(const PARCVarint *varint);

extern uint16_t parcVarint_AsUint16(const PARCVarint *varint);

extern uint32_t parcVarint_AsUint32(const PARCVarint *varint);

/**
 * Produce the 16 low-order bits of this `PARCVarint` as a `uint8_t`.
 *
 * @param [in] varint The inpu instance of `PARCVarint`
 * @return The 16 low-order bits as a `uint8_t`
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
uint64_t parcVarint_AsUint64(const PARCVarint *varint);

/**
 * Return the value of the given `PARCVarint` cast as a `size_t`
 *
 * @param [in] varint The `PARCVarint` to cast as a `size_t`
 *
 * @return The given `PARCVarint` cast as a `size_t`
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
size_t parcVarint_AsSize(const PARCVarint *varint);

/**
 * Set the value of the given `PARCVarint` to the given value.
 *
 * @param [in,out] varint The `PARCVarint` to be modified
 * @param [in] newValue The new value for the `PARCVarint`
 * @return The modified `PARCVarint`.
 */
PARCVarint *parcVarint_Set(PARCVarint *varint, uint64_t newValue);

/**
 * Multiply the `PARCVarint`
 *
 * @param [in,out] varint The `PARCVarint` to be multiplied by the @p multiplicand
 * @param [in] multiplicand The multiplicand to multiply by
 * @return The `PARCVarint` used as input.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCVarint *parcVarint_Multiply(PARCVarint *varint, int multiplicand);

/**
 * Divide the `PARCVarint` by a divisor
 *
 * @param [in,out] varint The `PARCVarint` to be divided by the @p divisor
 * @param [in] divisor The divisor to use
 * @return The `PARCVarint` used as input.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCVarint *parcVarint_Divide(PARCVarint *varint, int divisor);
/**
 * Multiply the `PARCVarint`
 *
 * @param [in,out] varint The `PARCVarint` to which the @p addend should be added
 * @param [in] addend The number to add to the `PARCVarint`
 * @return The `PARCVarint` used as input.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCVarint *parcVarint_Add(PARCVarint *varint, int addend);

/**
 * Subtract the @p subtrahend from the `PARCVarint`.
 *
 * @param [in,out] varint The `PARCVarint` from which to subtract the @p subtrahend
 * @param [in] subtrahend The number to subtract from the  `PARCVarint`
 * @return The `PARCVarint` used as input.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCVarint *parcVarint_Subtract(PARCVarint *varint, int subtrahend);
#endif // libparc_parc_VarInt_h
