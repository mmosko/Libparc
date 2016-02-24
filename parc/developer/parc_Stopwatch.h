/*
 * Copyright (c) 2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
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
 * @file parc_Timer.h
 * @brief <#Brief Description#>
 *
 * <#Detailed Description#>
 *
 * @author <#gscott#>, Palo Alto Research Center (Xerox PARC)
 * @copyright 2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef PARCLibrary_parc_Timer
#define PARCLibrary_parc_Timer
#include <stdbool.h>

#include <parc/algol/parc_JSON.h>
#include <parc/algol/parc_HashCode.h>

struct PARCStopwatch;
typedef struct PARCStopwatch PARCStopwatch;

/**
 * Increase the number of references to a `PARCStopwatch` instance.
 *
 * Note that new `PARCStopwatch` is not created,
 * only that the given `PARCStopwatch` reference count is incremented.
 * Discard the reference by invoking `parcStopwatch_Release`.
 *
 * @param [in] instance A pointer to a valid PARCStopwatch instance.
 *
 * @return The same value as @p instance.
 *
 * Example:
 * @code
 * {
 *     PARCStopwatch *a = parcStopwatch_Create();
 *
 *     PARCStopwatch *b = parcStopwatch_Acquire();

 *     parcStopwatch_Release(&a);
 *     parcStopwatch_Release(&b);
 * }
 * @endcode
 */
PARCStopwatch *parcStopwatch_Acquire(const PARCStopwatch *instance);

#ifdef PARCLibrary_DISABLE_VALIDATION
#  define parcStopwatch_OptionalAssertValid(_instance_)
#else
#  define parcStopwatch_OptionalAssertValid(_instance_) parcStopwatch_AssertValid(_instance_)
#endif

/**
 * Assert that the given `PARCStopwatch` instance is valid.
 *
 * @param [in] instance A pointer to a valid PARCStopwatch instance.
 *
 * Example:
 * @code
 * {
 *     PARCStopwatch *a = parcStopwatch_Create();
 *
 *     parcStopwatch_AssertValid(a);
 *
 *     printf("Instance is valid.\n");
 *
 *     parcStopwatch_Release(&b);
 * }
 * @endcode
 */
void parcStopwatch_AssertValid(const PARCStopwatch *instance);

/**
 * Create an instance of PARCStopwatch
 *
 * <#Paragraphs Of Explanation#>
 *
 * @return non-NULL A pointer to a valid PARCStopwatch instance.
 * @return NULL An error occurred.
 *
 * Example:
 * @code
 * {
 *     PARCStopwatch *a = parcStopwatch_Create();
 *
 *     parcStopwatch_Release(&a);
 * }
 * @endcode
 */
PARCStopwatch *parcStopwatch_Create(void);

/**
 * Compares @p instance with @p other for order.
 *
 * Returns a negative integer, zero, or a positive integer as @p instance
 * is less than, equal to, or greater than @p other.
 *
 * @param [in] instance A pointer to a valid PARCStopwatch instance.
 * @param [in] other A pointer to a valid PARCStopwatch instance.
 *
 * @return <0 Instance is less than @p other.
 * @return 0 Instance a and instance b compare the same.
 * @return >0 Instance a is greater than instance b.
 *
 * Example:
 * @code
 * {
 *     PARCStopwatch *a = parcStopwatch_Create();
 *     PARCStopwatch *b = parcStopwatch_Create();
 *
 *     if (parcStopwatch_Compare(a, b) == 0) {
 *         printf("Instances are equal.\n");
 *     }
 *
 *     parcStopwatch_Release(&a);
 *     parcStopwatch_Release(&b);
 * }
 * @endcode
 *
 * @see parcStopwatch_Equals
 */
int parcStopwatch_Compare(const PARCStopwatch *instance, const PARCStopwatch *other);

