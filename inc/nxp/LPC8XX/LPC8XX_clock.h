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
LPC800 series common clocking functions
*/
#ifndef LPC8XX_CLOCK_H
#define LPC8XX_CLOCK_H

/* Internal oscillator frequency */
#define SYSCTL_IRC_FREQ     (12000000)
#ifndef MAX_CLOCK_FREQ
#define MAX_CLOCK_FREQ        (30000000)
#endif

typedef enum CHIP_SYSCTL_PLLCLKSRC {
    SYSCTL_PLLCLKSRC_IRC = 0,        /*!< Internal oscillator */
    SYSCTL_PLLCLKSRC_SYSOSC,        /*!< Crystal (system) oscillator */
    SYSCTL_PLLCLKSRC_RESERVED,
    SYSCTL_PLLCLKSRC_EXT_CLKIN,    /*!< External clock input */
} CHIP_SYSCTL_PLLCLKSRC_T;

typedef enum CHIP_WDTLFO_OSC {
    WDTLFO_OSC_ILLEGAL,
    WDTLFO_OSC_0_60,
    WDTLFO_OSC_1_05,
    WDTLFO_OSC_1_40,
    WDTLFO_OSC_1_75,
    WDTLFO_OSC_2_10,
    WDTLFO_OSC_2_40,
    WDTLFO_OSC_2_70,
    WDTLFO_OSC_3_00,
    WDTLFO_OSC_3_25,
    WDTLFO_OSC_3_50,
    WDTLFO_OSC_3_75,
    WDTLFO_OSC_4_00,
    WDTLFO_OSC_4_20,
    WDTLFO_OSC_4_40,
    WDTLFO_OSC_4_60
} CHIP_WDTLFO_OSC_T;

typedef enum CHIP_SYSCTL_MAINCLKSRC {
    SYSCTL_MAINCLKSRC_IRC = 0,
    SYSCTL_MAINCLKSRC_PLLIN,
    SYSCTL_MAINCLKSRC_WDTOSC,
    SYSCTL_MAINCLKSRC_PLLOUT,
} CHIP_SYSCTL_MAINCLKSRC_T;

typedef enum CHIP_SYSCTL_CLOCK {
    SYSCTL_CLOCK_SYS = 0,    /*!< System clock */
    SYSCTL_CLOCK_ROM,        /*!< ROM clock */
    SYSCTL_CLOCK_RAM,        /*!< RAM clock */
    SYSCTL_CLOCK_FLASHREG,    /*!< FLASH register interface clock */
    SYSCTL_CLOCK_FLASH,        /*!< FLASH array access clock */
    SYSCTL_CLOCK_I2C0,        /*!< I2C0 clock */
    SYSCTL_CLOCK_GPIO,        /*!< GPIO clock */
    SYSCTL_CLOCK_SWM,        /*!< Switch matrix clock */
    SYSCTL_CLOCK_SCT,        /*!< State configurable timer clock */
    SYSCTL_CLOCK_WKT,        /*!< Self wake-up timer clock */
    SYSCTL_CLOCK_MRT,        /*!< Multi-rate timer clock */
    SYSCTL_CLOCK_SPI0,        /*!< SPI0 clock */
    SYSCTL_CLOCK_SPI1,        /*!< SPI01 clock */
    SYSCTL_CLOCK_CRC,        /*!< CRC clock */
    SYSCTL_CLOCK_UART0,        /*!< UART0 clock */
    SYSCTL_CLOCK_UART1,        /*!< UART1 clock */
    SYSCTL_CLOCK_UART2,        /*!< UART2 clock */
    SYSCTL_CLOCK_WWDT,        /*!< Watchdog clock */
    SYSCTL_CLOCK_IOCON,        /*!< IOCON clock */
    SYSCTL_CLOCK_ACOMP,        /*!< Analog comparator clock */

    /* LPC82x Specific Clocks */
    SYSCTL_CLOCK_I2C1 = 21, /*!< I2C1 Clock */
    SYSCTL_CLOCK_I2C2,      /*!< I2C2 Clock */
    SYSCTL_CLOCK_I2C3,      /*!< I2C3 Clock */
    SYSCTL_CLOCK_ADC,       /*!< 12-Bit ADC Clock */
    SYSCTL_CLOCK_MTB = 26,  /*!< Macro Trace Buffer [USED FOR DEBUGGING] */
    SYSCTL_CLOCK_DMA = 29,  /*!< DMA Clock */
} CHIP_SYSCTL_CLOCK_T;

