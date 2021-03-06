/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>
*/
/* 
LPC800 series common cyclic redudancy check registers, definitions and 
functions.
*/
#ifndef LPC8XX_CRC_H
#define LPC8XX_CRC_H

/* CRC register block structure */
typedef struct {                
    __IO uint32_t MODE;         /* CRC Mode Register */
    __IO uint32_t SEED;         /* CRC SEED Register */
    union {
        __I uint32_t SUM;       /* CRC Checksum Register. */
        __O uint32_t WRDATA32;  /* CRC Data Register: write size 32-bit */
        __O uint16_t WRDATA16;  /* CRC Data Register: write size 16-bit */
        __O uint8_t  WRDATA8;   /* CRC Data Register: write size 8-bit */
    };
} LPC_CRC_T;

/* CRC MODE register description */
#define CRC_MODE_POLY_BITMASK   ((0x03))    /** CRC polynomial Bit mask */
#define CRC_MODE_POLY_CCITT     (0x00)        /** Select CRC-CCITT polynomial */
#define CRC_MODE_POLY_CRC16     (0x01)        /** Select CRC-16 polynomial */
#define CRC_MODE_POLY_CRC32     (0x02)        /** Select CRC-32 polynomial */
#define CRC_MODE_WRDATA_BITMASK (0x03 << 2)    /** CRC WR_Data Config Bit mask */
#define CRC_MODE_WRDATA_BIT_RVS (1 << 2)    /** Select Bit order reverse for WR_DATA (per byte) */
#define CRC_MODE_WRDATA_CMPL    (1 << 3)    /** Select One's complement for WR_DATA */
#define CRC_MODE_SUM_BITMASK    (0x03 << 4)    /** CRC Sum Config Bit mask */
#define CRC_MODE_SUM_BIT_RVS    (1 << 4)    /** Select Bit order reverse for CRC_SUM */
#define CRC_MODE_SUM_CMPL       (1 << 5)    /** Select One's complement for CRC_SUM */

#define MODE_CFG_CCITT          (0x00)    /** Pre-defined mode word for default CCITT setup */
#define MODE_CFG_CRC16          (0x15)    /** Pre-defined mode word for default CRC16 setup */
#define MODE_CFG_CRC32          (0x36)    /** Pre-defined mode word for default CRC32 setup */

#define CRC_SEED_CCITT          (0x0000FFFF)/** Initial seed value for CCITT mode */
#define CRC_SEED_CRC16          (0x00000000)/** Initial seed value for CRC16 mode */
#define CRC_SEED_CRC32          (0xFFFFFFFF)/** Initial seed value for CRC32 mode */

/* CRC polynomial */
typedef enum IP_CRC_001_POLY {
    CRC_POLY_CCITT = CRC_MODE_POLY_CCITT,    /**< CRC-CCIT polynomial */
    CRC_POLY_CRC16 = CRC_MODE_POLY_CRC16,    /**< CRC-16 polynomial */
    CRC_POLY_CRC32 = CRC_MODE_POLY_CRC32,    /**< CRC-32 polynomial */
    CRC_POLY_LAST,
} CRC_POLY_T;

static inline void CrcInit(void)
{
    ClockEnablePeriphClock(SYSCTL_CLOCK_CRC);
}

static inline void CrcDeinit(void)
{
    ClockDisablePeriphClock(SYSCTL_CLOCK_CRC);
}

static inline void CrcSetPoly(CRC_POLY_T poly, uint32_t flags)
{
    LPC_CRC->MODE = (uint32_t) poly | flags;
}

static inline void CrcUseCRC16(void)
{
    LPC_CRC->MODE = MODE_CFG_CRC16;
    LPC_CRC->SEED = CRC_SEED_CRC16;
}

static inline void CrcUseCRC32(void)
{
    LPC_CRC->MODE = MODE_CFG_CRC32;
    LPC_CRC->SEED = CRC_SEED_CRC32;
}

static inline void CrcUseCCITT(void)
{
    LPC_CRC->MODE = MODE_CFG_CCITT;
    LPC_CRC->SEED = CRC_SEED_CCITT;
}

void CrcUseDefaultConfig(CRC_POLY_T poly);

static inline void CrcSetMode(uint32_t mode)
{
    LPC_CRC->MODE = mode;
}

static inline uint32_t CrcGetMode(void)
{
    return LPC_CRC->MODE;
}

static inline void CrcSetSeed(uint32_t seed)
{
    LPC_CRC->SEED = seed;
}

static inline uint32_t CrcGetSeed(void)
{
    return LPC_CRC->SEED;
}

static inline void CrcWrite8(uint8_t data)
{
    LPC_CRC->WRDATA8 = data;
}

static inline void CrcWrite16(uint16_t data)
{
    LPC_CRC->WRDATA16 = data;
}

static inline void CrcWrite32(uint32_t data)
{
    LPC_CRC->WRDATA32 = data;
}

static inline uint32_t CrcSum(void)
{
    return LPC_CRC->SUM;
}

static inline uint32_t CrcCRC8(const uint8_t *data, uint32_t bytes)
{
    CrcUseCCITT();
    while (bytes > 0) {
        CrcWrite8(*data);
        data++;
        bytes--;
    }
    return CrcSum();
}

static inline uint32_t CrcCRC16(const uint16_t *data, uint32_t hwords)
{
    CrcUseCRC16();
    while (hwords > 0) {
        CrcWrite16(*data);
        data++;
        hwords--;
    }
    return CrcSum();
}

static inline uint32_t CrcCRC32(const uint32_t *data, uint32_t words)
{
    CrcUseCRC32();
    while (words > 0) {
        CrcWrite32(*data);
        data++;
        words--;
    }
    return CrcSum();
}

#endif