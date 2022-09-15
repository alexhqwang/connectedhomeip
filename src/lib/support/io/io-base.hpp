/**
 *    Copyright (c) 2022 Project CHIP Authors
 *    Copyright 2013-2016 Nest Labs Inc. All Rights Reserved.
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
 *      This file defines C++ functions for safely performing simple,
 *      memory-mapped accesses, potentially to unaligned memory
 *      locations.
 */

#pragma once

#include <lib/support/io/io-base.h>

namespace chip {
namespace IO {

/**
 * This determines whether the specified pointer is aligned on the
 * indicated size boundary.
 *
 * @note The size should be a power of 2 (e.g. 1, 2, 4, 8, 16, etc.).
 *
 * @param[in]  p     The pointer to check the alignment of.
 * @param[in]  size  The size, in bytes, boundary to check
 *                   the alignment against.
 *
 * @return True if the pointer is aligned to the specified size;
 *         otherwise, false.
 */
static inline bool IsAligned(const void *p, size_t size)
{
    return IoIsAligned(p, size);
}

/**
 * This determines whether the specified pointer is aligned on the
 * size boundary for the template type, T.
 *
 * @tparam     T     The type of pointer to check the alignment of.
 *
 * @param[in]  p     The pointer to check the alignment of.
 *
 * @return True if the pointer is aligned to size of the type;
 *         otherwise, false.
 */
template <typename T>
static inline bool IsAligned(const T *p)
{
    return IoIsAligned(p, sizeof(T));
}

/**
 * Perform an aligned memory read of the 8-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 8-bit value from.
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  GetAligned8(const void *p)
{
    return IoGetAligned8(p);
}

/**
 * Perform an aligned memory read of the 16-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 16-bit value from.
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t GetAligned16(const void *p)
{
    return IoGetAligned16(p);
}

/**
 * Perform an aligned memory read of the 32-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 32-bit value from.
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t GetAligned32(const void *p)
{
    return IoGetAligned32(p);
}

/**
 * Perform an aligned memory read of the 64-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 64-bit value from.
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t GetAligned64(const void *p)
{
    return IoGetAligned64(p);
}

/**
 * Perform an unaligned memory read of the 8-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 8-bit value from.
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  GetUnaligned8(const void *p)
{
    return IoGetUnaligned8(p);
}

/**
 * Perform an unaligned memory read of the 16-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 16-bit value from.
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t GetUnaligned16(const void *p)
{
    return IoGetUnaligned16(p);
}

/**
 * Perform an unaligned memory read of the 32-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 32-bit value from.
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t GetUnaligned32(const void *p)
{
    return IoGetUnaligned32(p);
}

/**
 * Perform an unaligned memory read of the 64-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 64-bit value from.
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t GetUnaligned64(const void *p)
{
    return IoGetUnaligned64(p);
}

/**
 * Perform a, potentially unaligned, memory read of the 8-bit value
 * from the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 8-bit value from.
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  GetMaybeAligned8(const void *p)
{
    return IoGetMaybeAligned8(p);
}

/**
 * Perform a, potentially unaligned, memory read of the 16-bit value
 * from the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 16-bit value from.
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t GetMaybeAligned16(const void *p)
{
    return IoGetMaybeAligned16(p);
}

/**
 * Perform a, potentially unaligned, memory read of the 32-bit value
 * from the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 32-bit value from.
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t GetMaybeAligned32(const void *p)
{
    return IoGetMaybeAligned32(p);
}

/**
 * Perform a, potentially unaligned, memory read of the 64-bit value
 * from the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 64-bit value from.
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t GetMaybeAligned64(const void *p)
{
    return IoGetMaybeAligned64(p);
}

/**
 * Perform an aligned memory write of the 8-bit value to the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to write the 8-bit value to.
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     PutAligned8(void *p, const uint8_t v)
{
    IoPutAligned8(p, v);
}

/**
 * Perform an aligned memory write of the 16-bit value to the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to write the 16-bit value to.
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     PutAligned16(void *p, const uint16_t v)
{
    IoPutAligned16(p, v);
}

/**
 * Perform an aligned memory write of the 32-bit value to the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to write the 32-bit value to.
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     PutAligned32(void *p, const uint32_t v)
{
    IoPutAligned32(p, v);
}

/**
 * Perform an aligned memory write of the 64-bit value to the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to write the 64-bit value to.
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     PutAligned64(void *p, const uint64_t v)
{
    IoPutAligned64(p, v);
}

/**
 * Perform an unaligned memory write of the 8-bit value to the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to write the 8-bit value to.
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     PutUnaligned8(void *p, const uint8_t v)
{
    IoPutUnaligned8(p, v);
}

/**
 * Perform an unaligned memory write of the 16-bit value to the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to write the 16-bit value to.
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     PutUnaligned16(void *p, const uint16_t v)
{
    IoPutUnaligned16(p, v);
}

/**
 * Perform an unaligned memory write of the 32-bit value to the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to write the 32-bit value to.
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     PutUnaligned32(void *p, const uint32_t v)
{
    IoPutUnaligned32(p, v);
}

/**
 * Perform an unaligned memory write of the 64-bit value to the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to write the 64-bit value to.
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     PutUnaligned64(void *p, const uint64_t v)
{
    IoPutUnaligned64(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 8-bit value
 * to the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the 8-bit value to.
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     PutMaybeAligned8(void *p, const uint8_t v)
{
    IoPutMaybeAligned8(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 16-bit value
 * to the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the 16-bit value to.
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     PutMaybeAligned16(void *p, const uint16_t v)
{
    IoPutMaybeAligned16(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 32-bit value
 * to the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the 32-bit value to.
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     PutMaybeAligned32(void *p, const uint32_t v)
{
    IoPutMaybeAligned32(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 64-bit value
 * to the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the 64-bit value to.
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     PutMaybeAligned64(void *p, const uint64_t v)
{
    IoPutMaybeAligned64(p, v);
}

/**
 * Perform an aligned memory read of the 8-bit value at the specified
 * pointer address and increment the pointer by 8-bits (1 byte).
 *
 * @param[inout]  p   A reference to a pointer address to read the
 *                    8-bit value from and to then increment by
 *                    8-bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  ReadAligned8(const void *&p)
{
    return IoReadAligned8(&p);
}

/**
 * Perform an aligned memory read of the 16-bit value at the specified
 * pointer address and increment the pointer by 16-bits (2 bytes).
 *
 * @param[inout]  p   A reference to a pointer address to read the
 *                    16-bit value from and to then increment by
 *                    16-bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t ReadAligned16(const void *&p)
{
    return IoReadAligned16(&p);
}

/**
 * Perform an aligned memory read of the 32-bit value at the specified
 * pointer address and increment the pointer by 32-bits (4 bytes).
 *
 * @param[inout]  p   A reference to a pointer address to read the
 *                    32-bit value from and to then increment by
 *                    32-bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t ReadAligned32(const void *&p)
{
    return IoReadAligned32(&p);
}

/**
 * Perform an aligned memory read of the 64-bit value at the specified
 * pointer address and increment the pointer by 64-bits (8 bytes).
 *
 * @param[inout]  p   A reference to a pointer address to read the
 *                    64-bit value from and to then increment by
 *                    64-bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t ReadAligned64(const void *&p)
{
    return IoReadAligned64(&p);
}

/**
 * Perform an unaligned memory read of the 8-bit value at the specified
 * pointer address and increment the pointer by 8-bits (1 byte).
 *
 * @param[inout]  p   A reference to a pointer address to read the
 *                    8-bit value from and to then increment by
 *                    8-bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t ReadUnaligned8(const void *&p)
{
    return IoReadUnaligned8(&p);
}

/**
 * Perform an unaligned memory read of the 16-bit value at the specified
 * pointer address and increment the pointer by 16-bits (2 bytes).
 *
 * @param[inout]  p   A reference to a pointer address to read the
 *                    16-bit value from and to then increment by
 *                    16-bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t ReadUnaligned16(const void *&p)
{
    return IoReadUnaligned16(&p);
}

/**
 * Perform an aligned memory read of the 32-bit value at the specified
 * pointer address and increment the pointer by 32-bits (4 bytes).
 *
 * @param[inout]  p   A reference to a pointer address to read the
 *                    32-bit value from and to then increment by
 *                    32-bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t ReadUnaligned32(const void *&p)
{
    return IoReadUnaligned32(&p);
}

/**
 * Perform an unaligned memory read of the 64-bit value at the specified
 * pointer address and increment the pointer by 64-bits (8 bytes).
 *
 * @param[inout]  p   A reference to a pointer address to read the
 *                    64-bit value from and to then increment by
 *                    64-bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t ReadUnaligned64(const void *&p)
{
    return IoReadUnaligned64(&p);
}

/**
 * Perform a, potentially unaligned, memory read of the 8-bit value
 * from the specified pointer address and increment the pointer by
 * 8-bits (1 bytes).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 8-bit value from and to
 *                    then increment by 8-bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  ReadMaybeAligned8(const void *&p)
{
    return IoReadMaybeAligned8(&p);
}

/**
 * Perform a, potentially unaligned, memory read of the 16-bit value
 * from the specified pointer address and increment the pointer by
 * 16-bits (2 bytes).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 16-bit value from and to
 *                    then increment by 16-bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t ReadMaybeAligned16(const void *&p)
{
    return IoReadMaybeAligned16(&p);
}

/**
 * Perform a, potentially unaligned, memory read of the 32-bit value
 * from the specified pointer address and increment the pointer by
 * 32-bits (4 bytes).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 32-bit value from and to
 *                    then increment by 32-bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t ReadMaybeAligned32(const void *&p)
{
    return IoReadMaybeAligned32(&p);
}

/**
 * Perform a, potentially unaligned, memory read of the 64-bit value
 * from the specified pointer address and increment the pointer by
 * 64-bits (8 bytes).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 64-bit value from and to
 *                    then increment by 64-bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t ReadMaybeAligned64(const void *&p)
{
    return IoReadMaybeAligned64(&p);
}

/**
 * Perform an aligned memory write of the 8-bit value to the specified
 * pointer address and increment the pointer by 8-bits (1 byte).
 *
 * @param[inout]  p   A reference to a pointer address to read the 8-bit
 *                    value from and to then increment by 8-bits (1 byte).
 *
 * @param[in]     v   The 8-bit value to write.
 *
 */
static inline void     WriteAligned8(void *&p, const uint8_t v)
{
    IoWriteAligned8(&p, v);
}

/**
 * Perform an aligned memory write of the 16-bit value to the specified
 * pointer address and increment the pointer by 16-bits (2 bytes).
 *
 * @param[inout]  p   A reference to a pointer address to read the 16-bit
 *                    value from and to then increment by 16-bits (2 bytes).
 *
 * @param[in]     v   The 16-bit value to write.
 *
 */
static inline void     WriteAligned16(void *&p, const uint16_t v)
{
    IoWriteAligned16(&p, v);
}

/**
 * Perform an aligned memory write of the 32-bit value to the specified
 * pointer address and increment the pointer by 32-bits (4 bytes).
 *
 * @param[inout]  p   A reference to a pointer address to read the 32-bit
 *                    value from and to then increment by 32-bits (4 bytes).
 *
 * @param[in]     v   The 32-bit value to write.
 *
 */
static inline void     WriteAligned32(void *&p, const uint32_t v)
{
    IoWriteAligned32(&p, v);
}

/**
 * Perform an aligned memory write of the 64-bit value to the specified
 * pointer address and increment the pointer by 64-bits (8 bytes).
 *
 * @param[inout]  p   A reference to a pointer address to read the 64-bit
 *                    value from and to then increment by 64-bits (8 bytes).
 *
 * @param[in]     v   The 64-bit value to write.
 *
 */
static inline void     WriteAligned64(void *&p, const uint64_t v)
{
    IoWriteAligned64(&p, v);
}

/**
 * Perform an unaligned memory write of the 8-bit value to the specified
 * pointer address and increment the pointer by 8-bits (1 byte).
 *
 * @param[inout]  p   A reference to a pointer address to read the 8-bit
 *                    value from and to then increment by 8-bits (1 byte).
 *
 * @param[in]     v   The 8-bit value to write.
 *
 */
static inline void     WriteUnaligned8(void *&p, const uint8_t v)
{
    IoWriteUnaligned8(&p, v);
}

/**
 * Perform an unaligned memory write of the 16-bit value to the specified
 * pointer address and increment the pointer by 16-bits (2 bytes).
 *
 * @param[inout]  p   A reference to a pointer address to read the 16-bit
 *                    value from and to then increment by 16-bits (2 bytes).
 *
 * @param[in]     v   The 16-bit value to write.
 *
 */
static inline void     WriteUnaligned16(void *&p, const uint16_t v)
{
    IoWriteUnaligned16(&p, v);
}

/**
 * Perform an unaligned memory write of the 32-bit value to the specified
 * pointer address and increment the pointer by 32-bits (4 bytes).
 *
 * @param[inout]  p   A reference to a pointer address to read the 32-bit
 *                    value from and to then increment by 32-bits (4 bytes).
 *
 * @param[in]     v   The 32-bit value to write.
 *
 */
static inline void     WriteUnaligned32(void *&p, const uint32_t v)
{
    IoWriteUnaligned32(&p, v);
}

/**
 * Perform an unaligned memory write of the 64-bit value to the specified
 * pointer address and increment the pointer by 64-bits (8 bytes).
 *
 * @param[inout]  p   A reference to a pointer address to read the 64-bit
 *                    value from and to then increment by 64-bits (8 bytes).
 *
 * @param[in]     v   The 64-bit value to write.
 *
 */
static inline void     WriteUnaligned64(void *&p, const uint64_t v)
{
    IoWriteUnaligned64(&p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 8-bit value
 * to the specified pointer address and increment the pointer by
 * 8-bits (1 byte).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 8-bit value from and to
 *                    then increment by 8-bits (1 byte).
 *
 * @param[in]     v   The 8-bit value to write.
 *
 */
static inline void     WriteMaybeAligned8(void *&p, const uint8_t v)
{
    IoWriteMaybeAligned8(&p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 16-bit value
 * to the specified pointer address and increment the pointer by
 * 16-bits (2 bytes).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 16-bit value from and to
 *                    then increment by 16-bits (2 bytes).
 *
 * @param[in]     v   The 16-bit value to write.
 *
 */
static inline void     WriteMaybeAligned16(void *&p, const uint16_t v)
{
    IoWriteMaybeAligned16(&p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 32-bit value
 * to the specified pointer address and increment the pointer by
 * 32-bits (4 bytes).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 32-bit value from and to
 *                    then increment by 32-bits (4 bytes).
 *
 * @param[in]     v   The 32-bit value to write.
 *
 */
static inline void     WriteMaybeAligned32(void *&p, const uint32_t v)
{
    IoWriteMaybeAligned32(&p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 64-bit value
 * to the specified pointer address and increment the pointer by
 * 64-bits (8 bytes).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 64-bit value from and to
 *                    then increment by 64-bits (8 bytes).
 *
 * @param[in]     v   The 64-bit value to write.
 *
 */
static inline void     WriteMaybeAligned64(void *&p, const uint64_t v)
{
    IoWriteMaybeAligned64(&p, v);
}

/**
 * Perform a memory read of the 8-bit value at the specified pointer
 * address.
 *
 * @param[in]  p      A pointer address to read the 8-bit value from.
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  Get8(const void *p)
{
    return IoGet8(p);
}

/**
 * Perform a, potentially unaligned, memory read of the 16-bit value
 * from the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 16-bit value from.
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t Get16(const void *p)
{
    return IoGet16(p);
}

/**
 * Perform a, potentially unaligned, memory read of the 32-bit value
 * from the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 32-bit value from.
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t Get32(const void *p)
{
    return IoGet32(p);
}

/**
 * Perform a, potentially unaligned, memory read of the 64-bit value
 * from the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 64-bit value from.
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t Get64(const void *p)
{
    return IoGet64(p);
}

/**
 * Perform a, potentially unaligned, memory write of the 8-bit value
 * to the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the 8-bit value to.
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void Put8(void *p, const uint8_t v)
{
    IoPut8(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 16-bit value
 * to the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the 16-bit value to.
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void Put16(void *p, const uint16_t v)
{
    IoPut16(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 32-bit value
 * to the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the 32-bit value to.
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void Put32(void *p, const uint32_t v)
{
    IoPut32(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 64-bit value
 * to the specified pointer address.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the 64-bit value to.
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void Put64(void *p, const uint64_t v)
{
    IoPut64(p, v);
}

/**
 * Perform a, potentially unaligned, memory read of the 16-bit value
 * from the specified pointer address and increment the pointer by
 * 8-bits (1 byte).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 8-bit value from and to
 *                    then increment by 8-bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  Read8(const void *&p)
{
    return IoRead8(&p);
}

/**
 * Perform a, potentially unaligned, memory read of the 16-bit value
 * from the specified pointer address and increment the pointer by
 * 16-bits (2 bytes).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 16-bit value from and to
 *                    then increment by 16-bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t Read16(const void *&p)
{
    return IoRead16(&p);
}

/**
 * Perform a, potentially unaligned, memory read of the 32-bit value
 * from the specified pointer address and increment the pointer by
 * 32-bits (4 bytes).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 32-bit value from and to
 *                    then increment by 32-bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t Read32(const void *&p)
{
    return IoRead32(&p);
}

/**
 * Perform a, potentially unaligned, memory read of the 64-bit value
 * from the specified pointer address and increment the pointer by
 * 64-bits (8 bytes).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 64-bit value from and to
 *                    then increment by 64-bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t Read64(const void *&p)
{
    return IoRead64(&p);
}

/**
 * Perform a, potentially unaligned, memory write of the 8-bit value
 * to the specified pointer address and increment the pointer by
 * 8-bits (1 byte).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 8-bit value from and to
 *                    then increment by 8-bits (1 byte).
 *
 * @param[in]     v   The 8-bit value to write.
 *
 */
static inline void Write8(void *&p, const uint8_t v)
{
    IoWrite8(&p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 16-bit value
 * to the specified pointer address and increment the pointer by
 * 16-bits (2 bytes).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 16-bit value from and to
 *                    then increment by 16-bits (2 bytes).
 *
 * @param[in]     v   The 16-bit value to write.
 *
 */
static inline void Write16(void *&p, const uint16_t v)
{
    IoWrite16(&p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 32-bit value
 * to the specified pointer address and increment the pointer by
 * 32-bits (4 bytes).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 32-bit value from and to
 *                    then increment by 32-bits (4 bytes).
 *
 * @param[in]     v   The 32-bit value to write.
 *
 */
static inline void Write32(void *&p, const uint32_t v)
{
    IoWrite32(&p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 64-bit value
 * to the specified pointer address and increment the pointer by
 * 64-bits (8 bytes).
 *
 * @param[inout]  p   A reference to a pointer address, potentially
 *                    unaligned, to read the 64-bit value from and to
 *                    then increment by 64-bits (8 bytes).
 *
 * @param[in]     v   The 64-bit value to write.
 *
 */
static inline void Write64(void *&p, const uint64_t v)
{
    IoWrite64(&p, v);
}

} // namespace IO
} // namespace chip
