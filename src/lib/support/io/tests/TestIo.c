/**
 *    Copyright (c) 2022 Project CHIP Authors
 *    Copyright 2012-2016 Nest Labs Inc. All Rights Reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *      This file implements a unit test suite for the C language
 *      binding of the memory-mapped I/O functions and macros.
 *
 *      Note: Matter UnitTestRegistration currently requires C++.
 *      At the time of the port, the tests pass when renaming this
 *      file to .cpp and registering the test suite below.
 *
 */

#include "lib/support/io/tests/TestIo.h"

#include <stdlib.h>
#include <unistd.h>

#include <lib/support/io/io.h>

#include <nlunit-test.h>

static void CheckIntrospection(nlTestSuite *inSuite, void *inContext)
{
    bool aligned;
    uint8_t v8;
    uint16_t v16;
    uint32_t v32;
    uint64_t v64;
    _uint128_t v128;

    // Check for natural alignment of an 8-bit stack variable.

    aligned = IoIsAligned(&v8, sizeof(v8));
    NL_TEST_ASSERT(inSuite, aligned == true);

    // Check for natural alignment of an 16-bit stack variable, which
    // should also be aligned on 8-bit as well.

    aligned = IoIsAligned(&v16, sizeof(v16));
    NL_TEST_ASSERT(inSuite, aligned == true);

    aligned = IoIsAligned(&v16, sizeof(v8));
    NL_TEST_ASSERT(inSuite, aligned == true);

    // Check for natural alignment of an 32-bit stack variable, which
    // should also be aligned on 16- and 8-bit as well.

    aligned = IoIsAligned(&v32, sizeof(v32));
    NL_TEST_ASSERT(inSuite, aligned == true);

    aligned = IoIsAligned(&v32, sizeof(v16));
    NL_TEST_ASSERT(inSuite, aligned == true);

    aligned = IoIsAligned(&v32, sizeof(v8));
    NL_TEST_ASSERT(inSuite, aligned == true);

    // Check for natural alignment of an 64-bit stack variable, which
    // should also be aligned on 32-, 16-, and 8-bit as well.

    aligned = IoIsAligned(&v64, sizeof(v64));
    NL_TEST_ASSERT(inSuite, aligned == true);

    aligned = IoIsAligned(&v64, sizeof(v32));
    NL_TEST_ASSERT(inSuite, aligned == true);

    aligned = IoIsAligned(&v64, sizeof(v16));
    NL_TEST_ASSERT(inSuite, aligned == true);

    aligned = IoIsAligned(&v64, sizeof(v8));
    NL_TEST_ASSERT(inSuite, aligned == true);

    // Check for natural alignment of an 128-bit stack variable, which
    // should also be aligned on 64-, 32-, 16-, and 8-bit as well.

    aligned = IoIsAligned(&v128, sizeof(v128));
    NL_TEST_ASSERT(inSuite, aligned == true);

    aligned = IoIsAligned(&v128, sizeof(v64));
    NL_TEST_ASSERT(inSuite, aligned == true);

    aligned = IoIsAligned(&v128, sizeof(v32));
    NL_TEST_ASSERT(inSuite, aligned == true);

    aligned = IoIsAligned(&v128, sizeof(v16));
    NL_TEST_ASSERT(inSuite, aligned == true);

    aligned = IoIsAligned(&v128, sizeof(v8));
    NL_TEST_ASSERT(inSuite, aligned == true);
}
      
static void CheckAlignedGet(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t s8 = MAGIC_8;
    const uint16_t s16 = MAGIC_16;
    const uint32_t s32 = MAGIC_32;
    const uint64_t s64 = MAGIC_64;
    uint8_t v8;
    uint16_t v16;
    uint32_t v32;
    uint64_t v64;

    v8 = IoGetAligned8(&s8);
    NL_TEST_ASSERT(inSuite, v8 == MAGIC_8);

    v16 = IoGetAligned16(&s16);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);

    v32 = IoGetAligned32(&s32);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);

    v64 = IoGetAligned64(&s64);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
}
         