/**
 * Create an independent copy the given `PARCBuffer`
 *
 * A new buffer is created as a complete copy of the original.
 *
 * @param [in] original A pointer to a valid PARCStopwatch instance.
 *
 * @return NULL Memory could not be allocated.
 * @return non-NULL A pointer to a new `PARCStopwatch` instance.
 *
 * Example:
 * @code
 * {
 *     PARCStopwatch *a = parcStopwatch_Create();
 *
 *     PARCStopwatch *copy = parcStopwatch_Copy(&b);
 *
 *     parcStopwatch_Release(&b);
 *     parcStopwatch_Release(&copy);
 * }
 * @endcode
 */
PARCStopwatch *parcStopwatch_Copy(const PARCStopwatch *original);

/**
 * Print a human readable representation of the given `PARCStopwatch`.
 *
 * @param [in] instance A pointer to a valid PARCStopwatch instance.
 * @param [in] indentation The indentation level to use for printing.
 *
 * Example:
 * @code
 * {
 *     PARCStopwatch *a = parcStopwatch_Create();
 *
 *     parcStopwatch_Display(a, 0);
 *
 *     parcStopwatch_Release(&a);
 * }
 * @endcode
 */
void parcStopwatch_Display(const PARCStopwatch *instance, int indentation);

/**
 * Determine if two `PARCStopwatch` instances are equal.
 *
 * The following equivalence relations on non-null `PARCStopwatch` instances are maintained: *
 *   * It is reflexive: for any non-null reference value x, `parcStopwatch_Equals(x, x)` must return true.
 *
 *   * It is symmetric: for any non-null reference values x and y, `parcStopwatch_Equals(x, y)` must return true if and only if
 *        `parcStopwatch_Equals(y x)` returns true.
 *
 *   * It is transitive: for any non-null reference values x, y, and z, if
 *        `parcStopwatch_Equals(x, y)` returns true and
 *        `parcStopwatch_Equals(y, z)` returns true,
 *        then `parcStopwatch_Equals(x, z)` must return true.
 *
 *   * It is consistent: for any non-null reference values x and y, multiple invocations of `parcStopwatch_Equals(x, y)`
 *         consistently return true or consistently return false.
 *
 *   * For any non-null reference value x, `parcStopwatch_Equals(x, NULL)` must return false.
 *
 * @param [in] x A pointer to a valid PARCStopwatch instance.
 * @param [in] y A pointer to a valid PARCStopwatch instance.
 *
 * @return true The instances x and y are equal.
 *
 * Example:
 * @code
 * {
 *     PARCStopwatch *a = parcStopwatch_Create();
 *     PARCStopwatch *b = parcStopwatch_Create();
 *
 *     if (parcStopwatch_Equals(a, b)) {
 *         printf("Instances are equal.\n");
 *     }
 *
 *     parcStopwatch_Release(&a);
 *     parcStopwatch_Release(&b);
 * }
 * @endcode
 * @see parcStopwatch_HashCode
 */
bool parcStopwatch_Equals(const PARCStopwatch *x, const PARCStopwatch *y);

/**
 * Returns a hash code value for the given instance.
 *
 * The general contract of `HashCode` is:
 *
 * Whenever it is invoked on the same instance more than once during an execution of an application,
 * the `HashCode` function must consistently return the same value,
 * provided no information used in a corresponding comparisons on the instance is modified.
 *
 * This value need not remain consistent from one execution of an application to another execution of the same application.
 * If two instances are equal according to the {@link parcStopwatch_Equals} method,
 * then calling the {@link parcStopwatch_HashCode} method on each of the two instances must produce the same integer result.
 *
 * It is not required that if two instances are unequal according to the
 * {@link parcStopwatch_Equals} function,
 * then calling the `parcStopwatch_HashCode`
 * method on each of the two objects must produce distinct integer results.
 *
 * @param [in] instance A pointer to a valid PARCStopwatch instance.
 *
 * @return The hashcode for the given instance.
 *
 * Example:
 * @code
 * {
 *     PARCStopwatch *a = parcStopwatch_Create();
 *
 *     PARCHashCode hashValue = parcStopwatch_HashCode(buffer);
 *     parcStopwatch_Release(&a);
 * }
 * @endcode
 */
