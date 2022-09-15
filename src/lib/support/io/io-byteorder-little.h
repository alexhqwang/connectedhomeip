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
 *      for little endian target systems.
 */

#pragma once

#include <lib/support/io/byteorder.h>
#include <lib/support/io/io-base.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform a, potentially unaligned, memory read of the little endian
 * byte ordered 8-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 8-bit little endian byte ordered value from.
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoLittleEndianGet8(const void *p)
{
    return IoGet8(p);
}

/**
 * Perform a, potentially unaligned, memory read of the little endian
 * byte ordered 16-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 16-bit little endian byte ordered value from.
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoLittleEndianGet16(const void *p)
{
    return ByteOrderSwap16LittleToHost(IoGet16(p));
}

/**
 * Perform a, potentially unaligned, memory read of the little endian
 * byte ordered 32-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 32-bit little endian byte ordered value from.
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoLittleEndianGet32(const void *p)
{
    return ByteOrderSwap32LittleToHost(IoGet32(p));
}

/**
 * Perform a, potentially unaligned, memory read of the little endian
 * byte ordered 64-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to read
 *                    the 64-bit little endian byte ordered value from.
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoLittleEndianGet64(const void *p)
{
    return ByteOrderSwap64LittleToHost(IoGet64(p));
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 8-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the target system byte ordered 8-bit value to in little
 *                    endian byte ordering.
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     IoLittleEndianPut8(void *p, uint8_t v)
{
    IoPut8(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 16-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the target system byte ordered 16-bit value to in little
 *                    endian byte ordering.
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     IoLittleEndianPut16(void *p, uint16_t v)
{
    IoPut16(p, ByteOrderSwap16HostToLittle(v));
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 32-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the target system byte ordered 32-bit value to in little
 *                    endian byte ordering.
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     IoLittleEndianPut32(void *p, uint32_t v)
{
    IoPut32(p, ByteOrderSwap32HostToLittle(v));
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 64-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      A pointer address, potentially unaligned, to write
 *                    the target system byte ordered 64-bit value to in little
 *                    endian byte ordering.
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     IoLittleEndianPut64(void *p, uint64_t v)
{
    IoPut64(p, ByteOrderSwap64HostToLittle(v));
}

/**
 * Perform a, potentially unaligned, memory read of the little endian
 * byte ordered 8-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 8-bits (1 byte).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 8-bit little endian byte
 *                    ordered value from and to then increment by 8-
 *                    bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoLittleEndianRead8(const void **p)
{
    return IoRead8(p);
}

/**
 * Perform a, potentially unaligned, memory read of the little endian
 * byte ordered 16-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 16-bit little endian byte
 *                    ordered value from and to then increment by 16-
 *                    bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoLittleEndianRead16(const void **p)
{
    return ByteOrderSwap16LittleToHost(IoRead16(p));
}

/**
 * Perform a, potentially unaligned, memory read of the little endian
 * byte ordered 32-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 32-bit little endian byte
 *                    ordered value from and to then increment by 32-
 *                    bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoLittleEndianRead32(const void **p)
{
    return ByteOrderSwap32LittleToHost(IoRead32(p));
}

/**
 * Perform a, potentially unaligned, memory read of the little endian
 * byte ordered 64-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to a pointer address, potentially
 *                    unaligned, to read the 64-bit little endian byte
 *                    ordered value from and to then increment by 64-
 *                    bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoLittleEndianRead64(const void **p)
{
    return ByteOrderSwap64LittleToHost(IoRead64(p));
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 8-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      A pointer to a pointer address, potentially
 *                    unaligned, to write the target system byte
 *                    ordered 8-bit value to in little endian byte
 *                    ordering and to then increment by 8-bits (1
 *                    byte).
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     IoLittleEndianWrite8(void **p, uint8_t v)
{
    IoWrite8(p, v);
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 16-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      A pointer to a pointer address, potentially
 *                    unaligned, to write the target system byte
 *                    ordered 16-bit value to in little endian byte
 *                    ordering and to then increment by 16-bits (2
 *                    bytes).
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     IoLittleEndianWrite16(void **p, uint16_t v)
{
    IoWrite16(p, ByteOrderSwap16HostToLittle(v));
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 32-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      A pointer to a pointer address, potentially
 *                    unaligned, to write the target system byte
 *                    ordered 32-bit value to in little endian byte
 *                    ordering and to then increment by 16-bits (4
 *                    bytes).
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     IoLittleEndianWrite32(void **p, uint32_t v)
{
    IoWrite32(p, ByteOrderSwap32HostToLittle(v));
}

/**
 * Perform a, potentially unaligned, memory write of the target system
 * byte ordered 64-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      A pointer to a pointer address, potentially
 *                    unaligned, to write the target system byte
 *                    ordered 64-bit value to in little endian byte
 *                    ordering and to then increment by 64-bits (8
 *                    bytes).
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     IoLittleEndianWrite64(void **p, uint64_t v)
{
    IoWrite64(p, ByteOrderSwap64HostToLittle(v));
}

/**
 * Perform an aligned memory read of the little endian
 * byte ordered 8-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An aligned pointer address to read
 *                    the 8-bit little endian byte ordered value from.
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoLittleEndianGetAligned8(const void *p)
{
    return IoGetAligned8(p);
}

/**
 * Perform an aligned memory read of the little endian
 * byte ordered 16-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An aligned pointer address to read
 *                    the 16-bit little endian byte ordered value from.
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoLittleEndianGetAligned16(const void *p)
{
    return ByteOrderSwap16LittleToHost(IoGetAligned16(p));
}

/**
 * Perform an aligned memory read of the little endian
 * byte ordered 32-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An aligned pointer address to read
 *                    the 32-bit little endian byte ordered value from.
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoLittleEndianGetAligned32(const void *p)
{
    return ByteOrderSwap32LittleToHost(IoGetAligned32(p));
}

/**
 * Perform an aligned memory read of the little endian
 * byte ordered 64-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An aligned pointer address to read
 *                    the 64-bit little endian byte ordered value from.
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoLittleEndianGetAligned64(const void *p)
{
    return ByteOrderSwap64LittleToHost(IoGetAligned64(p));
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 8-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      An aligned pointer address to write
 *                    the target system byte ordered 8-bit value to in little
 *                    endian byte ordering.
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     IoLittleEndianPutAligned8(void *p, uint8_t v)
{
    IoPutAligned8(p, v);
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 16-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      An aligned pointer address to write
 *                    the target system byte ordered 16-bit value to in little
 *                    endian byte ordering.
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     IoLittleEndianPutAligned16(void *p, uint16_t v)
{
    IoPutAligned16(p, ByteOrderSwap16HostToLittle(v));
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 32-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      An aligned pointer address to write
 *                    the target system byte ordered 32-bit value to in little
 *                    endian byte ordering.
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     IoLittleEndianPutAligned32(void *p, uint32_t v)
{
    IoPutAligned32(p, ByteOrderSwap32HostToLittle(v));
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 64-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      An aligned pointer address to write
 *                    the target system byte ordered 64-bit value to in little
 *                    endian byte ordering.
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     IoLittleEndianPutAligned64(void *p, uint64_t v)
{
    IoPutAligned64(p, ByteOrderSwap64HostToLittle(v));
}

/**
 * Perform an aligned memory read of the little endian
 * byte ordered 8-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 8-bits (1 byte).
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to read the 8-bit little endian byte
 *                    ordered value from and to then increment by 8-
 *                    bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoLittleEndianReadAligned8(const void **p)
{
    return IoReadAligned8(p);
}

/**
 * Perform an aligned memory read of the little endian
 * byte ordered 16-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to read the 16-bit little endian byte
 *                    ordered value from and to then increment by 16-
 *                    bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoLittleEndianReadAligned16(const void **p)
{
    return ByteOrderSwap16LittleToHost(IoReadAligned16(p));
}

/**
 * Perform an aligned memory read of the little endian
 * byte ordered 32-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to read the 32-bit little endian byte
 *                    ordered value from and to then increment by 32-
 *                    bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoLittleEndianReadAligned32(const void **p)
{
    return ByteOrderSwap32LittleToHost(IoReadAligned32(p));
}

/**
 * Perform an aligned memory read of the little endian
 * byte ordered 64-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to read the 64-bit little endian byte
 *                    ordered value from and to then increment by 64-
 *                    bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoLittleEndianReadAligned64(const void **p)
{
    return ByteOrderSwap64LittleToHost(IoReadAligned64(p));
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 8-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to write the target system byte
 *                    ordered 8-bit value to in little endian byte
 *                    ordering and to then increment by 8-bits (1
 *                    byte).
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     IoLittleEndianWriteAligned8(void **p, uint8_t v)
{
    IoWriteAligned8(p, v);
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 16-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to write the target system byte
 *                    ordered 16-bit value to in little endian byte
 *                    ordering and to then increment by 16-bits (2
 *                    bytes).
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     IoLittleEndianWriteAligned16(void **p, uint16_t v)
{
    IoWriteAligned16(p, ByteOrderSwap16HostToLittle(v));
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 32-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to write the target system byte
 *                    ordered 32-bit value to in little endian byte
 *                    ordering and to then increment by 16-bits (4
 *                    bytes).
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     IoLittleEndianWriteAligned32(void **p, uint32_t v)
{
    IoWriteAligned32(p, ByteOrderSwap32HostToLittle(v));
}

/**
 * Perform an aligned memory write of the target system
 * byte ordered 64-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[inout]  p   A pointer to an aligned pointer address, 
 *                    to write the target system byte
 *                    ordered 64-bit value to in little endian byte
 *                    ordering and to then increment by 64-bits (8
 *                    bytes).
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     IoLittleEndianWriteAligned64(void **p, uint64_t v)
{
    IoWriteAligned64(p, ByteOrderSwap64HostToLittle(v));
}

/**
 * Perform an unaligned memory read of the little endian
 * byte ordered 8-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to read
 *                    the 8-bit little endian byte ordered value from.
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoLittleEndianGetUnaligned8(const void *p)
{
    return IoGetUnaligned8(p);
}

/**
 * Perform an unaligned memory read of the little endian
 * byte ordered 16-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to read
 *                    the 16-bit little endian byte ordered value from.
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoLittleEndianGetUnaligned16(const void *p)
{
    return ByteOrderSwap16LittleToHost(IoGetUnaligned16(p));
}

/**
 * Perform an unaligned memory read of the little endian
 * byte ordered 32-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to read
 *                    the 32-bit little endian byte ordered value from.
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoLittleEndianGetUnaligned32(const void *p)
{
    return ByteOrderSwap32LittleToHost(IoGetUnaligned32(p));
}

/**
 * Perform an unaligned memory read of the little endian
 * byte ordered 64-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in target system byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to read
 *                    the 64-bit little endian byte ordered value from.
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoLittleEndianGetUnaligned64(const void *p)
{
    return ByteOrderSwap64LittleToHost(IoGetUnaligned64(p));
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 8-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to write
 *                    the target system byte ordered 8-bit value to in little
 *                    endian byte ordering.
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     IoLittleEndianPutUnaligned8(void *p, uint8_t v)
{
    IoPutUnaligned8(p, v);
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 16-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to write
 *                    the target system byte ordered 16-bit value to in little
 *                    endian byte ordering.
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     IoLittleEndianPutUnaligned16(void *p, uint16_t v)
{
    IoPutUnaligned16(p, ByteOrderSwap16HostToLittle(v));
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 32-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to write
 *                    the target system byte ordered 32-bit value to in little
 *                    endian byte ordering.
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     IoLittleEndianPutUnaligned32(void *p, uint32_t v)
{
    IoPutUnaligned32(p, ByteOrderSwap32HostToLittle(v));
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 64-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[in]  p      An unaligned pointer address to write
 *                    the target system byte ordered 64-bit value to in little
 *                    endian byte ordering.
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     IoLittleEndianPutUnaligned64(void *p, uint64_t v)
{
    IoPutUnaligned64(p, ByteOrderSwap64HostToLittle(v));
}

/**
 * Perform an unaligned memory read of the little endian
 * byte ordered 8-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 8-bits (1 byte).
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to read the 8-bit little endian byte
 *                    ordered value from and to then increment by 8-
 *                    bits (1 byte).
 *
 * @return The 8-bit value at the specified pointer address.
 */
