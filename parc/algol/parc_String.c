/*
 * Copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
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
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#include <config.h>

#include <parc/algol/parc_Memory.h>
#include <parc/algol/parc_Object.h>
#include <parc/algol/parc_DisplayIndented.h>

#include <parc/algol/parc_String.h>

struct PARCString {
    char *string;
};

static bool
_parcString_Destructor(PARCString **instancePtr)
{
    assertNotNull(instancePtr, "Parameter must be a non-null pointer to a PARCString pointer.");
    PARCString *string = *instancePtr;

    parcMemory_Deallocate(&string->string);
    return true;
}

parcObject_ImplementAcquire(parcString, PARCString);

parcObject_ImplementRelease(parcString, PARCString);

parcObject_Override(PARCString, PARCObject,
                    .destructor = (PARCObjectDestructor *) _parcString_Destructor,
                    .copy = (PARCObjectCopy *) parcString_Copy,
                    .display = (PARCObjectDisplay *) parcString_Display,
                    .toString = (PARCObjectToString *) parcString_ToString,
                    .equals = (PARCObjectEquals *) parcString_Equals,
                    .compare = (PARCObjectCompare *) parcString_Compare,
                    .hashCode = (PARCObjectHashCode *) parcString_HashCode,
                    .toJSON = (PARCObjectToJSON *) parcString_ToJSON,
                    .display = (PARCObjectDisplay *) parcString_Display);

void
parcString_AssertValid(const PARCString *instance)
{
    assertTrue(parcString_IsValid(instance),
               "PARCString is not valid.");
}

PARCString *
parcString_Create(const char *string)
{
    PARCString *result = parcObject_CreateInstance(PARCString);
    if (result != NULL) {
        result->string = parcMemory_StringDuplicate(string, strlen(string));
    }
    return result;
}

PARCString *
parcString_CreateFromBuffer(const PARCBuffer *buffer)
{
    PARCString *result = parcString_Create(parcBuffer_Overlay((PARCBuffer *) buffer, 0));

    return result;
}

int
parcString_Compare(const PARCString *string, const PARCString *other)
{
    int result = 0;

    if (string == NULL) {
        if (other != NULL) {
            result = -1;
        }
    } else if (other == NULL) {
        result = 1;
    } else {
        parcString_OptionalAssertValid(string);
        parcString_OptionalAssertValid(other);

        int comparison = strcmp(string->string, other->string);
        if (comparison < 0) {
            result = -1;
        } else if (comparison > 0) {
            result = 1;
        }
    }

    return result;
}

PARCString *
parcString_Copy(const PARCString *original)
{
    PARCString *result = parcString_Create(original->string);

    return result;
}

void
parcString_Display(const PARCString *instance, int indentation)
{
    parcDisplayIndented_PrintLine(indentation, "PARCString@%p {", instance);
    parcDisplayIndented_PrintLine(indentation + 1, "%s", instance->string);
    parcDisplayIndented_PrintLine(indentation, "}");
}

bool
parcString_Equals(const PARCString *x, const PARCString *y)
{
    bool result = false;

    if (x == y) {
        result = true;
    } else if (x == NULL || y == NULL) {
        result = false;
    } else {
        parcString_OptionalAssertValid(x);
        parcString_OptionalAssertValid(y);

        result = strcmp(x->string, y->string) == 0;
    }

    return result;
}

PARCHashCode
parcString_HashCode(const PARCString *string)
{
    PARCHashCode result = 0;

    result = parcHashCode_Hash((uint8_t *) string->string, strlen(string->string));

    return result;
}

bool
parcString_IsValid(const PARCString *string)
{
    bool result = false;

    if (string != NULL) {
        if (string->string != NULL) {
            result = true;
        }
    }

    return result;
}

PARCJSON *
parcString_ToJSON(const PARCString *string)
{
    PARCJSON *result = parcJSON_Create();

    return result;
}

char *
parcString_ToString(const PARCString *string)
{
    char *result = parcMemory_StringDuplicate(string->string, strlen(string->string));

    return result;
}

const char *
parcString_GetString(const PARCString *string)
{
    parcString_OptionalAssertValid(string);

    return string->string;
}