static void CheckAlignedPut(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t v8 = MAGIC_8;
    const uint16_t v16 = MAGIC_16;
    const uint32_t v32 = MAGIC_32;
    const uint64_t v64 = MAGIC_64;
    uint8_t s8;
    uint16_t s16;
    uint32_t s32;
    uint64_t s64;

    IoPutAligned8(&s8, v8);
    NL_TEST_ASSERT(inSuite, s8 == MAGIC_8);

    IoPutAligned16(&s16, v16);
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);

    IoPutAligned32(&s32, v32);
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);

    IoPutAligned64(&s64, v64);
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
}
         
static void CheckUnalignedGet(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t s8 = MAGIC_8;
    const uint16_t s16 = MAGIC_16;
    const uint32_t s32 = MAGIC_32;
    const uint64_t s64 = MAGIC_64;
    uint8_t buffer[sizeof(uint64_t) * 2];
    uint8_t v8;
    uint16_t v16;
    uint32_t v32;
    uint64_t v64;
    void *p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    memcpy(p, &s8, sizeof(s8));

    v8 = IoGetUnaligned8(p);
    NL_TEST_ASSERT(inSuite, v8 == MAGIC_8);

    // Try 16-bit quantities.

    p = &buffer[0];
    memcpy(p, &s16, sizeof(s16));

    v16 = IoGetUnaligned16(p);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);

    p = &buffer[1];
    memcpy(p, &s16, sizeof(s16));

    v16 = IoGetUnaligned16(p);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);

    // Try 32-bit quantities.

    p = &buffer[0];
    memcpy(p, &s32, sizeof(s32));

    v32 = IoGetUnaligned32(p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);

    p = &buffer[1];
    memcpy(p, &s32, sizeof(s32));

    v32 = IoGetUnaligned32(p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);

    p = &buffer[2];
    memcpy(p, &s32, sizeof(s32));

    v32 = IoGetUnaligned32(p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);

    p = &buffer[3];
    memcpy(p, &s32, sizeof(s32));

    v32 = IoGetUnaligned32(p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);

    // Try 64-bit quantities.

    p = &buffer[0];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetUnaligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[1];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetUnaligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[2];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetUnaligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[3];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetUnaligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[4];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetUnaligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[5];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetUnaligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[6];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetUnaligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[7];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetUnaligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
}
       
static void CheckUnalignedPut(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t v8 = MAGIC_8;
    const uint16_t v16 = MAGIC_16;
    const uint32_t v32 = MAGIC_32;
    const uint64_t v64 = MAGIC_64;
    uint8_t buffer[sizeof(uint64_t) * 2];
    uint8_t s8;
    uint16_t s16;
    uint32_t s32;
    uint64_t s64;
    void *p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    IoPutUnaligned8(p, v8);
    memcpy(&s8, p, sizeof(v8));
    NL_TEST_ASSERT(inSuite, s8 == MAGIC_8);

    // Try 16-bit quantities.

    p = &buffer[0];
    IoPutUnaligned16(p, v16);
    memcpy(&s16, p, sizeof(v16));
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);

    p = &buffer[1];
    IoPutUnaligned16(p, v16);
    memcpy(&s16, p, sizeof(v16));
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);

    // Try 32-bit quantities.

    p = &buffer[0];
    IoPutUnaligned32(p, v32);
    memcpy(&s32, p, sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);

    p = &buffer[1];
    IoPutUnaligned32(p, v32);
    memcpy(&s32, p, sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);

    p = &buffer[2];
    IoPutUnaligned32(p, v32);
    memcpy(&s32, p, sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);

    p = &buffer[3];
    IoPutUnaligned32(p, v32);
    memcpy(&s32, p, sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);

    // Try 64-bit quantities.

    p = &buffer[0];
    IoPutUnaligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[1];
    IoPutUnaligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[2];
    IoPutUnaligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[3];
    IoPutUnaligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[4];
    IoPutUnaligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[5];
    IoPutUnaligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[6];
    IoPutUnaligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[7];
    IoPutUnaligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
}
       