static inline uint8_t  IoLittleEndianReadUnaligned8(const void **p)
{
    return IoReadUnaligned8(p);
}

/**
 * Perform an unaligned memory read of the little endian
 * byte ordered 16-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 16-bits (2 bytes).
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to read the 16-bit little endian byte
 *                    ordered value from and to then increment by 16-
 *                    bits (2 bytes).
 *
 * @return The 16-bit value at the specified pointer address.
 */
static inline uint16_t IoLittleEndianReadUnaligned16(const void **p)
{
    return ByteOrderSwap16LittleToHost(IoReadUnaligned16(p));
}

/**
 * Perform an unaligned memory read of the little endian
 * byte ordered 32-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 32-bits (4 bytes).
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to read the 32-bit little endian byte
 *                    ordered value from and to then increment by 32-
 *                    bits (4 bytes).
 *
 * @return The 32-bit value at the specified pointer address.
 */
static inline uint32_t IoLittleEndianReadUnaligned32(const void **p)
{
    return ByteOrderSwap32LittleToHost(IoReadUnaligned32(p));
}

/**
 * Perform an unaligned memory read of the little endian
 * byte ordered 64-bit value from the specified pointer address,
 * perform byte reordering, as necessary, for the target system to put
 * the value in target system byte ordering, and increment the pointer
 * by 64-bits (8 bytes).
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to read the 64-bit little endian byte
 *                    ordered value from and to then increment by 64-
 *                    bits (8 bytes).
 *
 * @return The 64-bit value at the specified pointer address.
 */
