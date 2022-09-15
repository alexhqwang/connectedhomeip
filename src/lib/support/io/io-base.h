/**
 *    Copyright (c) 2022 Project CHIP Authors
 *    Copyright 2013-2017 Nest Labs Inc. All Rights Reserved.
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
 *      This file defines C functions for safely performing simple,
 *      memory-mapped accesses, potentially to unaligned memory
 *      locations.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <lib/support/io/io-private.h>

/*
 * If we are compiling under clang, GCC, or any such compatible
 * compiler, in which -fno-builtins or -ffreestanding might be
 * asserted, thereby eliminating built-in function optimization, we
 * STILL want built-in memcpy. We want this because it allows the
 * compiler to use architecture-specific machine instructions or
 * inline code generation to optimize an otherwise-expensive memcpy
 * for unaligned reads and writes, which is exactly the kind of
 * efficiency that would be expected of nlIO.
 */
#if __IOHasBuiltin(__builtin_memcpy)
#define __IO_MEMCPY __builtin_memcpy
#else
#define __IO_MEMCPY memcpy
#endif

#ifdef __cplusplus
extern "C" {
#endif

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
static inline bool IoIsAligned(const void *p, size_t size)
{
    const uintptr_t value = (uintptr_t)(p);
    const uintptr_t mask  = size - 1;

    return ((value & mask) == 0);
}

/**
 * Perform an aligned memory read of the 8-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 8-bit value from.
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoGetAligned8(const void *p)
{
    return *(const uint8_t *)(p);
}

/**
 * Perform an aligned memory read of the 16-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 16-bit value from.
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoGetAligned16(const void *p)
{
    return *(const uint16_t *)(p);
}

/**
 * Perform an aligned memory read of the 32-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 32-bit value from.
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoGetAligned32(const void *p)
{
    return *(const uint32_t *)(p);
}

/**
 * Perform an aligned memory read of the 64-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 64-bit value from.
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoGetAligned64(const void *p)
{
    return *(const uint64_t *)(p);
}

/**
 * Perform an unaligned memory read of the 8-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 8-bit value from.
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoGetUnaligned8(const void *p)
{
    return IoGetAligned8(p);
}

/**
 * Perform an unaligned memory read of the 16-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 16-bit value from.
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoGetUnaligned16(const void *p)
{
    uint16_t temp;

    __IO_MEMCPY(&temp, p, sizeof(uint16_t));

    return temp;
}

/**
 * Perform an unaligned memory read of the 32-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 32-bit value from.
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoGetUnaligned32(const void *p)
{
    uint32_t temp;

    __IO_MEMCPY(&temp, p, sizeof(uint32_t));

    return temp;
}

/**
 * Perform an unaligned memory read of the 64-bit value at the specified
 * pointer address.
 *
 * @param[in]  p      A pointer address to read the 64-bit value from.
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoGetUnaligned64(const void *p)
{
    uint64_t temp;

    __IO_MEMCPY(&temp, p, sizeof(uint64_t));

    return temp;
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
static inline uint8_t  IoGetMaybeAligned8(const void *p)
{
    return IoGetAligned8(p);
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
static inline uint16_t IoGetMaybeAligned16(const void *p)
{
    if (IoIsAligned(p, sizeof (uint16_t)))
        return IoGetAligned16(p);
    else
        return IoGetUnaligned16(p);
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
static inline uint32_t IoGetMaybeAligned32(const void *p)
{
    if (IoIsAligned(p, sizeof (uint32_t)))
        return IoGetAligned32(p);
    else
        return IoGetUnaligned32(p);
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
static inline uint64_t IoGetMaybeAligned64(const void *p)
{
    if (IoIsAligned(p, sizeof (uint64_t)))
        return IoGetAligned64(p);
    else
        return IoGetUnaligned64(p);
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
static inline void     IoPutAligned8(void *p, const uint8_t v)
{
    *(uint8_t *)(p) = v;
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
static inline void     IoPutAligned16(void *p, const uint16_t v)
{
    *(uint16_t *)(p) = v;
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
static inline void     IoPutAligned32(void *p, const uint32_t v)
{
    *(uint32_t *)(p) = v;
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
static inline void     IoPutAligned64(void *p, const uint64_t v)
{
    *(uint64_t *)(p) = v;
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
static inline void     IoPutUnaligned8(void *p, const uint8_t v)
{
    IoPutAligned8(p, v);
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
static inline void     IoPutUnaligned16(void *p, const uint16_t v)
{
    __IO_MEMCPY(p, &v, sizeof(uint16_t));
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
static inline void     IoPutUnaligned32(void *p, const uint32_t v)
{
    __IO_MEMCPY(p, &v, sizeof(uint32_t));
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
static inline void     IoPutUnaligned64(void *p, const uint64_t v)
{
    __IO_MEMCPY(p, &v, sizeof(uint64_t));
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
static inline void     IoPutMaybeAligned8(void *p, const uint8_t v)
{
    IoPutAligned8(p, v);
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
static inline void     IoPutMaybeAligned16(void *p, const uint16_t v)
{
    if (IoIsAligned(p, sizeof (uint16_t)))
        IoPutAligned16(p, v);
    else
        IoPutUnaligned16(p, v);
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
static inline void     IoPutMaybeAligned32(void *p, const uint32_t v)
{
    if (IoIsAligned(p, sizeof (uint32_t)))
        IoPutAligned32(p, v);
    else
        IoPutUnaligned32(p, v);
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
static inline void     IoPutMaybeAligned64(void *p, const uint64_t v)
{
    if (IoIsAligned(p, sizeof (uint64_t)))
        IoPutAligned64(p, v);
    else
        IoPutUnaligned64(p, v);
}

/**
 * Perform an aligned memory read of the 8-bit value at the specified
 * pointer address and increment the pointer by 8-bits (1 byte).
 *
 * @param[inout]  p   A pointer to a pointer address to read the
 *                    8-bit value from and to then increment by
 *                    8-bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoReadAligned8(const void **p)
{
    const uint8_t temp = IoGetAligned8(*p);

    *(const uint8_t **)(p) += sizeof (uint8_t);

    return temp;
}

/**
 * Perform an aligned memory read of the 16-bit value at the specified
 * pointer address and increment the pointer by 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address to read the
 *                    16-bit value from and to then increment by
 *                    16-bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoReadAligned16(const void **p)
{
    const uint16_t temp = IoGetAligned16(*p);

    *(const uint8_t **)(p) += sizeof (uint16_t);

    return temp;
}

/**
 * Perform an aligned memory read of the 32-bit value at the specified
 * pointer address and increment the pointer by 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address to read the
 *                    32-bit value from and to then increment by
 *                    32-bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoReadAligned32(const void **p)
{
    const uint32_t temp = IoGetAligned32(*p);

    *(const uint8_t **)(p) += sizeof (uint32_t);

    return temp;
}

/**
 * Perform an aligned memory read of the 64-bit value at the specified
 * pointer address and increment the pointer by 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address to read the
 *                    64-bit value from and to then increment by
 *                    64-bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoReadAligned64(const void **p)
{
    const uint64_t temp = IoGetAligned64(*p);

    *(const uint8_t **)(p) += sizeof (uint64_t);

    return temp;
}

/**
 * Perform an unaligned memory read of the 8-bit value at the specified
 * pointer address and increment the pointer by 8-bits (1 byte).
 *
 * @param[inout]  p   A pointer to a pointer address to read the
 *                    8-bit value from and to then increment by
 *                    8-bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t IoReadUnaligned8(const void **p)
{
    const uint8_t temp = IoGetUnaligned8(*p);

    *(const uint8_t **)(p) += sizeof (uint8_t);

    return temp;
}

/**
 * Perform an unaligned memory read of the 16-bit value at the specified
 * pointer address and increment the pointer by 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address to read the
 *                    16-bit value from and to then increment by
 *                    16-bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoReadUnaligned16(const void **p)
{
    const uint16_t temp = IoGetUnaligned16(*p);

    *(const uint8_t **)(p) += sizeof (uint16_t);

    return temp;
}

/**
 * Perform an aligned memory read of the 32-bit value at the specified
 * pointer address and increment the pointer by 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address to read the
 *                    32-bit value from and to then increment by
 *                    32-bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoReadUnaligned32(const void **p)
{
    const uint32_t temp = IoGetUnaligned32(*p);

    *(const uint8_t **)(p) += sizeof (uint32_t);

    return temp;
}

/**
 * Perform an unaligned memory read of the 64-bit value at the specified
 * pointer address and increment the pointer by 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address to read the
 *                    64-bit value from and to then increment by
 *                    64-bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoReadUnaligned64(const void **p)
{
    const uint64_t temp = IoGetUnaligned64(*p);

    *(const uint8_t **)(p) += sizeof (uint64_t);

    return temp;
}

/**
 * Perform a, potentially unaligned, memory read of the 8-bit value
 * from the specified pointer address and increment the pointer by
 * 8-bits (1 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 8-bit value from and to
 *                    then increment by 8-bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoReadMaybeAligned8(const void **p)
{
    const uint8_t temp = IoGetMaybeAligned8(*p);

    *(const uint8_t **)(p) += sizeof (uint8_t);

    return temp;
}

/**
 * Perform a, potentially unaligned, memory read of the 16-bit value
 * from the specified pointer address and increment the pointer by
 * 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 16-bit value from and to
 *                    then increment by 16-bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoReadMaybeAligned16(const void **p)
{
    const uint16_t temp = IoGetMaybeAligned16(*p);

    *(const uint8_t **)(p) += sizeof (uint16_t);

    return temp;
}

/**
 * Perform a, potentially unaligned, memory read of the 32-bit value
 * from the specified pointer address and increment the pointer by
 * 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 32-bit value from and to
 *                    then increment by 32-bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoReadMaybeAligned32(const void **p)
{
    const uint32_t temp = IoGetMaybeAligned32(*p);

    *(const uint8_t **)(p) += sizeof (uint32_t);

    return temp;
}

/**
 * Perform a, potentially unaligned, memory read of the 64-bit value
 * from the specified pointer address and increment the pointer by
 * 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 64-bit value from and to
 *                    then increment by 64-bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoReadMaybeAligned64(const void **p)
{
    const uint64_t temp = IoGetMaybeAligned64(*p);

    *(const uint8_t **)(p) += sizeof (uint64_t);

    return temp;
}

/**
 * Perform an aligned memory write of the 8-bit value to the specified
 * pointer address and increment the pointer by 8-bits (1 byte).
 *
 * @param[inout]  p   A pointer to a pointer address to read the 8-bit
 *                    value from and to then increment by 8-bits (1 byte).
 *
 * @param[in]     v   The 8-bit value to write.
 *
 */
static inline void     IoWriteAligned8(void **p, const uint8_t v)
{
    IoPutAligned8(*p, v);       *(const uint8_t **)(p) += sizeof (uint8_t);
}

/**
 * Perform an aligned memory write of the 16-bit value to the specified
 * pointer address and increment the pointer by 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address to read the 16-bit
 *                    value from and to then increment by 16-bits (2 bytes).
 *
 * @param[in]     v   The 16-bit value to write.
 *
 */
static inline void     IoWriteAligned16(void **p, const uint16_t v)
{
    IoPutAligned16(*p, v);      *(const uint8_t **)(p) += sizeof (uint16_t);
}

/**
 * Perform an aligned memory write of the 32-bit value to the specified
 * pointer address and increment the pointer by 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address to read the 32-bit
 *                    value from and to then increment by 32-bits (4 bytes).
 *
 * @param[in]     v   The 32-bit value to write.
 *
 */
static inline void     IoWriteAligned32(void **p, const uint32_t v)
{
    IoPutAligned32(*p, v);      *(const uint8_t **)(p) += sizeof (uint32_t);
}

/**
 * Perform an aligned memory write of the 64-bit value to the specified
 * pointer address and increment the pointer by 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address to read the 64-bit
 *                    value from and to then increment by 64-bits (8 bytes).
 *
 * @param[in]     v   The 64-bit value to write.
 *
 */
static inline void     IoWriteAligned64(void **p, const uint64_t v)
{
    IoPutAligned64(*p, v);      *(const uint8_t **)(p) += sizeof (uint64_t);
}

/**
 * Perform an unaligned memory write of the 8-bit value to the specified
 * pointer address and increment the pointer by 8-bits (1 byte).
 *
 * @param[inout]  p   A pointer to a pointer address to read the 8-bit
 *                    value from and to then increment by 8-bits (1 byte).
 *
 * @param[in]     v   The 8-bit value to write.
 *
 */
static inline void     IoWriteUnaligned8(void **p, const uint8_t v)
{
    IoPutUnaligned8(*p, v);     *(const uint8_t **)(p) += sizeof (uint8_t);
}

/**
 * Perform an unaligned memory write of the 16-bit value to the specified
 * pointer address and increment the pointer by 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address to read the 16-bit
 *                    value from and to then increment by 16-bits (2 bytes).
 *
 * @param[in]     v   The 16-bit value to write.
 *
 */
static inline void     IoWriteUnaligned16(void **p, const uint16_t v)
{
    IoPutUnaligned16(*p, v);    *(const uint8_t **)(p) += sizeof (uint16_t);
}

/**
 * Perform an unaligned memory write of the 32-bit value to the specified
 * pointer address and increment the pointer by 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address to read the 32-bit
 *                    value from and to then increment by 32-bits (4 bytes).
 *
 * @param[in]     v   The 32-bit value to write.
 *
 */
static inline void     IoWriteUnaligned32(void **p, const uint32_t v)
{
    IoPutUnaligned32(*p, v);    *(const uint8_t **)(p) += sizeof (uint32_t);
}

/**
 * Perform an unaligned memory write of the 64-bit value to the specified
 * pointer address and increment the pointer by 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address to read the 64-bit
 *                    value from and to then increment by 64-bits (8 bytes).
 *
 * @param[in]     v   The 64-bit value to write.
 *
 */
static inline void     IoWriteUnaligned64(void **p, const uint64_t v)
{
    IoPutUnaligned64(*p, v);    *(const uint8_t **)(p) += sizeof (uint64_t);
}

/**
 * Perform a, potentially unaligned, memory write of the 8-bit value
 * to the specified pointer address and increment the pointer by
 * 8-bits (2 byte).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 8-bit value from and to
 *                    then increment by 8-bits (1 byte).
 *
 * @param[in]     v   The 8-bit value to write.
 *
 */
static inline void     IoWriteMaybeAligned8(void **p, const uint8_t v)
{
    IoPutMaybeAligned8(*p, v);  *(const uint8_t **)(p) += sizeof (uint8_t);
}

/**
 * Perform a, potentially unaligned, memory write of the 16-bit value
 * to the specified pointer address and increment the pointer by
 * 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 16-bit value from and to
 *                    then increment by 16-bits (2 bytes).
 *
 * @param[in]     v   The 16-bit value to write.
 *
 */
static inline void     IoWriteMaybeAligned16(void **p, const uint16_t v)
{
    IoPutMaybeAligned16(*p, v); *(const uint8_t **)(p) += sizeof (uint16_t);
}

/**
 * Perform a, potentially unaligned, memory write of the 32-bit value
 * to the specified pointer address and increment the pointer by
 * 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 32-bit value from and to
 *                    then increment by 32-bits (4 bytes).
 *
 * @param[in]     v   The 32-bit value to write.
 *
 */
static inline void     IoWriteMaybeAligned32(void **p, const uint32_t v)
{
    IoPutMaybeAligned32(*p, v); *(const uint8_t **)(p) += sizeof (uint32_t);
}

/**
 * Perform a, potentially unaligned, memory write of the 64-bit value
 * to the specified pointer address and increment the pointer by
 * 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 64-bit value from and to
 *                    then increment by 64-bits (8 bytes).
 *
 * @param[in]     v   The 64-bit value to write.
 *
 */
static inline void     IoWriteMaybeAligned64(void **p, const uint64_t v)
{
    IoPutMaybeAligned64(*p, v); *(const uint8_t **)(p) += sizeof (uint64_t);
}

/**
 * Perform a memory read of the 8-bit value at the specified pointer
 * address.
 *
 * @param[in]  p      A pointer address to read the 8-bit value from.
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t IoGet8(const void *p)
{
    return IoGetAligned8(p);
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
static inline uint16_t IoGet16(const void *p)
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
static inline uint32_t IoGet32(const void *p)
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
static inline uint64_t IoGet64(const void *p)
{
    return IoGetMaybeAligned64(p);
}

/**
 * Perform a memory write of the 8-bit value to the specified pointer
 * address.
 *
 * @param[in]  p      A pointer address to write the 8-bit value to.
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void IoPut8(void *p, uint8_t v)
{
    IoPutAligned8(p, v);
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
static inline void IoPut16(void *p, uint16_t v)
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
static inline void IoPut32(void *p, uint32_t v)
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
static inline void IoPut64(void *p, uint64_t v)
{
    IoPutMaybeAligned64(p, v);
}

/**
 * Perform a, potentially unaligned, memory read of the 16-bit value
 * from the specified pointer address and increment the pointer by
 * 8-bits (1 byte).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 8-bit value from and to
 *                    then increment by 8-bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoRead8(const void **p)
{
    return IoReadAligned8(p);
}

/**
 * Perform a, potentially unaligned, memory read of the 16-bit value
 * from the specified pointer address and increment the pointer by
 * 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 16-bit value from and to
 *                    then increment by 16-bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoRead16(const void **p)
{
    return IoReadMaybeAligned16(p);
}

/**
 * Perform a, potentially unaligned, memory read of the 32-bit value
 * from the specified pointer address and increment the pointer by
 * 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 32-bit value from and to
 *                    then increment by 32-bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoRead32(const void **p)
{
    return IoReadMaybeAligned32(p);
}

/**
 * Perform a, potentially unaligned, memory read of the 64-bit value
 * from the specified pointer address and increment the pointer by
 * 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 64-bit value from and to
 *                    then increment by 64-bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoRead64(const void **p)
{
    return IoReadMaybeAligned64(p);
}

/**
 * Perform a, potentially unaligned, memory write of the 8-bit value
 * to the specified pointer address and increment the pointer by
 * 8-bits (1 byte).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 8-bit value from and to
 *                    then increment by 8-bits (1 byte).
 *
 * @param[in]     v   The 8-bit value to write.
 *
 */
static inline void IoWrite8(void **p, uint8_t v)
{
    IoWriteAligned8(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 16-bit value
 * to the specified pointer address and increment the pointer by
 * 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 16-bit value from and to
 *                    then increment by 16-bits (2 bytes).
 *
 * @param[in]     v   The 16-bit value to write.
 *
 */
static inline void IoWrite16(void **p, uint16_t v)
{
    IoWriteMaybeAligned16(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 32-bit value
 * to the specified pointer address and increment the pointer by
 * 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 32-bit value from and to
 *                    then increment by 32-bits (4 bytes).
 *
 * @param[in]     v   The 32-bit value to write.
 *
 */
static inline void IoWrite32(void **p, uint32_t v)
{
    IoWriteMaybeAligned32(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the 64-bit value
 * to the specified pointer address and increment the pointer by
 * 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 64-bit value from and to
 *                    then increment by 64-bits (8 bytes).
 *
 * @param[in]     v   The 64-bit value to write.
 *
 */
static inline void IoWrite64(void **p, uint64_t v)
{
    IoWriteMaybeAligned64(p, v);
}

#ifdef __cplusplus
}
#endif

#undef __IO_MEMCPY