static void CheckMaybeAlignedGet(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t s8 = MAGIC_8;
    const uint16_t s16 = MAGIC_16;
    const uint32_t s32 = MAGIC_32;
    const uint64_t s64 = MAGIC_64;
    uint8_t buffer[sizeof(uint64_t) * 2];
    uint8_t v8;
    uint16_t v16;
    uint32_t v32;
    uint64_t v64;
    void *p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    v8 = IoGetMaybeAligned8(&s8);
    NL_TEST_ASSERT(inSuite, v8 == MAGIC_8);

    // Try 16-bit quantities.

    p = &buffer[0];
    memcpy(p, &s16, sizeof(s16));

    v16 = IoGetMaybeAligned16(p);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);

    p = &buffer[1];
    memcpy(p, &s16, sizeof(s16));

    v16 = IoGetMaybeAligned16(p);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);

    // Try 32-bit quantities.

    p = &buffer[0];
    memcpy(p, &s32, sizeof(s32));

    v32 = IoGetMaybeAligned32(p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);

    p = &buffer[1];
    memcpy(p, &s32, sizeof(s32));

    v32 = IoGetMaybeAligned32(p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);

    p = &buffer[2];
    memcpy(p, &s32, sizeof(s32));

    v32 = IoGetMaybeAligned32(p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);

    p = &buffer[3];
    memcpy(p, &s32, sizeof(s32));

    v32 = IoGetMaybeAligned32(p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);

    // Try 64-bit quantities.

    p = &buffer[0];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetMaybeAligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[1];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetMaybeAligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[2];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetMaybeAligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[3];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetMaybeAligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[4];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetMaybeAligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[5];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetMaybeAligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[6];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetMaybeAligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[7];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGetMaybeAligned64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
}
    
static void CheckMaybeAlignedPut(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t v8 = MAGIC_8;
    const uint16_t v16 = MAGIC_16;
    const uint32_t v32 = MAGIC_32;
    const uint64_t v64 = MAGIC_64;
    uint8_t buffer[sizeof(uint64_t) * 2];
    uint8_t s8;
    uint16_t s16;
    uint32_t s32;
    uint64_t s64;
    void *p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    IoPutMaybeAligned8(p, v8);
    memcpy(&s8, p, sizeof(v8));
    NL_TEST_ASSERT(inSuite, s8 == MAGIC_8);

    // Try 16-bit quantities.

    p = &buffer[0];
    IoPutMaybeAligned16(p, v16);
    memcpy(&s16, p, sizeof(v16));
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);

    p = &buffer[1];
    IoPutMaybeAligned16(p, v16);
    memcpy(&s16, p, sizeof(v16));
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);

    // Try 32-bit quantities.

    p = &buffer[0];
    IoPutMaybeAligned32(p, v32);
    memcpy(&s32, p, sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);

    p = &buffer[1];
    IoPutMaybeAligned32(p, v32);
    memcpy(&s32, p, sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);

    p = &buffer[2];
    IoPutMaybeAligned32(p, v32);
    memcpy(&s32, p, sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);

    p = &buffer[3];
    IoPutMaybeAligned32(p, v32);
    memcpy(&s32, p, sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);

    // Try 64-bit quantities.

    p = &buffer[0];
    IoPutMaybeAligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[1];
    IoPutMaybeAligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[2];
    IoPutMaybeAligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[3];
    IoPutMaybeAligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[4];
    IoPutMaybeAligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[5];
    IoPutMaybeAligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[6];
    IoPutMaybeAligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[7];
    IoPutMaybeAligned64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
}

static void CheckGet(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t s8 = MAGIC_8;
    const uint16_t s16 = MAGIC_16;
    const uint32_t s32 = MAGIC_32;
    const uint64_t s64 = MAGIC_64;
    uint8_t buffer[sizeof(uint64_t) * 2];
    uint8_t v8;
    uint16_t v16;
    uint32_t v32;
    uint64_t v64;
    void *p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    v8 = IoGet8(&s8);
    NL_TEST_ASSERT(inSuite, v8 == MAGIC_8);

    // Try 16-bit quantities.

    p = &buffer[0];
    memcpy(p, &s16, sizeof(s16));

    v16 = IoGet16(p);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);

    p = &buffer[1];
    memcpy(p, &s16, sizeof(s16));

    v16 = IoGet16(p);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);

    // Try 32-bit quantities.

    p = &buffer[0];
    memcpy(p, &s32, sizeof(s32));

    v32 = IoGet32(p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);

    p = &buffer[1];
    memcpy(p, &s32, sizeof(s32));

    v32 = IoGet32(p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);

    p = &buffer[2];
    memcpy(p, &s32, sizeof(s32));

    v32 = IoGet32(p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);

    p = &buffer[3];
    memcpy(p, &s32, sizeof(s32));

    v32 = IoGet32(p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);

    // Try 64-bit quantities.

    p = &buffer[0];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGet64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[1];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGet64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[2];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGet64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[3];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGet64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[4];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGet64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[5];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGet64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[6];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGet64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);

    p = &buffer[7];
    memcpy(p, &s64, sizeof(s64));

    v64 = IoGet64(p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
}
                