static inline uint64_t IoLittleEndianReadUnaligned64(const void **p)
{
    return ByteOrderSwap64LittleToHost(IoReadUnaligned64(p));
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 8-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to write the target system byte
 *                    ordered 8-bit value to in little endian byte
 *                    ordering and to then increment by 8-bits (1
 *                    byte).
 *
 * @param[in]  v      The 8-bit value to write.
 *
 */
static inline void     IoLittleEndianWriteUnaligned8(void **p, uint8_t v)
{
    IoWriteUnaligned8(p, v);
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 16-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to write the target system byte
 *                    ordered 16-bit value to in little endian byte
 *                    ordering and to then increment by 16-bits (2
 *                    bytes).
 *
 * @param[in]  v      The 16-bit value to write.
 *
 */
static inline void     IoLittleEndianWriteUnaligned16(void **p, uint16_t v)
{
    IoWriteUnaligned16(p, ByteOrderSwap16HostToLittle(v));
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 32-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to write the target system byte
 *                    ordered 32-bit value to in little endian byte
 *                    ordering and to then increment by 32-bits (4
 *                    bytes).
 *
 * @param[in]  v      The 32-bit value to write.
 *
 */
static inline void     IoLittleEndianWriteUnaligned32(void **p, uint32_t v)
{
    IoWriteUnaligned32(p, ByteOrderSwap32HostToLittle(v));
}

/**
 * Perform an unaligned memory write of the target system
 * byte ordered 64-bit value to the specified pointer address,
 * perform byte reordering, as necessary, for the target system to
 * put the value in little endian byte ordering.
 *
 * @param[inout]  p   A pointer to an unaligined pointer address, 
 *                    to write the target system byte
 *                    ordered 64-bit value to in little endian byte
 *                    ordering and to then increment by 64-bits (8
 *                    bytes).
 *
 * @param[in]  v      The 64-bit value to write.
 *
 */
static inline void     IoLittleEndianWriteUnaligned64(void **p, uint64_t v)
{
    IoWriteUnaligned64(p, ByteOrderSwap64HostToLittle(v));
}

#ifdef __cplusplus
}
#endif