PARCHashCode parcStopwatch_HashCode(const PARCStopwatch *instance);

/**
 * Determine if an instance of `PARCStopwatch` is valid.
 *
 * Valid means the internal state of the type is consistent with its required current or future behaviour.
 * This may include the validation of internal instances of types.
 *
 * @param [in] instance A pointer to a valid PARCStopwatch instance.
 *
 * @return true The instance is valid.
 * @return false The instance is not valid.
 *
 * Example:
 * @code
 * {
 *     PARCStopwatch *a = parcStopwatch_Create();
 *
 *     if (parcStopwatch_IsValid(a)) {
 *         printf("Instance is valid.\n");
 *     }
 *
 *     parcStopwatch_Release(&a);
 * }
 * @endcode
 *
 */
bool parcStopwatch_IsValid(const PARCStopwatch *instance);

/**
 * Release a previously acquired reference to the given `PARCStopwatch` instance,
 * decrementing the reference count for the instance.
 *
 * The pointer to the instance is set to NULL as a side-effect of this function.
 *
 * If the invocation causes the last reference to the instance to be released,
 * the instance is deallocated and the instance's implementation will perform
 * additional cleanup and release other privately held references.
 *
 * @param [in,out] instancePtr A pointer to a pointer to the instance to release.
 *
 * Example:
 * @code
 * {
 *     PARCStopwatch *a = parcStopwatch_Create();
 *
 *     parcStopwatch_Release(&a);
 * }
 * @endcode
 */
void parcStopwatch_Release(PARCStopwatch **instancePtr);

/**
 * Create a `PARCJSON` instance (representation) of the given object.
 *
 * @param [in] instance A pointer to a valid PARCStopwatch instance.
 *
 * @return NULL Memory could not be allocated to contain the `PARCJSON` instance.
 * @return non-NULL An allocated C string that must be deallocated via parcMemory_Deallocate().
 *
 * Example:
 * @code
 * {
 *     PARCStopwatch *a = parcStopwatch_Create();
 *
 *     PARCJSON *json = parcStopwatch_ToJSON(a);
 *
 *     printf("JSON representation: %s\n", parcJSON_ToString(json));
 *     parcJSON_Release(&json);
 *
 *     parcStopwatch_Release(&a);
 * }
 * @endcode
 */
PARCJSON *parcStopwatch_ToJSON(const PARCStopwatch *instance);

/**
 * Produce a null-terminated string representation of the specified `PARCStopwatch`.
 *
 * The result must be freed by the caller via {@link parcMemory_Deallocate}.
 *
 * @param [in] instance A pointer to a valid PARCStopwatch instance.
 *
 * @return NULL Cannot allocate memory.
 * @return non-NULL A pointer to an allocated, null-terminated C string that must be deallocated via {@link parcMemory_Deallocate}.
 *
 * Example:
 * @code
 * {
 *     PARCStopwatch *a = parcStopwatch_Create();
 *
 *     char *string = parcStopwatch_ToString(a);
 *
 *     parcStopwatch_Release(&a);
 *
 *     parcMemory_Deallocate(&string);
 * }
 * @endcode
 *
 * @see parcStopwatch_Display
 */
char *parcStopwatch_ToString(const PARCStopwatch *instance);

/**
 * <#One Line Description#>
 *
 * <#Paragraphs Of Explanation#>
 *
 * @param [in] timer A pointer to a valid PARCStopwatch instance.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
void parcStopwatch_Start(PARCStopwatch *timer);

/**
 * <#One Line Description#>
 *
 * <#Paragraphs Of Explanation#>
 *
 * @param [in] timer A pointer to a valid PARCStopwatch instance.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
void parcStopwatch_Stop(PARCStopwatch *timer);

/**
 * <#One Line Description#>
 *
 * <#Paragraphs Of Explanation#>
 *
 * @param [in] timer A pointer to a valid PARCStopwatch instance.
 *
 * @return The difference between the start and stop times.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
uint64_t parcStopwatch_ElapsedTime(const PARCStopwatch *timer);
#endif
