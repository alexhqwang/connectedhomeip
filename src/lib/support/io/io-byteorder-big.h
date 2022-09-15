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
 *      This file defines C functions for safely performing simple,
 *      memory-mapped accesses, potentially to unaligned, aligned, and
 *      unaligned memory locations with byte reordering, specifically
 *      for big endian target systems.
 */

#pragma once

#include <lib/support/io/byteorder.h>
#include <lib/support/io/io-base.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform a, potentially unaligned, memory read of the big endian
 * byte ordered 8-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 8-bit big endian byte ordered value from.
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoBigEndianGet8(const void *p)
{
    return IoGet8(p);
}

/**
 * Perform a, potentially unaligned, memory read of the big endian
 * byte ordered 16-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 16-bit big endian byte ordered value from.
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoBigEndianGet16(const void *p)
{
    return ByteOrderSwap16BigToHost(IoGet16(p));
}

/**
 * Perform a, potentially unaligned, memory read of the big endian
 * byte ordered 32-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 32-bit big endian byte ordered value from.
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoBigEndianGet32(const void *p)
{
    return ByteOrderSwap32BigToHost(IoGet32(p));
}

/**
 * Perform a, potentially unaligned, memory read of the big endian
 * byte ordered 64-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 64-bit big endian byte ordered value from.
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoBigEndianGet64(const void *p)
{
    return ByteOrderSwap64BigToHost(IoGet64(p));
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 8-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the target system byte ordered 8-bit value to in big
 *                    endian byte ordering.
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     IoBigEndianPut8(void *p, uint8_t v)
{
    IoPut8(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 16-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the target system byte ordered 16-bit value to in big
 *                    endian byte ordering.
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     IoBigEndianPut16(void *p, uint16_t v)
{
    IoPut16(p, ByteOrderSwap16HostToBig(v));
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 32-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the target system byte ordered 32-bit value to in big
 *                    endian byte ordering.
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     IoBigEndianPut32(void *p, uint32_t v)
{
    IoPut32(p, ByteOrderSwap32HostToBig(v));
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 64-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the target system byte ordered 64-bit value to in big
 *                    endian byte ordering.
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     IoBigEndianPut64(void *p, uint64_t v)
{
    IoPut64(p, ByteOrderSwap64HostToBig(v));
}

/**
 * Perform a, potentially unaligned, memory read of the big endian
 * byte ordered 8-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 8-bits (1 byte).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 8-bit big endian byte
 *                    ordered value from and to then increment by 8-
 *                    bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoBigEndianRead8(const void **p)
{
    return IoRead8(p);
}

/**
 * Perform a, potentially unaligned, memory read of the big endian
 * byte ordered 16-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 16-bit big endian byte
 *                    ordered value from and to then increment by 16-
 *                    bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoBigEndianRead16(const void **p)
{
    return ByteOrderSwap16BigToHost(IoRead16(p));
}

/**
 * Perform a, potentially unaligned, memory read of the big endian
 * byte ordered 32-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 32-bit big endian byte
 *                    ordered value from and to then increment by 32-
 *                    bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoBigEndianRead32(const void **p)
{
    return ByteOrderSwap32BigToHost(IoRead32(p));
}

/**
 * Perform a, potentially unaligned, memory read of the big endian
 * byte ordered 64-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 64-bit big endian byte
 *                    ordered value from and to then increment by 64-
 *                    bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoBigEndianRead64(const void **p)
{
    return ByteOrderSwap64BigToHost(IoRead64(p));
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 8-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      A pointer to a pointer address, potentially
 *                    unaligned, to write the target system byte
 *                    ordered 8-bit value to in big endian byte
 *                    ordering and to then increment by 8-bits (1
 *                    byte).
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     IoBigEndianWrite8(void **p, uint8_t v)
{
    IoWrite8(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 16-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      A pointer to a pointer address, potentially
 *                    unaligned, to write the target system byte
 *                    ordered 16-bit value to in big endian byte
 *                    ordering and to then increment by 16-bits (2
 *                    bytes).
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     IoBigEndianWrite16(void **p, uint16_t v)
{
    IoWrite16(p, ByteOrderSwap16HostToBig(v));
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 32-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      A pointer to a pointer address, potentially
 *                    unaligned, to write the target system byte
 *                    ordered 32-bit value to in big endian byte
 *                    ordering and to then increment by 16-bits (4
 *                    bytes).
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     IoBigEndianWrite32(void **p, uint32_t v)
{
    IoWrite32(p, ByteOrderSwap32HostToBig(v));
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 64-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      A pointer to a pointer address, potentially
 *                    unaligned, to write the target system byte
 *                    ordered 64-bit value to in big endian byte
 *                    ordering and to then increment by 64-bits (8
 *                    bytes).
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     IoBigEndianWrite64(void **p, uint64_t v)
{
    IoWrite64(p, ByteOrderSwap64HostToBig(v));
}

/**
 * Perform an aligned memory read of the big endian
 * byte ordered 8-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An aligned pointer address to read
 *                    the 8-bit big endian byte ordered value from.
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoBigEndianGetAligned8(const void *p)
{
    return IoGetAligned8(p);
}

/**
 * Perform an aligned memory read of the big endian
 * byte ordered 16-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An aligned pointer address to read
 *                    the 16-bit big endian byte ordered value from.
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoBigEndianGetAligned16(const void *p)
{
    return ByteOrderSwap16BigToHost(IoGetAligned16(p));
}

/**
 * Perform an aligned memory read of the big endian
 * byte ordered 32-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An aligned pointer address to read
 *                    the 32-bit big endian byte ordered value from.
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoBigEndianGetAligned32(const void *p)
{
    return ByteOrderSwap32BigToHost(IoGetAligned32(p));
}

/**
 * Perform an aligned memory read of the big endian
 * byte ordered 64-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An aligned pointer address to read
 *                    the 64-bit big endian byte ordered value from.
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoBigEndianGetAligned64(const void *p)
{
    return ByteOrderSwap64BigToHost(IoGetAligned64(p));
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 8-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      An aligned pointer address to write
 *                    the target system byte ordered 8-bit value to in big
 *                    endian byte ordering.
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     IoBigEndianPutAligned8(void *p, uint8_t v)
{
    IoPutAligned8(p, v);
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 16-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      An aligned pointer address to write
 *                    the target system byte ordered 16-bit value to in big
 *                    endian byte ordering.
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     IoBigEndianPutAligned16(void *p, uint16_t v)
{
    IoPutAligned16(p, ByteOrderSwap16HostToBig(v));
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 32-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      An aligned pointer address to write
 *                    the target system byte ordered 32-bit value to in big
 *                    endian byte ordering.
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     IoBigEndianPutAligned32(void *p, uint32_t v)
{
    IoPutAligned32(p, ByteOrderSwap32HostToBig(v));
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 64-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      An aligned pointer address to write
 *                    the target system byte ordered 64-bit value to in big
 *                    endian byte ordering.
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     IoBigEndianPutAligned64(void *p, uint64_t v)
{
    IoPutAligned64(p, ByteOrderSwap64HostToBig(v));
}

/**
 * Perform an aligned memory read of the big endian
 * byte ordered 8-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 8-bits (1 byte).
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to read the 8-bit big endian byte
 *                    ordered value from and to then increment by 8-
 *                    bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoBigEndianReadAligned8(const void **p)
{
    return IoReadAligned8(p);
}

/**
 * Perform an aligned memory read of the big endian
 * byte ordered 16-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to read the 16-bit big endian byte
 *                    ordered value from and to then increment by 16-
 *                    bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoBigEndianReadAligned16(const void **p)
{
    return ByteOrderSwap16BigToHost(IoReadAligned16(p));
}

/**
 * Perform an aligned memory read of the big endian
 * byte ordered 32-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to read the 32-bit big endian byte
 *                    ordered value from and to then increment by 32-
 *                    bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoBigEndianReadAligned32(const void **p)
{
    return ByteOrderSwap32BigToHost(IoReadAligned32(p));
}

/**
 * Perform an aligned memory read of the big endian
 * byte ordered 64-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to read the 64-bit big endian byte
 *                    ordered value from and to then increment by 64-
 *                    bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoBigEndianReadAligned64(const void **p)
{
    return ByteOrderSwap64BigToHost(IoReadAligned64(p));
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 8-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to write the target system byte
 *                    ordered 8-bit value to in big endian byte
 *                    ordering and to then increment by 8-bits (1
 *                    byte).
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     IoBigEndianWriteAligned8(void **p, uint8_t v)
{
    IoWriteAligned8(p, v);
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 16-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to write the target system byte
 *                    ordered 16-bit value to in big endian byte
 *                    ordering and to then increment by 16-bits (2
 *                    bytes).
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     IoBigEndianWriteAligned16(void **p, uint16_t v)
{
    IoWriteAligned16(p, ByteOrderSwap16HostToBig(v));
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 32-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to write the target system byte
 *                    ordered 32-bit value to in big endian byte
 *                    ordering and to then increment by 16-bits (4
 *                    bytes).
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     IoBigEndianWriteAligned32(void **p, uint32_t v)
{
    IoWriteAligned32(p, ByteOrderSwap32HostToBig(v));
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 64-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to write the target system byte
 *                    ordered 64-bit value to in big endian byte
 *                    ordering and to then increment by 64-bits (8
 *                    bytes).
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     IoBigEndianWriteAligned64(void **p, uint64_t v)
{
    IoWriteAligned64(p, ByteOrderSwap64HostToBig(v));
}

/**
 * Perform an unaligned memory read of the big endian
 * byte ordered 8-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to read
 *                    the 8-bit big endian byte ordered value from.
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoBigEndianGetUnaligned8(const void *p)
{
    return IoGetUnaligned8(p);
}

/**
 * Perform an unaligned memory read of the big endian
 * byte ordered 16-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to read
 *                    the 16-bit big endian byte ordered value from.
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoBigEndianGetUnaligned16(const void *p)
{
    return ByteOrderSwap16BigToHost(IoGetUnaligned16(p));
}

/**
 * Perform an unaligned memory read of the big endian
 * byte ordered 32-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to read
 *                    the 32-bit big endian byte ordered value from.
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoBigEndianGetUnaligned32(const void *p)
{
    return ByteOrderSwap32BigToHost(IoGetUnaligned32(p));
}

/**
 * Perform an unaligned memory read of the big endian
 * byte ordered 64-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to read
 *                    the 64-bit big endian byte ordered value from.
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoBigEndianGetUnaligned64(const void *p)
{
    return ByteOrderSwap64BigToHost(IoGetUnaligned64(p));
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 8-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to write
 *                    the target system byte ordered 8-bit value to in big
 *                    endian byte ordering.
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     IoBigEndianPutUnaligned8(void *p, uint8_t v)
{
    IoPutUnaligned8(p, v);
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 16-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to write
 *                    the target system byte ordered 16-bit value to in big
 *                    endian byte ordering.
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     IoBigEndianPutUnaligned16(void *p, uint16_t v)
{
    IoPutUnaligned16(p, ByteOrderSwap16HostToBig(v));
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 32-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to write
 *                    the target system byte ordered 32-bit value to in big
 *                    endian byte ordering.
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     IoBigEndianPutUnaligned32(void *p, uint32_t v)
{
    IoPutUnaligned32(p, ByteOrderSwap32HostToBig(v));
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 64-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to write
 *                    the target system byte ordered 64-bit value to in big
 *                    endian byte ordering.
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     IoBigEndianPutUnaligned64(void *p, uint64_t v)
{
    IoPutUnaligned64(p, ByteOrderSwap64HostToBig(v));
}

/**
 * Perform an unaligned memory read of the big endian
 * byte ordered 8-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 8-bits (1 byte).
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to read the 8-bit big endian byte
 *                    ordered value from and to then increment by 8-
 *                    bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoBigEndianReadUnaligned8(const void **p)
{
    return IoReadUnaligned8(p);
}

/**
 * Perform an unaligned memory read of the big endian
 * byte ordered 16-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to read the 16-bit big endian byte
 *                    ordered value from and to then increment by 16-
 *                    bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoBigEndianReadUnaligned16(const void **p)
{
    return ByteOrderSwap16BigToHost(IoReadUnaligned16(p));
}

/**
 * Perform an unaligned memory read of the big endian
 * byte ordered 32-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to read the 32-bit big endian byte
 *                    ordered value from and to then increment by 32-
 *                    bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoBigEndianReadUnaligned32(const void **p)
{
    return ByteOrderSwap32BigToHost(IoReadUnaligned32(p));
}

/**
 * Perform an unaligned memory read of the big endian
 * byte ordered 64-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to read the 64-bit big endian byte
 *                    ordered value from and to then increment by 64-
 *                    bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoBigEndianReadUnaligned64(const void **p)
{
    return ByteOrderSwap64BigToHost(IoReadUnaligned64(p));
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 8-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to write the target system byte
 *                    ordered 8-bit value to in big endian byte
 *                    ordering and to then increment by 8-bits (1
 *                    byte).
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     IoBigEndianWriteUnaligned8(void **p, uint8_t v)
{
    IoWriteUnaligned8(p, v);
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 16-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to write the target system byte
 *                    ordered 16-bit value to in big endian byte
 *                    ordering and to then increment by 16-bits (2
 *                    bytes).
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     IoBigEndianWriteUnaligned16(void **p, uint16_t v)
{
    IoWriteUnaligned16(p, ByteOrderSwap16HostToBig(v));
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 32-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to write the target system byte
 *                    ordered 32-bit value to in big endian byte
 *                    ordering and to then increment by 32-bits (4
 *                    bytes).
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     IoBigEndianWriteUnaligned32(void **p, uint32_t v)
{
    IoWriteUnaligned32(p, ByteOrderSwap32HostToBig(v));
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 64-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in big endian byte ordering.
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to write the target system byte
 *                    ordered 64-bit value to in big endian byte
 *                    ordering and to then increment by 64-bits (8
 *                    bytes).
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     IoBigEndianWriteUnaligned64(void **p, uint64_t v)
{
    IoWriteUnaligned64(p, ByteOrderSwap64HostToBig(v));
}

#ifdef __cplusplus
}
#endif