static void CheckPut(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t v8 = MAGIC_8;
    const uint16_t v16 = MAGIC_16;
    const uint32_t v32 = MAGIC_32;
    const uint64_t v64 = MAGIC_64;
    uint8_t buffer[sizeof(uint64_t) * 2];
    uint8_t s8;
    uint16_t s16;
    uint32_t s32;
    uint64_t s64;
    void *p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    IoPut8(p, v8);
    memcpy(&s8, p, sizeof(v8));
    NL_TEST_ASSERT(inSuite, s8 == MAGIC_8);

    // Try 16-bit quantities.

    p = &buffer[0];
    IoPut16(p, v16);
    memcpy(&s16, p, sizeof(v16));
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);

    p = &buffer[1];
    IoPut16(p, v16);
    memcpy(&s16, p, sizeof(v16));
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);

    // Try 32-bit quantities.

    p = &buffer[0];
    IoPut32(p, v32);
    memcpy(&s32, p, sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);

    p = &buffer[1];
    IoPut32(p, v32);
    memcpy(&s32, p, sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);

    p = &buffer[2];
    IoPut32(p, v32);
    memcpy(&s32, p, sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);

    p = &buffer[3];
    IoPut32(p, v32);
    memcpy(&s32, p, sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);

    // Try 64-bit quantities.

    p = &buffer[0];
    IoPut64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[1];
    IoPut64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[2];
    IoPut64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[3];
    IoPut64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[4];
    IoPut64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[5];
    IoPut64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[6];
    IoPut64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);

    p = &buffer[7];
    IoPut64(p, v64);
    memcpy(&s64, p, sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
}

static void CheckAlignedRead(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t s8 = MAGIC_8;
    const uint16_t s16 = MAGIC_16;
    const uint32_t s32 = MAGIC_32;
    const uint64_t s64 = MAGIC_64;
    uint8_t v8;
    uint16_t v16;
    uint32_t v32;
    uint64_t v64;
    const void *p;

    p = &s8;
    v8 = IoReadAligned8(&p);
    NL_TEST_ASSERT(inSuite, v8 == MAGIC_8);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&s8 + sizeof(s8));

    p = &s16;
    v16 = IoReadAligned16(&p);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&s16 + sizeof(s16));

    p = &s32;
    v32 = IoReadAligned32(&p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&s32 + sizeof(s32));

    p = &s64;
    v64 = IoReadAligned64(&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&s64 + sizeof(s64));
}
        
static void CheckAlignedWrite(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t v8 = MAGIC_8;
    const uint16_t v16 = MAGIC_16;
    const uint32_t v32 = MAGIC_32;
    const uint64_t v64 = MAGIC_64;
    uint8_t s8;
    uint16_t s16;
    uint32_t s32;
    uint64_t s64;
    void *p;

    p = &s8;
    IoWriteAligned8(&p, v8);
    NL_TEST_ASSERT(inSuite, s8 == MAGIC_8);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&s8 + sizeof(s8));

    p = &s16;
    IoWriteAligned16(&p, v16);
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&s16 + sizeof(s16));

    p = &s32;
    IoWriteAligned32(&p, v32);
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&s32 + sizeof(s32));

    p = &s64;
    IoWriteAligned64(&p, v64);
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&s64 + sizeof(s64));
}
       