typedef enum CHIP_SYSCTL_CLKOUTSRC {
    SYSCTL_CLKOUTSRC_IRC = 0,        /*!< Internal oscillator for CLKOUT */
    SYSCTL_CLKOUTSRC_SYSOSC,        /*!< System oscillator for CLKOUT */
    SYSCTL_CLKOUTSRC_WDTOSC,        /*!< Watchdog oscillator for CLKOUT */
    SYSCTL_CLKOUTSRC_MAINSYSCLK,    /*!< Main system clock for CLKOUT */
} CHIP_SYSCTL_CLKOUTSRC_T;

static inline void Chip_Clock_SetupSystemPLL(uint8_t msel, uint8_t psel)
{
    LPC_SYSCTL->SYSPLLCTRL = (msel & 0x1F) | ((psel & 0x3) << 5);
}

static inline bool Chip_Clock_IsSystemPLLLocked(void)
{
    return (bool) ((LPC_SYSCTL->SYSPLLSTAT & 1) != 0);
}

static inline void Chip_Clock_SetWDTOSC(CHIP_WDTLFO_OSC_T wdtclk, uint8_t div)
{
    LPC_SYSCTL->WDTOSCCTRL  = (((uint32_t) wdtclk) << 5) | ((div >> 1) - 1);
}

static inline CHIP_SYSCTL_MAINCLKSRC_T Chip_Clock_GetMainClockSource(void)
{
    return (CHIP_SYSCTL_MAINCLKSRC_T) (LPC_SYSCTL->MAINCLKSEL & ~SYSCTL_MAINCLKSEL_RESERVED);
}

static inline void Chip_Clock_SetSysClockDiv(uint32_t div)
{
    LPC_SYSCTL->SYSAHBCLKDIV  = div;
}

static inline void Chip_Clock_EnablePeriphClock(CHIP_SYSCTL_CLOCK_T clk)
{
    LPC_SYSCTL->SYSAHBCLKCTRL = (1 << clk) | (LPC_SYSCTL->SYSAHBCLKCTRL & ~SYSCTL_SYSAHBCLKCTRL_RESERVED);
}

static inline void Chip_Clock_DisablePeriphClock(CHIP_SYSCTL_CLOCK_T clk)
{
    LPC_SYSCTL->SYSAHBCLKCTRL &= ~((1 << clk) | SYSCTL_SYSAHBCLKCTRL_RESERVED);
}

static inline void Chip_Clock_SetUARTClockDiv(uint32_t div)
{
    LPC_SYSCTL->UARTCLKDIV = div;
}

static inline uint32_t Chip_Clock_GetUARTClockDiv(void)
{
    return LPC_SYSCTL->UARTCLKDIV & ~SYSCTL_UARTCLKDIV_RESERVED;
}

static inline void Chip_SYSCTL_SetUSARTFRGDivider(uint8_t div)
{
    LPC_SYSCTL->UARTFRGDIV = (uint32_t) div;
}

static inline uint32_t Chip_SYSCTL_GetUSARTFRGDivider(void)
{
    return LPC_SYSCTL->UARTFRGDIV & ~SYSCTL_UARTFRGDIV_RESERVED;
}

static inline void Chip_SYSCTL_SetUSARTFRGMultiplier(uint8_t mult)
{
    LPC_SYSCTL->UARTFRGMULT = (uint32_t) mult;
}

static inline uint32_t Chip_SYSCTL_GetUSARTFRGMultiplier(void)
{
    return LPC_SYSCTL->UARTFRGMULT & ~SYSCTL_UARTFRGMULT_RESERVED;
}

uint32_t Chip_Clock_SetUSARTNBaseClockRate(uint32_t rate, bool fEnable);

uint32_t Chip_Clock_GetUSARTNBaseClockRate(void);


static inline uint32_t Chip_Clock_GetIntOscRate(void)
{
    return SYSCTL_IRC_FREQ;
}

static inline void Chip_Clock_SetSystemPLLSource(CHIP_SYSCTL_PLLCLKSRC_T src)
{
    LPC_SYSCTL->SYSPLLCLKSEL  = (uint32_t) src;
    LPC_SYSCTL->SYSPLLCLKUEN  = 0;
    LPC_SYSCTL->SYSPLLCLKUEN  = 1;
}

