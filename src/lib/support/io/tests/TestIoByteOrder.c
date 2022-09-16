/**
 *    Copyright (c) 2022 Project CHIP Authors
 *    Copyright 2015-2016 Nest Labs Inc. All Rights Reserved.
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
 *      binding of the Nest Labs memory-mapped I/O functions with
 *      byte reordering.
 *
 *      Note: Matter UnitTestRegistration currently requires C++.
 *      At the time of the port, the tests pass when renaming this
 *      file to .cpp and registering the test suite below.
 *
 */

#include "TestIoByteOrder.h"

#include <stdlib.h>
#include <unistd.h>

#include <lib/support/io/io-byteorder.h>

#include <nlunit-test.h>

static void CheckGetBig(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;

    v8_out  = IoBigEndianGet8(&v8_in);
    v16_out = IoBigEndianGet16(&v16_in);
    v32_out = IoBigEndianGet32(&v32_in);
    v64_out = IoBigEndianGet64(&v64_in);

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckGetLittle(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;

    v8_out  = IoLittleEndianGet8(&v8_in);
    v16_out = IoLittleEndianGet16(&v16_in);
    v32_out = IoLittleEndianGet32(&v32_in);
    v64_out = IoLittleEndianGet64(&v64_in);

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckPutBig(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;

    IoBigEndianPut8(&v8_out,   v8_in);
    IoBigEndianPut16(&v16_out, v16_in);
    IoBigEndianPut32(&v32_out, v32_in);
    IoBigEndianPut64(&v64_out, v64_in);

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckPutLittle(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;

    IoLittleEndianPut8(&v8_out,   v8_in);
    IoLittleEndianPut16(&v16_out, v16_in);
    IoLittleEndianPut32(&v32_out, v32_in);
    IoLittleEndianPut64(&v64_out, v64_in);

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckReadBig(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in   = MAGIC8;
    const uint16_t v16_in  = MAGIC16;
    const uint32_t v32_in  = MAGIC32;
    const uint64_t v64_in  = MAGIC64;
    const void     *p8_in  = &v8_in;
    const void     *p16_in = &v16_in;
    const void     *p32_in = &v32_in;
    const void     *p64_in = &v64_in;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;

    v8_out  = IoBigEndianRead8(&p8_in);
    v16_out = IoBigEndianRead16(&p16_in);
    v32_out = IoBigEndianRead32(&p32_in);
    v64_out = IoBigEndianRead64(&p64_in);

    NL_TEST_ASSERT(inSuite, p8_in == (&v8_in + 1));
    NL_TEST_ASSERT(inSuite, p16_in == (&v16_in + 1));
    NL_TEST_ASSERT(inSuite, p32_in == (&v32_in + 1));
    NL_TEST_ASSERT(inSuite, p64_in == (&v64_in + 1));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckReadLittle(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in   = MAGIC8;
    const uint16_t v16_in  = MAGIC16;
    const uint32_t v32_in  = MAGIC32;
    const uint64_t v64_in  = MAGIC64;
    const void     *p8_in  = &v8_in;
    const void     *p16_in = &v16_in;
    const void     *p32_in = &v32_in;
    const void     *p64_in = &v64_in;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;

    v8_out  = IoLittleEndianRead8(&p8_in);
    v16_out = IoLittleEndianRead16(&p16_in);
    v32_out = IoLittleEndianRead32(&p32_in);
    v64_out = IoLittleEndianRead64(&p64_in);

    NL_TEST_ASSERT(inSuite, p8_in == (&v8_in + 1));
    NL_TEST_ASSERT(inSuite, p16_in == (&v16_in + 1));
    NL_TEST_ASSERT(inSuite, p32_in == (&v32_in + 1));
    NL_TEST_ASSERT(inSuite, p64_in == (&v64_in + 1));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckWriteBig(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in   = MAGIC8;
    const uint16_t v16_in  = MAGIC16;
    const uint32_t v32_in  = MAGIC32;
    const uint64_t v64_in  = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;
    void           *p8_out  = &v8_out;
    void           *p16_out = &v16_out;
    void           *p32_out = &v32_out;
    void           *p64_out = &v64_out;

    IoBigEndianWrite8(&p8_out, v8_in);
    IoBigEndianWrite16(&p16_out, v16_in);
    IoBigEndianWrite32(&p32_out, v32_in);
    IoBigEndianWrite64(&p64_out, v64_in);

    NL_TEST_ASSERT(inSuite, p8_out == (&v8_out + 1));
    NL_TEST_ASSERT(inSuite, p16_out == (&v16_out + 1));
    NL_TEST_ASSERT(inSuite, p32_out == (&v32_out + 1));
    NL_TEST_ASSERT(inSuite, p64_out == (&v64_out + 1));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckWriteLittle(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in   = MAGIC8;
    const uint16_t v16_in  = MAGIC16;
    const uint32_t v32_in  = MAGIC32;
    const uint64_t v64_in  = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;
    void           *p8_out  = &v8_out;
    void           *p16_out = &v16_out;
    void           *p32_out = &v32_out;
    void           *p64_out = &v64_out;

    IoLittleEndianWrite8(&p8_out, v8_in);
    IoLittleEndianWrite16(&p16_out, v16_in);
    IoLittleEndianWrite32(&p32_out, v32_in);
    IoLittleEndianWrite64(&p64_out, v64_in);

    NL_TEST_ASSERT(inSuite, p8_out == (&v8_out + 1));
    NL_TEST_ASSERT(inSuite, p16_out == (&v16_out + 1));
    NL_TEST_ASSERT(inSuite, p32_out == (&v32_out + 1));
    NL_TEST_ASSERT(inSuite, p64_out == (&v64_out + 1));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckGetBigAligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;

    v8_out  = IoBigEndianGetAligned8(&v8_in);
    v16_out = IoBigEndianGetAligned16(&v16_in);
    v32_out = IoBigEndianGetAligned32(&v32_in);
    v64_out = IoBigEndianGetAligned64(&v64_in);

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckGetLittleAligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;

    v8_out  = IoLittleEndianGetAligned8(&v8_in);
    v16_out = IoLittleEndianGetAligned16(&v16_in);
    v32_out = IoLittleEndianGetAligned32(&v32_in);
    v64_out = IoLittleEndianGetAligned64(&v64_in);

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckPutBigAligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;

    IoBigEndianPutAligned8(&v8_out,   v8_in);
    IoBigEndianPutAligned16(&v16_out, v16_in);
    IoBigEndianPutAligned32(&v32_out, v32_in);
    IoBigEndianPutAligned64(&v64_out, v64_in);

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckPutLittleAligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;

    IoLittleEndianPutAligned8(&v8_out,   v8_in);
    IoLittleEndianPutAligned16(&v16_out, v16_in);
    IoLittleEndianPutAligned32(&v32_out, v32_in);
    IoLittleEndianPutAligned64(&v64_out, v64_in);

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckReadBigAligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in   = MAGIC8;
    const uint16_t v16_in  = MAGIC16;
    const uint32_t v32_in  = MAGIC32;
    const uint64_t v64_in  = MAGIC64;
    const void     *p8_in  = &v8_in;
    const void     *p16_in = &v16_in;
    const void     *p32_in = &v32_in;
    const void     *p64_in = &v64_in;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;

    v8_out  = IoBigEndianReadAligned8(&p8_in);
    v16_out = IoBigEndianReadAligned16(&p16_in);
    v32_out = IoBigEndianReadAligned32(&p32_in);
    v64_out = IoBigEndianReadAligned64(&p64_in);

    NL_TEST_ASSERT(inSuite, p8_in == (&v8_in + 1));
    NL_TEST_ASSERT(inSuite, p16_in == (&v16_in + 1));
    NL_TEST_ASSERT(inSuite, p32_in == (&v32_in + 1));
    NL_TEST_ASSERT(inSuite, p64_in == (&v64_in + 1));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckReadLittleAligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in   = MAGIC8;
    const uint16_t v16_in  = MAGIC16;
    const uint32_t v32_in  = MAGIC32;
    const uint64_t v64_in  = MAGIC64;
    const void     *p8_in  = &v8_in;
    const void     *p16_in = &v16_in;
    const void     *p32_in = &v32_in;
    const void     *p64_in = &v64_in;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;

    v8_out  = IoLittleEndianReadAligned8(&p8_in);
    v16_out = IoLittleEndianReadAligned16(&p16_in);
    v32_out = IoLittleEndianReadAligned32(&p32_in);
    v64_out = IoLittleEndianReadAligned64(&p64_in);

    NL_TEST_ASSERT(inSuite, p8_in == (&v8_in + 1));
    NL_TEST_ASSERT(inSuite, p16_in == (&v16_in + 1));
    NL_TEST_ASSERT(inSuite, p32_in == (&v32_in + 1));
    NL_TEST_ASSERT(inSuite, p64_in == (&v64_in + 1));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckWriteBigAligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in   = MAGIC8;
    const uint16_t v16_in  = MAGIC16;
    const uint32_t v32_in  = MAGIC32;
    const uint64_t v64_in  = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;
    void           *p8_out  = &v8_out;
    void           *p16_out = &v16_out;
    void           *p32_out = &v32_out;
    void           *p64_out = &v64_out;

    IoBigEndianWriteAligned8(&p8_out, v8_in);
    IoBigEndianWriteAligned16(&p16_out, v16_in);
    IoBigEndianWriteAligned32(&p32_out, v32_in);
    IoBigEndianWriteAligned64(&p64_out, v64_in);

    NL_TEST_ASSERT(inSuite, p8_out == (&v8_out + 1));
    NL_TEST_ASSERT(inSuite, p16_out == (&v16_out + 1));
    NL_TEST_ASSERT(inSuite, p32_out == (&v32_out + 1));
    NL_TEST_ASSERT(inSuite, p64_out == (&v64_out + 1));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckWriteLittleAligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in   = MAGIC8;
    const uint16_t v16_in  = MAGIC16;
    const uint32_t v32_in  = MAGIC32;
    const uint64_t v64_in  = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_out;
    uint32_t       v32_out;
    uint64_t       v64_out;
    void           *p8_out  = &v8_out;
    void           *p16_out = &v16_out;
    void           *p32_out = &v32_out;
    void           *p64_out = &v64_out;

    IoLittleEndianWriteAligned8(&p8_out, v8_in);
    IoLittleEndianWriteAligned16(&p16_out, v16_in);
    IoLittleEndianWriteAligned32(&p32_out, v32_in);
    IoLittleEndianWriteAligned64(&p64_out, v64_in);

    NL_TEST_ASSERT(inSuite, p8_out == (&v8_out + 1));
    NL_TEST_ASSERT(inSuite, p16_out == (&v16_out + 1));
    NL_TEST_ASSERT(inSuite, p32_out == (&v32_out + 1));
    NL_TEST_ASSERT(inSuite, p64_out == (&v64_out + 1));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out  == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_out == MAGIC_SWAP64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

// XXX - Unaligned

static void CheckGetBigUnaligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_0_out;
    uint16_t       v16_1_out;
    uint32_t       v32_0_out;
    uint32_t       v32_1_out;
    uint32_t       v32_2_out;
    uint32_t       v32_3_out;
    uint64_t       v64_0_out;
    uint64_t       v64_1_out;
    uint64_t       v64_2_out;
    uint64_t       v64_3_out;
    uint64_t       v64_4_out;
    uint64_t       v64_5_out;
    uint64_t       v64_6_out;
    uint64_t       v64_7_out;
    uint8_t        buffer[sizeof(uint64_t) * 2];
    void *         p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    memcpy(p, &v8_in, sizeof(v8_in));

    v8_out = IoBigEndianGetUnaligned8(p);

    // Try 16-bit quantities.

    p = &buffer[0];
    memcpy(p, &v16_in, sizeof(v16_in));

    v16_0_out = IoBigEndianGetUnaligned16(p);

    p = &buffer[1];
    memcpy(p, &v16_in, sizeof(v16_in));

    v16_1_out = IoBigEndianGetUnaligned16(p);

    // Try 32-bit quantities.

    p = &buffer[0];
    memcpy(p, &v32_in, sizeof(v32_in));

    v32_0_out = IoBigEndianGetUnaligned32(p);

    p = &buffer[1];
    memcpy(p, &v32_in, sizeof(v32_in));

    v32_1_out = IoBigEndianGetUnaligned32(p);

    p = &buffer[2];
    memcpy(p, &v32_in, sizeof(v32_in));

    v32_2_out = IoBigEndianGetUnaligned32(p);

    p = &buffer[3];
    memcpy(p, &v32_in, sizeof(v32_in));

    v32_3_out = IoBigEndianGetUnaligned32(p);

    // Try 64-bit quantities.

    p = &buffer[0];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_0_out = IoBigEndianGetUnaligned64(p);

    p = &buffer[1];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_1_out = IoBigEndianGetUnaligned64(p);

    p = &buffer[2];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_2_out = IoBigEndianGetUnaligned64(p);

    p = &buffer[3];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_3_out = IoBigEndianGetUnaligned64(p);

    p = &buffer[4];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_4_out = IoBigEndianGetUnaligned64(p);

    p = &buffer[5];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_5_out = IoBigEndianGetUnaligned64(p);

    p = &buffer[6];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_6_out = IoBigEndianGetUnaligned64(p);

    p = &buffer[7];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_7_out = IoBigEndianGetUnaligned64(p);

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC_SWAP64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckGetLittleUnaligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_0_out;
    uint16_t       v16_1_out;
    uint32_t       v32_0_out;
    uint32_t       v32_1_out;
    uint32_t       v32_2_out;
    uint32_t       v32_3_out;
    uint64_t       v64_0_out;
    uint64_t       v64_1_out;
    uint64_t       v64_2_out;
    uint64_t       v64_3_out;
    uint64_t       v64_4_out;
    uint64_t       v64_5_out;
    uint64_t       v64_6_out;
    uint64_t       v64_7_out;
    uint8_t        buffer[sizeof(uint64_t) * 2];
    void *         p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    memcpy(p, &v8_in, sizeof(v8_in));

    v8_out = IoLittleEndianGetUnaligned8(p);

    // Try 16-bit quantities.

    p = &buffer[0];
    memcpy(p, &v16_in, sizeof(v16_in));

    v16_0_out = IoLittleEndianGetUnaligned16(p);

    p = &buffer[1];
    memcpy(p, &v16_in, sizeof(v16_in));

    v16_1_out = IoLittleEndianGetUnaligned16(p);

    // Try 32-bit quantities.

    p = &buffer[0];
    memcpy(p, &v32_in, sizeof(v32_in));

    v32_0_out = IoLittleEndianGetUnaligned32(p);

    p = &buffer[1];
    memcpy(p, &v32_in, sizeof(v32_in));

    v32_1_out = IoLittleEndianGetUnaligned32(p);

    p = &buffer[2];
    memcpy(p, &v32_in, sizeof(v32_in));

    v32_2_out = IoLittleEndianGetUnaligned32(p);

    p = &buffer[3];
    memcpy(p, &v32_in, sizeof(v32_in));

    v32_3_out = IoLittleEndianGetUnaligned32(p);

    // Try 64-bit quantities.

    p = &buffer[0];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_0_out = IoLittleEndianGetUnaligned64(p);

    p = &buffer[1];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_1_out = IoLittleEndianGetUnaligned64(p);

    p = &buffer[2];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_2_out = IoLittleEndianGetUnaligned64(p);

    p = &buffer[3];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_3_out = IoLittleEndianGetUnaligned64(p);

    p = &buffer[4];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_4_out = IoLittleEndianGetUnaligned64(p);

    p = &buffer[5];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_5_out = IoLittleEndianGetUnaligned64(p);

    p = &buffer[6];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_6_out = IoLittleEndianGetUnaligned64(p);

    p = &buffer[7];
    memcpy(p, &v64_in, sizeof(v64_in));

    v64_7_out = IoLittleEndianGetUnaligned64(p);

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC_SWAP64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckPutBigUnaligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_0_out;
    uint16_t       v16_1_out;
    uint32_t       v32_0_out;
    uint32_t       v32_1_out;
    uint32_t       v32_2_out;
    uint32_t       v32_3_out;
    uint64_t       v64_0_out;
    uint64_t       v64_1_out;
    uint64_t       v64_2_out;
    uint64_t       v64_3_out;
    uint64_t       v64_4_out;
    uint64_t       v64_5_out;
    uint64_t       v64_6_out;
    uint64_t       v64_7_out;
    uint8_t        buffer[sizeof(uint64_t) * 2];
    void *         p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    IoBigEndianPutUnaligned8(p, v8_in);
    memcpy(&v8_out, p, sizeof(v8_in));

    // Try 16-bit quantities.

    p = &buffer[0];
    IoBigEndianPutUnaligned16(p, v16_in);
    memcpy(&v16_0_out, p, sizeof(v16_in));

    p = &buffer[1];
    IoBigEndianPutUnaligned16(p, v16_in);
    memcpy(&v16_1_out, p, sizeof(v16_in));

    // Try 32-bit quantities.

    p = &buffer[0];
    IoBigEndianPutUnaligned32(p, v32_in);
    memcpy(&v32_0_out, p, sizeof(v32_in));

    p = &buffer[1];
    IoBigEndianPutUnaligned32(p, v32_in);
    memcpy(&v32_1_out, p, sizeof(v32_in));

    p = &buffer[2];
    IoBigEndianPutUnaligned32(p, v32_in);
    memcpy(&v32_2_out, p, sizeof(v32_in));

    p = &buffer[3];
    IoBigEndianPutUnaligned32(p, v32_in);
    memcpy(&v32_3_out, p, sizeof(v32_in));

    // Try 64-bit quantities.

    p = &buffer[0];
    IoBigEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_0_out, p, sizeof(v64_in));

    p = &buffer[1];
    IoBigEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_1_out, p, sizeof(v64_in));

    p = &buffer[2];
    IoBigEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_2_out, p, sizeof(v64_in));

    p = &buffer[3];
    IoBigEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_3_out, p, sizeof(v64_in));

    p = &buffer[4];
    IoBigEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_4_out, p, sizeof(v64_in));

    p = &buffer[5];
    IoBigEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_5_out, p, sizeof(v64_in));

    p = &buffer[6];
    IoBigEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_6_out, p, sizeof(v64_in));

    p = &buffer[7];
    IoBigEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_7_out, p, sizeof(v64_in));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC_SWAP64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckPutLittleUnaligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_0_out;
    uint16_t       v16_1_out;
    uint32_t       v32_0_out;
    uint32_t       v32_1_out;
    uint32_t       v32_2_out;
    uint32_t       v32_3_out;
    uint64_t       v64_0_out;
    uint64_t       v64_1_out;
    uint64_t       v64_2_out;
    uint64_t       v64_3_out;
    uint64_t       v64_4_out;
    uint64_t       v64_5_out;
    uint64_t       v64_6_out;
    uint64_t       v64_7_out;
    uint8_t        buffer[sizeof(uint64_t) * 2];
    void *         p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    IoLittleEndianPutUnaligned8(p, v8_in);
    memcpy(&v8_out, p, sizeof(v8_in));

    // Try 16-bit quantities.

    p = &buffer[0];
    IoLittleEndianPutUnaligned16(p, v16_in);
    memcpy(&v16_0_out, p, sizeof(v16_in));

    p = &buffer[1];
    IoLittleEndianPutUnaligned16(p, v16_in);
    memcpy(&v16_1_out, p, sizeof(v16_in));

    // Try 32-bit quantities.

    p = &buffer[0];
    IoLittleEndianPutUnaligned32(p, v32_in);
    memcpy(&v32_0_out, p, sizeof(v32_in));

    p = &buffer[1];
    IoLittleEndianPutUnaligned32(p, v32_in);
    memcpy(&v32_1_out, p, sizeof(v32_in));

    p = &buffer[2];
    IoLittleEndianPutUnaligned32(p, v32_in);
    memcpy(&v32_2_out, p, sizeof(v32_in));

    p = &buffer[3];
    IoLittleEndianPutUnaligned32(p, v32_in);
    memcpy(&v32_3_out, p, sizeof(v32_in));

    // Try 64-bit quantities.

    p = &buffer[0];
    IoLittleEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_0_out, p, sizeof(v64_in));

    p = &buffer[1];
    IoLittleEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_1_out, p, sizeof(v64_in));

    p = &buffer[2];
    IoLittleEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_2_out, p, sizeof(v64_in));

    p = &buffer[3];
    IoLittleEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_3_out, p, sizeof(v64_in));

    p = &buffer[4];
    IoLittleEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_4_out, p, sizeof(v64_in));

    p = &buffer[5];
    IoLittleEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_5_out, p, sizeof(v64_in));

    p = &buffer[6];
    IoLittleEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_6_out, p, sizeof(v64_in));

    p = &buffer[7];
    IoLittleEndianPutUnaligned64(p, v64_in);
    memcpy(&v64_7_out, p, sizeof(v64_in));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC_SWAP64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckReadBigUnaligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_0_out;
    uint16_t       v16_1_out;
    uint32_t       v32_0_out;
    uint32_t       v32_1_out;
    uint32_t       v32_2_out;
    uint32_t       v32_3_out;
    uint64_t       v64_0_out;
    uint64_t       v64_1_out;
    uint64_t       v64_2_out;
    uint64_t       v64_3_out;
    uint64_t       v64_4_out;
    uint64_t       v64_5_out;
    uint64_t       v64_6_out;
    uint64_t       v64_7_out;
    uint8_t        buffer[sizeof(uint64_t) * 2];
    const void *   p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    memcpy(&buffer[0], &v8_in, sizeof(v8_in));

    v8_out = IoBigEndianReadUnaligned8((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v8_in));

    // Try 16-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &v16_in, sizeof(v16_in));

    v16_0_out = IoBigEndianReadUnaligned16((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v16_in));

    p = &buffer[1];
    memcpy(&buffer[1], &v16_in, sizeof(v16_in));

    v16_1_out = IoBigEndianReadUnaligned16((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(v16_in));

    // Try 32-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &v32_in, sizeof(v32_in));

    v32_0_out = IoBigEndianReadUnaligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v32_in));

    p = &buffer[1];
    memcpy(&buffer[1], &v32_in, sizeof(v32_in));

    v32_1_out = IoBigEndianReadUnaligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(v32_in));

    p = &buffer[2];
    memcpy(&buffer[2], &v32_in, sizeof(v32_in));

    v32_2_out = IoBigEndianReadUnaligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(v32_in));

    p = &buffer[3];
    memcpy(&buffer[3], &v32_in, sizeof(v32_in));

    v32_3_out = IoBigEndianReadUnaligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(v32_in));

    // Try 64-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &v64_in, sizeof(v64_in));

    v64_0_out = IoBigEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v64_in));

    p = &buffer[1];
    memcpy(&buffer[1], &v64_in, sizeof(v64_in));

    v64_1_out = IoBigEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(v64_in));

    p = &buffer[2];
    memcpy(&buffer[2], &v64_in, sizeof(v64_in));

    v64_2_out = IoBigEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(v64_in));

    p = &buffer[3];
    memcpy(&buffer[3], &v64_in, sizeof(v64_in));

    v64_3_out = IoBigEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(v64_in));

    p = &buffer[4];
    memcpy(&buffer[4], &v64_in, sizeof(v64_in));

    v64_4_out = IoBigEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[4] + sizeof(v64_in));

    p = &buffer[5];
    memcpy(&buffer[5], &v64_in, sizeof(v64_in));

    v64_5_out = IoBigEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[5] + sizeof(v64_in));

    p = &buffer[6];
    memcpy(&buffer[6], &v64_in, sizeof(v64_in));

    v64_6_out = IoBigEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[6] + sizeof(v64_in));

    p = &buffer[7];
    memcpy(&buffer[7], &v64_in, sizeof(v64_in));

    v64_7_out = IoBigEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[7] + sizeof(v64_in));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC_SWAP64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckReadLittleUnaligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in  = MAGIC8;
    const uint16_t v16_in = MAGIC16;
    const uint32_t v32_in = MAGIC32;
    const uint64_t v64_in = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_0_out;
    uint16_t       v16_1_out;
    uint32_t       v32_0_out;
    uint32_t       v32_1_out;
    uint32_t       v32_2_out;
    uint32_t       v32_3_out;
    uint64_t       v64_0_out;
    uint64_t       v64_1_out;
    uint64_t       v64_2_out;
    uint64_t       v64_3_out;
    uint64_t       v64_4_out;
    uint64_t       v64_5_out;
    uint64_t       v64_6_out;
    uint64_t       v64_7_out;
    uint8_t        buffer[sizeof(uint64_t) * 2];
    const void *   p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    memcpy(&buffer[0], &v8_in, sizeof(v8_in));

    v8_out = IoLittleEndianReadUnaligned8((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v8_in));

    // Try 16-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &v16_in, sizeof(v16_in));

    v16_0_out = IoLittleEndianReadUnaligned16((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v16_in));

    p = &buffer[1];
    memcpy(&buffer[1], &v16_in, sizeof(v16_in));

    v16_1_out = IoLittleEndianReadUnaligned16((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(v16_in));

    // Try 32-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &v32_in, sizeof(v32_in));

    v32_0_out = IoLittleEndianReadUnaligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v32_in));

    p = &buffer[1];
    memcpy(&buffer[1], &v32_in, sizeof(v32_in));

    v32_1_out = IoLittleEndianReadUnaligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(v32_in));

    p = &buffer[2];
    memcpy(&buffer[2], &v32_in, sizeof(v32_in));

    v32_2_out = IoLittleEndianReadUnaligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(v32_in));

    p = &buffer[3];
    memcpy(&buffer[3], &v32_in, sizeof(v32_in));

    v32_3_out = IoLittleEndianReadUnaligned32((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(v32_in));

    // Try 64-bit quantities.

    p = &buffer[0];
    memcpy(&buffer[0], &v64_in, sizeof(v64_in));

    v64_0_out = IoLittleEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v64_in));

    p = &buffer[1];
    memcpy(&buffer[1], &v64_in, sizeof(v64_in));

    v64_1_out = IoLittleEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(v64_in));

    p = &buffer[2];
    memcpy(&buffer[2], &v64_in, sizeof(v64_in));

    v64_2_out = IoLittleEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(v64_in));

    p = &buffer[3];
    memcpy(&buffer[3], &v64_in, sizeof(v64_in));

    v64_3_out = IoLittleEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(v64_in));

    p = &buffer[4];
    memcpy(&buffer[4], &v64_in, sizeof(v64_in));

    v64_4_out = IoLittleEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[4] + sizeof(v64_in));

    p = &buffer[5];
    memcpy(&buffer[5], &v64_in, sizeof(v64_in));

    v64_5_out = IoLittleEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[5] + sizeof(v64_in));

    p = &buffer[6];
    memcpy(&buffer[6], &v64_in, sizeof(v64_in));

    v64_6_out = IoLittleEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[6] + sizeof(v64_in));

    p = &buffer[7];
    memcpy(&buffer[7], &v64_in, sizeof(v64_in));

    v64_7_out = IoLittleEndianReadUnaligned64((const void **)&p);
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[7] + sizeof(v64_in));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC_SWAP64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckWriteBigUnaligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in   = MAGIC8;
    const uint16_t v16_in  = MAGIC16;
    const uint32_t v32_in  = MAGIC32;
    const uint64_t v64_in  = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_0_out;
    uint16_t       v16_1_out;
    uint32_t       v32_0_out;
    uint32_t       v32_1_out;
    uint32_t       v32_2_out;
    uint32_t       v32_3_out;
    uint64_t       v64_0_out;
    uint64_t       v64_1_out;
    uint64_t       v64_2_out;
    uint64_t       v64_3_out;
    uint64_t       v64_4_out;
    uint64_t       v64_5_out;
    uint64_t       v64_6_out;
    uint64_t       v64_7_out;
    uint8_t        buffer[sizeof(uint64_t) * 2];
    void *         p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    IoBigEndianWriteUnaligned8(&p, v8_in);
    memcpy(&v8_out, &buffer[0], sizeof(v8_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v8_out));

    // Try 16-bit quantities.

    p = &buffer[0];
    IoBigEndianWriteUnaligned16(&p, v16_in);
    memcpy(&v16_0_out, &buffer[0], sizeof(v16_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v16_0_out));

    p = &buffer[1];
    IoBigEndianWriteUnaligned16(&p, v16_in);
    memcpy(&v16_1_out, &buffer[1], sizeof(v16_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(v16_1_out));

    // Try 32-bit quantities.

    p = &buffer[0];
    IoBigEndianWriteUnaligned32(&p, v32_in);
    memcpy(&v32_0_out, &buffer[0], sizeof(v32_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v32_0_out));

    p = &buffer[1];
    IoBigEndianWriteUnaligned32(&p, v32_in);
    memcpy(&v32_1_out, &buffer[1], sizeof(v32_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(v32_1_out));

    p = &buffer[2];
    IoBigEndianWriteUnaligned32(&p, v32_in);
    memcpy(&v32_2_out, &buffer[2], sizeof(v32_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(v32_2_out));

    p = &buffer[3];
    IoBigEndianWriteUnaligned32(&p, v32_in);
    memcpy(&v32_3_out, &buffer[3], sizeof(v32_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(v32_3_out));

    // Try 64-bit quantities.

    p = &buffer[0];
    IoBigEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_0_out, &buffer[0], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v64_0_out));

    p = &buffer[1];
    IoBigEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_1_out, &buffer[1], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(v64_1_out));

    p = &buffer[2];
    IoBigEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_2_out, &buffer[2], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(v64_2_out));

    p = &buffer[3];
    IoBigEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_3_out, &buffer[3], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(v64_3_out));

    p = &buffer[4];
    IoBigEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_4_out, &buffer[4], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[4] + sizeof(v64_4_out));

    p = &buffer[5];
    IoBigEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_5_out, &buffer[5], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[5] + sizeof(v64_5_out));

    p = &buffer[6];
    IoBigEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_6_out, &buffer[6], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[6] + sizeof(v64_6_out));

    p = &buffer[7];
    IoBigEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_7_out, &buffer[7], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[7] + sizeof(v64_7_out));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC_SWAP64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static void CheckWriteLittleUnaligned(nlTestSuite *inSuite, void *inContext)
{
    const uint8_t  v8_in   = MAGIC8;
    const uint16_t v16_in  = MAGIC16;
    const uint32_t v32_in  = MAGIC32;
    const uint64_t v64_in  = MAGIC64;
    uint8_t        v8_out;
    uint16_t       v16_0_out;
    uint16_t       v16_1_out;
    uint32_t       v32_0_out;
    uint32_t       v32_1_out;
    uint32_t       v32_2_out;
    uint32_t       v32_3_out;
    uint64_t       v64_0_out;
    uint64_t       v64_1_out;
    uint64_t       v64_2_out;
    uint64_t       v64_3_out;
    uint64_t       v64_4_out;
    uint64_t       v64_5_out;
    uint64_t       v64_6_out;
    uint64_t       v64_7_out;
    uint8_t        buffer[sizeof(uint64_t) * 2];
    void *         p;

    // Try an 8-bit quantity. They are aligned anywhere and unaligned
    // nowhere.

    p = &buffer[0];
    IoLittleEndianWriteUnaligned8(&p, v8_in);
    memcpy(&v8_out, &buffer[0], sizeof(v8_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v8_out));

    // Try 16-bit quantities.

    p = &buffer[0];
    IoLittleEndianWriteUnaligned16(&p, v16_in);
    memcpy(&v16_0_out, &buffer[0], sizeof(v16_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v16_0_out));

    p = &buffer[1];
    IoLittleEndianWriteUnaligned16(&p, v16_in);
    memcpy(&v16_1_out, &buffer[1], sizeof(v16_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(v16_1_out));

    // Try 32-bit quantities.

    p = &buffer[0];
    IoLittleEndianWriteUnaligned32(&p, v32_in);
    memcpy(&v32_0_out, &buffer[0], sizeof(v32_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v32_0_out));

    p = &buffer[1];
    IoLittleEndianWriteUnaligned32(&p, v32_in);
    memcpy(&v32_1_out, &buffer[1], sizeof(v32_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(v32_1_out));

    p = &buffer[2];
    IoLittleEndianWriteUnaligned32(&p, v32_in);
    memcpy(&v32_2_out, &buffer[2], sizeof(v32_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(v32_2_out));

    p = &buffer[3];
    IoLittleEndianWriteUnaligned32(&p, v32_in);
    memcpy(&v32_3_out, &buffer[3], sizeof(v32_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(v32_3_out));

    // Try 64-bit quantities.

    p = &buffer[0];
    IoLittleEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_0_out, &buffer[0], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[0] + sizeof(v64_0_out));

    p = &buffer[1];
    IoLittleEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_1_out, &buffer[1], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[1] + sizeof(v64_1_out));

    p = &buffer[2];
    IoLittleEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_2_out, &buffer[2], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[2] + sizeof(v64_2_out));

    p = &buffer[3];
    IoLittleEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_3_out, &buffer[3], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[3] + sizeof(v64_3_out));

    p = &buffer[4];
    IoLittleEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_4_out, &buffer[4], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[4] + sizeof(v64_4_out));

    p = &buffer[5];
    IoLittleEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_5_out, &buffer[5], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[5] + sizeof(v64_5_out));

    p = &buffer[6];
    IoLittleEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_6_out, &buffer[6], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[6] + sizeof(v64_6_out));

    p = &buffer[7];
    IoLittleEndianWriteUnaligned64(&p, v64_in);
    memcpy(&v64_7_out, &buffer[7], sizeof(v64_in));
    NL_TEST_ASSERT(inSuite, p == (uint8_t *)&buffer[7] + sizeof(v64_7_out));