static void CheckUnalignedRead(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t s8 = MAGIC_8;
    const uint16_t s16 = MAGIC_16;
    const uint32_t s32 = MAGIC_32;
    const uint64_t s64 = MAGIC_64;
    uint8_t buffer[sizeof(uint64_t) * 2];
    uint8_t v8;
    uint16_t v16;
    uint32_t v32;
    uint64_t v64;
    const void *p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    memcpy(&buffer[0], &s8, sizeof(s8));

    v8 = IoReadUnaligned8((const void **)&p);
    NL_TEST_ASSERT(inSuite, v8 == MAGIC_8);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s8));

    // Try 16-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &s16, sizeof(s16));

    v16 = IoReadUnaligned16((const void **)&p);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s16));

    p = &buffer[1];
    memcpy(&buffer[1], &s16, sizeof(s16));

    v16 = IoReadUnaligned16((const void **)&p);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s16));

    // Try 32-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &s32, sizeof(s32));

    v32 = IoReadUnaligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s32));

    p = &buffer[1];
    memcpy(&buffer[1], &s32, sizeof(s32));

    v32 = IoReadUnaligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s32));

    p = &buffer[2];
    memcpy(&buffer[2], &s32, sizeof(s32));

    v32 = IoReadUnaligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(s32));

    p = &buffer[3];
    memcpy(&buffer[3], &s32, sizeof(s32));

    v32 = IoReadUnaligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(s32));

    // Try 64-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &s64, sizeof(s64));

    v64 = IoReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s64));

    p = &buffer[1];
    memcpy(&buffer[1], &s64, sizeof(s64));

    v64 = IoReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s64));

    p = &buffer[2];
    memcpy(&buffer[2], &s64, sizeof(s64));

    v64 = IoReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(s64));

    p = &buffer[3];
    memcpy(&buffer[3], &s64, sizeof(s64));

    v64 = IoReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(s64));

    p = &buffer[4];
    memcpy(&buffer[4], &s64, sizeof(s64));

    v64 = IoReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[4] + sizeof(s64));

    p = &buffer[5];
    memcpy(&buffer[5], &s64, sizeof(s64));

    v64 = IoReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[5] + sizeof(s64));

    p = &buffer[6];
    memcpy(&buffer[6], &s64, sizeof(s64));

    v64 = IoReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[6] + sizeof(s64));

    p = &buffer[7];
    memcpy(&buffer[7], &s64, sizeof(s64));

    v64 = IoReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[7] + sizeof(s64));
}
      
static void CheckUnalignedWrite(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t v8 = MAGIC_8;
    const uint16_t v16 = MAGIC_16;
    const uint32_t v32 = MAGIC_32;
    const uint64_t v64 = MAGIC_64;
    uint8_t buffer[sizeof(uint64_t) * 2];
    uint8_t s8;
    uint16_t s16;
    uint32_t s32;
    uint64_t s64;
    void *p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    IoWriteUnaligned8(&p, v8);
    memcpy(&s8, &buffer[0], sizeof(v8));
    NL_TEST_ASSERT(inSuite, s8 == MAGIC_8);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s8));

    // Try 16-bit quantities.

    p = &buffer[0];
    IoWriteUnaligned16(&p, v16);
    memcpy(&s16, &buffer[0], sizeof(v16));
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s16));

    p = &buffer[1];
    IoWriteUnaligned16(&p, v16);
    memcpy(&s16, &buffer[1], sizeof(v16));
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s16));

    // Try 32-bit quantities.

    p = &buffer[0];
    IoWriteUnaligned32(&p, v32);
    memcpy(&s32, &buffer[0], sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s32));

    p = &buffer[1];
    IoWriteUnaligned32(&p, v32);
    memcpy(&s32, &buffer[1], sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s32));

    p = &buffer[2];
    IoWriteUnaligned32(&p, v32);
    memcpy(&s32, &buffer[2], sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(s32));

    p = &buffer[3];
    IoWriteUnaligned32(&p, v32);
    memcpy(&s32, &buffer[3], sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(s32));

    // Try 64-bit quantities.

    p = &buffer[0];
    IoWriteUnaligned64(&p, v64);
    memcpy(&s64, &buffer[0], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s64));

    p = &buffer[1];
    IoWriteUnaligned64(&p, v64);
    memcpy(&s64, &buffer[1], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s64));

    p = &buffer[2];
    IoWriteUnaligned64(&p, v64);
    memcpy(&s64, &buffer[2], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(s64));

    p = &buffer[3];
    IoWriteUnaligned64(&p, v64);
    memcpy(&s64, &buffer[3], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(s64));

    p = &buffer[4];
    IoWriteUnaligned64(&p, v64);
    memcpy(&s64, &buffer[4], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[4] + sizeof(s64));

    p = &buffer[5];
    IoWriteUnaligned64(&p, v64);
    memcpy(&s64, &buffer[5], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[5] + sizeof(s64));

    p = &buffer[6];
    IoWriteUnaligned64(&p, v64);
    memcpy(&s64, &buffer[6], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[6] + sizeof(s64));

    p = &buffer[7];
    IoWriteUnaligned64(&p, v64);
    memcpy(&s64, &buffer[7], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[7] + sizeof(s64));
}
     