static inline void Chip_Clock_SetPLLBypass(bool bypass, bool highfr)
{
    uint32_t ctrl = 0;
    if(bypass)
        ctrl |= (1 << 0);
    if(highfr) 
        ctrl |= (1 << 1);

    LPC_SYSCTL->SYSOSCCTRL = ctrl;
}

static inline void Chip_Clock_SetMainClockSource(CHIP_SYSCTL_MAINCLKSRC_T src)
{
    LPC_SYSCTL->MAINCLKSEL  = (uint32_t) src;
    
    /* sequnce a 0 followed by 1 to update MAINCLK source selection */
    LPC_SYSCTL->MAINCLKUEN  = 0;
    LPC_SYSCTL->MAINCLKUEN  = 1;
}

static inline void Chip_Clock_SetCLKOUTSource(CHIP_SYSCTL_CLKOUTSRC_T src, uint32_t div)
{
    LPC_SYSCTL->CLKOUTSEL = (uint32_t) src;
    
    /* sequnce a 0 followed by 1 to update CLKOUT source selection */
    LPC_SYSCTL->CLKOUTUEN = 0;
    LPC_SYSCTL->CLKOUTUEN = 1;
    LPC_SYSCTL->CLKOUTDIV = div;
}

static inline uint32_t Chip_Clock_GetPLLFreq(uint32_t PLLReg, uint32_t inputRate)
{
    uint32_t m_val = ((PLLReg & 0x1F) + 1);

    return (inputRate * m_val);
}

uint32_t Chip_Clock_GetWDTOSCRate(void);

static inline uint32_t Chip_Clock_GetSystemPLLOutClockRate(void)
{
    return Chip_Clock_GetPLLFreq((LPC_SYSCTL->SYSPLLCTRL & ~SYSCTL_SYSPLLCTRL_RESERVED),
                                 Chip_Clock_GetSystemPLLInClockRate());
}

uint32_t Chip_Clock_GetSystemPLLOutClockRate(void);

static inline uint32_t Chip_Clock_GetSystemPLLInClockRate(void)
{
    uint32_t clkRate;

    switch ((CHIP_SYSCTL_PLLCLKSRC_T) (LPC_SYSCTL->SYSPLLCLKSEL & 0x3)) {
    case SYSCTL_PLLCLKSRC_IRC:
        clkRate = Chip_Clock_GetIntOscRate();
        break;

    case SYSCTL_PLLCLKSRC_SYSOSC:
        clkRate = Chip_Clock_GetMainOscRate();
        break;

    case SYSCTL_PLLCLKSRC_EXT_CLKIN:
        clkRate = Chip_Clock_GetExtClockInRate();
        break;

    default:
        clkRate = 0;
    }

    return clkRate;
}

static inline uint32_t Chip_Clock_GetMainClockRate(void)
{
    uint32_t clkRate = 0;

    switch ((CHIP_SYSCTL_MAINCLKSRC_T) (LPC_SYSCTL->MAINCLKSEL & 0x3)) {
    case SYSCTL_MAINCLKSRC_IRC:
        clkRate = Chip_Clock_GetIntOscRate();
        break;

    case SYSCTL_MAINCLKSRC_PLLIN:
        clkRate = Chip_Clock_GetSystemPLLInClockRate();
        break;

    case SYSCTL_MAINCLKSRC_WDTOSC:
        clkRate = Chip_Clock_GetWDTOSCRate();
        break;

    case SYSCTL_MAINCLKSRC_PLLOUT:
        clkRate = Chip_Clock_GetSystemPLLOutClockRate();
        break;
    }

    return clkRate;
}

static inline uint32_t Chip_Clock_GetSystemClockRate(void)
{
    return Chip_Clock_GetMainClockRate() / (LPC_SYSCTL->SYSAHBCLKDIV & ~SYSCTL_SYSAHBCLKDIV_RESERVED);
}

static inline uint32_t Chip_Clock_GetIOCONCLKDIVClockRate(CHIP_PIN_CLKDIV_T reg)
{
    uint32_t div = LPC_SYSCTL->IOCONCLKDIV[reg] & ~SYSCTL_IOCONCLKDIV_RESERVED;
    uint32_t main_clk = Chip_Clock_GetMainClockRate();
    
    return (div == 0) ? 0 : (main_clk / div);
}

static inline void Chip_Clock_SetIOCONCLKDIV(CHIP_PIN_CLKDIV_T reg, uint8_t div)
{
    int t_reg = IOCONCLK_MAX-reg;
    LPC_SYSCTL->IOCONCLKDIV[t_reg] = div;
}

#endif