#if MATTER_BYTEORDER == MATTER_BYTEORDER_LITTLE_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC64);

#elif MATTER_BYTEORDER == MATTER_BYTEORDER_BIG_ENDIAN
    NL_TEST_ASSERT(inSuite, v8_out    == MAGIC_SWAP8);
    NL_TEST_ASSERT(inSuite, v16_0_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v16_1_out == MAGIC_SWAP16);
    NL_TEST_ASSERT(inSuite, v32_0_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_1_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_2_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v32_3_out == MAGIC_SWAP32);
    NL_TEST_ASSERT(inSuite, v64_0_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_1_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_2_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_3_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_4_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_5_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_6_out == MAGIC_SWAP64);
    NL_TEST_ASSERT(inSuite, v64_7_out == MAGIC_SWAP64);

#else
    NL_TEST_ASSERT(inSuite, false);

#endif
}

static const nlTest sTests[] = {
    NL_TEST_DEF("get big",                CheckGetBig),
    NL_TEST_DEF("get little",             CheckGetLittle),
    NL_TEST_DEF("put big",                CheckPutBig),
    NL_TEST_DEF("put little",             CheckPutLittle),
    NL_TEST_DEF("read big",               CheckReadBig),
    NL_TEST_DEF("read little",            CheckReadLittle),
    NL_TEST_DEF("write big",              CheckWriteBig),
    NL_TEST_DEF("write little",           CheckWriteLittle),
    NL_TEST_DEF("get big aligned",        CheckGetBigAligned),
    NL_TEST_DEF("get little aligned",     CheckGetLittleAligned),
    NL_TEST_DEF("put big aligned",        CheckPutBigAligned),
    NL_TEST_DEF("put little aligned",     CheckPutLittleAligned),
    NL_TEST_DEF("read big aligned",       CheckReadBigAligned),
    NL_TEST_DEF("read little aligned",    CheckReadLittleAligned),
    NL_TEST_DEF("write big aligned",      CheckWriteBigAligned),
    NL_TEST_DEF("write little aligned",   CheckWriteLittleAligned),
    NL_TEST_DEF("get big unaligned",      CheckGetBigUnaligned),
    NL_TEST_DEF("get little unaligned",   CheckGetLittleUnaligned),
    NL_TEST_DEF("put big unaligned",      CheckPutBigUnaligned),
    NL_TEST_DEF("put little unaligned",   CheckPutLittleUnaligned),
    NL_TEST_DEF("read big unaligned",     CheckReadBigUnaligned),
    NL_TEST_DEF("read little unaligned",  CheckReadLittleUnaligned),
    NL_TEST_DEF("write big unaligned",    CheckWriteBigUnaligned),
    NL_TEST_DEF("write little unaligned", CheckWriteLittleUnaligned),

    NL_TEST_SENTINEL()
};

int TestIoByteOrder(void)
{
    nlTestSuite theSuite = {
        "IO ByteOrder tests",
        &sTests[0]
    };

    nlTestRunner(&theSuite, NULL);
    return nlTestRunnerStats(&theSuite);
}