static void CheckMaybeAlignedRead(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t s8 = MAGIC_8;
    const uint16_t s16 = MAGIC_16;
    const uint32_t s32 = MAGIC_32;
    const uint64_t s64 = MAGIC_64;
    uint8_t buffer[sizeof(uint64_t) * 2];
    uint8_t v8;
    uint16_t v16;
    uint32_t v32;
    uint64_t v64;
    const void *p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    memcpy(&buffer[0], &s8, sizeof(s8));

    v8 = IoReadMaybeAligned8((const void **)&p);
    NL_TEST_ASSERT(inSuite, v8 == MAGIC_8);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s8));

    // Try 16-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &s16, sizeof(s16));

    v16 = IoReadMaybeAligned16((const void **)&p);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s16));

    p = &buffer[1];
    memcpy(&buffer[1], &s16, sizeof(s16));

    v16 = IoReadMaybeAligned16((const void **)&p);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s16));

    // Try 32-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &s32, sizeof(s32));

    v32 = IoReadMaybeAligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s32));

    p = &buffer[1];
    memcpy(&buffer[1], &s32, sizeof(s32));

    v32 = IoReadMaybeAligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s32));

    p = &buffer[2];
    memcpy(&buffer[2], &s32, sizeof(s32));

    v32 = IoReadMaybeAligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(s32));

    p = &buffer[3];
    memcpy(&buffer[3], &s32, sizeof(s32));

    v32 = IoReadMaybeAligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(s32));

    // Try 64-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &s64, sizeof(s64));

    v64 = IoReadMaybeAligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s64));

    p = &buffer[1];
    memcpy(&buffer[1], &s64, sizeof(s64));

    v64 = IoReadMaybeAligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s64));

    p = &buffer[2];
    memcpy(&buffer[2], &s64, sizeof(s64));

    v64 = IoReadMaybeAligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(s64));

    p = &buffer[3];
    memcpy(&buffer[3], &s64, sizeof(s64));

    v64 = IoReadMaybeAligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(s64));

    p = &buffer[4];
    memcpy(&buffer[4], &s64, sizeof(s64));

    v64 = IoReadMaybeAligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[4] + sizeof(s64));

    p = &buffer[5];
    memcpy(&buffer[5], &s64, sizeof(s64));

    v64 = IoReadMaybeAligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[5] + sizeof(s64));

    p = &buffer[6];
    memcpy(&buffer[6], &s64, sizeof(s64));

    v64 = IoReadMaybeAligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[6] + sizeof(s64));

    p = &buffer[7];
    memcpy(&buffer[7], &s64, sizeof(s64));

    v64 = IoReadMaybeAligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[7] + sizeof(s64));
}
   
static void CheckMaybeAlignedWrite(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t v8 = MAGIC_8;
    const uint16_t v16 = MAGIC_16;
    const uint32_t v32 = MAGIC_32;
    const uint64_t v64 = MAGIC_64;
    uint8_t buffer[sizeof(uint64_t) * 2];
    uint8_t s8;
    uint16_t s16;
    uint32_t s32;
    uint64_t s64;
    void *p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    IoWriteMaybeAligned8(&p, v8);
    memcpy(&s8, &buffer[0], sizeof(v8));
    NL_TEST_ASSERT(inSuite, s8 == MAGIC_8);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s8));

    // Try 16-bit quantities.

    p = &buffer[0];
    IoWriteMaybeAligned16(&p, v16);
    memcpy(&s16, &buffer[0], sizeof(v16));
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s16));

    p = &buffer[1];
    IoWriteMaybeAligned16(&p, v16);
    memcpy(&s16, &buffer[1], sizeof(v16));
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s16));

    // Try 32-bit quantities.

    p = &buffer[0];
    IoWriteMaybeAligned32(&p, v32);
    memcpy(&s32, &buffer[0], sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s32));

    p = &buffer[1];
    IoWriteMaybeAligned32(&p, v32);
    memcpy(&s32, &buffer[1], sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s32));

    p = &buffer[2];
    IoWriteMaybeAligned32(&p, v32);
    memcpy(&s32, &buffer[2], sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(s32));

    p = &buffer[3];
    IoWriteMaybeAligned32(&p, v32);
    memcpy(&s32, &buffer[3], sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(s32));

    // Try 64-bit quantities.

    p = &buffer[0];
    IoWriteMaybeAligned64(&p, v64);
    memcpy(&s64, &buffer[0], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s64));

    p = &buffer[1];
    IoWriteMaybeAligned64(&p, v64);
    memcpy(&s64, &buffer[1], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s64));

    p = &buffer[2];
    IoWriteMaybeAligned64(&p, v64);
    memcpy(&s64, &buffer[2], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(s64));

    p = &buffer[3];
    IoWriteMaybeAligned64(&p, v64);
    memcpy(&s64, &buffer[3], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(s64));

    p = &buffer[4];
    IoWriteMaybeAligned64(&p, v64);
    memcpy(&s64, &buffer[4], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[4] + sizeof(s64));

    p = &buffer[5];
    IoWriteMaybeAligned64(&p, v64);
    memcpy(&s64, &buffer[5], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[5] + sizeof(s64));

    p = &buffer[6];
    IoWriteMaybeAligned64(&p, v64);
    memcpy(&s64, &buffer[6], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[6] + sizeof(s64));

    p = &buffer[7];
    IoWriteMaybeAligned64(&p, v64);
    memcpy(&s64, &buffer[7], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[7] + sizeof(s64));
}

static void CheckRead(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t s8 = MAGIC_8;
    const uint16_t s16 = MAGIC_16;
    const uint32_t s32 = MAGIC_32;
    const uint64_t s64 = MAGIC_64;
    uint8_t buffer[sizeof(uint64_t) * 2];
    uint8_t v8;
    uint16_t v16;
    uint32_t v32;
    uint64_t v64;
    const void *p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    memcpy(&buffer[0], &s8, sizeof(s8));

    v8 = IoRead8((const void **)&p);
    NL_TEST_ASSERT(inSuite, v8 == MAGIC_8);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s8));

    // Try 16-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &s16, sizeof(s16));

    v16 = IoRead16((const void **)&p);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s16));

    p = &buffer[1];
    memcpy(&buffer[1], &s16, sizeof(s16));

    v16 = IoRead16((const void **)&p);
    NL_TEST_ASSERT(inSuite, v16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s16));

    // Try 32-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &s32, sizeof(s32));

    v32 = IoRead32((const void **)&p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s32));

    p = &buffer[1];
    memcpy(&buffer[1], &s32, sizeof(s32));

    v32 = IoRead32((const void **)&p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s32));

    p = &buffer[2];
    memcpy(&buffer[2], &s32, sizeof(s32));

    v32 = IoRead32((const void **)&p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(s32));

    p = &buffer[3];
    memcpy(&buffer[3], &s32, sizeof(s32));

    v32 = IoRead32((const void **)&p);
    NL_TEST_ASSERT(inSuite, v32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(s32));

    // Try 64-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &s64, sizeof(s64));

    v64 = IoRead64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s64));

    p = &buffer[1];
    memcpy(&buffer[1], &s64, sizeof(s64));

    v64 = IoRead64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s64));

    p = &buffer[2];
    memcpy(&buffer[2], &s64, sizeof(s64));

    v64 = IoRead64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(s64));

    p = &buffer[3];
    memcpy(&buffer[3], &s64, sizeof(s64));

    v64 = IoRead64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(s64));

    p = &buffer[4];
    memcpy(&buffer[4], &s64, sizeof(s64));

    v64 = IoRead64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[4] + sizeof(s64));

    p = &buffer[5];
    memcpy(&buffer[5], &s64, sizeof(s64));

    v64 = IoRead64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[5] + sizeof(s64));

    p = &buffer[6];
    memcpy(&buffer[6], &s64, sizeof(s64));

    v64 = IoRead64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[6] + sizeof(s64));

    p = &buffer[7];
    memcpy(&buffer[7], &s64, sizeof(s64));

    v64 = IoRead64((const void **)&p);
    NL_TEST_ASSERT(inSuite, v64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[7] + sizeof(s64));
}

static void CheckWrite(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t v8 = MAGIC_8;
    const uint16_t v16 = MAGIC_16;
    const uint32_t v32 = MAGIC_32;
    const uint64_t v64 = MAGIC_64;
    uint8_t buffer[sizeof(uint64_t) * 2];
    uint8_t s8;
    uint16_t s16;
    uint32_t s32;
    uint64_t s64;
    void *p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    IoWrite8(&p, v8);
    memcpy(&s8, &buffer[0], sizeof(v8));
    NL_TEST_ASSERT(inSuite, s8 == MAGIC_8);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s8));

    // Try 16-bit quantities.

    p = &buffer[0];
    IoWrite16(&p, v16);
    memcpy(&s16, &buffer[0], sizeof(v16));
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s16));

    p = &buffer[1];
    IoWrite16(&p, v16);
    memcpy(&s16, &buffer[1], sizeof(v16));
    NL_TEST_ASSERT(inSuite, s16 == MAGIC_16);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s16));

    // Try 32-bit quantities.

    p = &buffer[0];
    IoWrite32(&p, v32);
    memcpy(&s32, &buffer[0], sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s32));

    p = &buffer[1];
    IoWrite32(&p, v32);
    memcpy(&s32, &buffer[1], sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s32));

    p = &buffer[2];
    IoWrite32(&p, v32);
    memcpy(&s32, &buffer[2], sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(s32));

    p = &buffer[3];
    IoWrite32(&p, v32);
    memcpy(&s32, &buffer[3], sizeof(v32));
    NL_TEST_ASSERT(inSuite, s32 == MAGIC_32);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(s32));

    // Try 64-bit quantities.

    p = &buffer[0];
    IoWrite64(&p, v64);
    memcpy(&s64, &buffer[0], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(s64));

    p = &buffer[1];
    IoWrite64(&p, v64);
    memcpy(&s64, &buffer[1], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(s64));

    p = &buffer[2];
    IoWrite64(&p, v64);
    memcpy(&s64, &buffer[2], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(s64));

    p = &buffer[3];
    IoWrite64(&p, v64);
    memcpy(&s64, &buffer[3], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(s64));

    p = &buffer[4];
    IoWrite64(&p, v64);
    memcpy(&s64, &buffer[4], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[4] + sizeof(s64));

    p = &buffer[5];
    IoWrite64(&p, v64);
    memcpy(&s64, &buffer[5], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[5] + sizeof(s64));

    p = &buffer[6];
    IoWrite64(&p, v64);
    memcpy(&s64, &buffer[6], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[6] + sizeof(s64));

    p = &buffer[7];
    IoWrite64(&p, v64);
    memcpy(&s64, &buffer[7], sizeof(v64));
    NL_TEST_ASSERT(inSuite, s64 == MAGIC_64);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[7] + sizeof(s64));
}

static const nlTest sTests[] = {
    NL_TEST_DEF("introspection",       CheckIntrospection),
    NL_TEST_DEF("aligned get",         CheckAlignedGet),
    NL_TEST_DEF("aligned put",         CheckAlignedPut),
    NL_TEST_DEF("unaligned get",       CheckUnalignedGet),
    NL_TEST_DEF("unaligned put",       CheckUnalignedPut),
    NL_TEST_DEF("maybe aligned get",   CheckMaybeAlignedGet),
    NL_TEST_DEF("maybe aligned put",   CheckMaybeAlignedPut),
    NL_TEST_DEF("get",                 CheckGet),
    NL_TEST_DEF("put",                 CheckPut),
    NL_TEST_DEF("aligned read",        CheckAlignedRead),
    NL_TEST_DEF("aligned write",       CheckAlignedWrite),
    NL_TEST_DEF("unaligned read",      CheckUnalignedRead),
    NL_TEST_DEF("unaligned write",     CheckUnalignedWrite),
    NL_TEST_DEF("maybe aligned read",  CheckMaybeAlignedRead),
    NL_TEST_DEF("maybe aligned write", CheckMaybeAlignedWrite),
    NL_TEST_DEF("read",                CheckRead),
    NL_TEST_DEF("write",               CheckWrite),
    NL_TEST_SENTINEL()
};

int TestIo(void)
{
    nlTestSuite theSuite = {
        "IO tests",
        &sTests[0]
    };

    nlTestRunner(&theSuite, NULL);
    return nlTestRunnerStats(&theSuite);
}
