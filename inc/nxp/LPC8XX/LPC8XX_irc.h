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
LPC800 series common internal RC oscillator registers, defines and 
functions.
*/
#ifndef LPC8XX_IRC_H
#define LPC8XX_IRC_H

 typedef struct {
    uint16_t    freq_main;            //    main clock frequency in MHz
    uint16_t    freq_sys;            //    system (CPU) clock frequency in MHz
    uint16_t    freq_fcco;            //    FCCO clock frequency in MHz
    uint16_t    msel;                //    MSEL (pre-decremented)
    uint16_t    psel;                //    PSEL (pre-decremented)
    uint16_t    divider;            //    SYSAHBCLKDIV
} LPC_8XX_PLL_T;

/*
 *    This table contains all useful PLL configurations
 *    for "integer" MHZ (e.g. 1MHz, 2MHz, etc.) frequencies.
 *
 *    This table has two inputs:
 *    - freq_main: This is the main frequency.
 *    - freq_sys: This is the system (CPU) frequency.
 *    These are used to select which table entry to use.
 *
 *    There are many ways to get some frequencies. For example,
 *    there are eight ways to make the CPU run at 12MHZ. If the peripheral bus
 *    needs to run very fast, it's possible to set the main clock
 *    up to 96MHz. If low power is a requirement, it's possible to set the main
 *    clock to 12MHz.
 *
 *    All the rest of the table entries are outputs.
 *    - freq_fcco is simply an FYI value. It is not used for programming.
 *    - MSEL / PSEL / divider are used to program the PLL.
 */
static const LPC_8XX_PLL_T config_tab[] = {
    {      12,   12,  192,    0,    3,    1    },        // 12.0000MHz
    {      12,    6,  192,    0,    3,    2    },        //  6.0000MHz
    {      12,    4,  192,    0,    3,    3    },        //  4.0000MHz
    {      12,    3,  192,    0,    3,    4    },        //  3.0000MHz
    {      12,    2,  192,    0,    3,    6    },        //  2.0000MHz
    {      12,    1,  192,    0,    3,   12    },        //  1.0000MHz
    {      24,   24,  192,    1,    2,    1    },        // 24.0000MHz
    {      24,   12,  192,    1,    2,    2    },        // 12.0000MHz
    {      24,    8,  192,    1,    2,    3    },        //  8.0000MHz
    {      24,    6,  192,    1,    2,    4    },        //  6.0000MHz
    {      24,    4,  192,    1,    2,    6    },        //  4.0000MHz
    {      24,    3,  192,    1,    2,    8    },        //  3.0000MHz
    {      24,    2,  192,    1,    2,   12    },        //  2.0000MHz
    {      24,    1,  192,    1,    2,   24    },        //  1.0000MHz
    {      36,   18,  288,    2,    2,    2    },        // 18.0000MHz
    {      36,   12,  288,    2,    2,    3    },        // 12.0000MHz
    {      36,    9,  288,    2,    2,    4    },        //  9.0000MHz
    {      36,    6,  288,    2,    2,    6    },        //  6.0000MHz
    {      36,    4,  288,    2,    2,    9    },        //  4.0000MHz
    {      36,    3,  288,    2,    2,   12    },        //  3.0000MHz
    {      36,    2,  288,    2,    2,   18    },        //  2.0000MHz
    {      36,    1,  288,    2,    2,   36    },        //  1.0000MHz
    {      48,   24,  192,    3,    1,    2    },        // 24.0000MHz
    {      48,   16,  192,    3,    1,    3    },        // 16.0000MHz
    {      48,   12,  192,    3,    1,    4    },        // 12.0000MHz
    {      48,    8,  192,    3,    1,    6    },        //  8.0000MHz
    {      48,    6,  192,    3,    1,    8    },        //  6.0000MHz
    {      48,    4,  192,    3,    1,   12    },        //  4.0000MHz
    {      48,    3,  192,    3,    1,   16    },        //  3.0000MHz
    {      48,    2,  192,    3,    1,   24    },        //  2.0000MHz
    {      48,    1,  192,    3,    1,   48    },        //  1.0000MHz
    {      60,   30,  240,    4,    1,    2    },        // 30.0000MHz
    {      60,   20,  240,    4,    1,    3    },        // 20.0000MHz
    {      60,   15,  240,    4,    1,    4    },        // 15.0000MHz
    {      60,   12,  240,    4,    1,    5    },        // 12.0000MHz
    {      60,   10,  240,    4,    1,    6    },        // 10.0000MHz
    {      60,    6,  240,    4,    1,   10    },        //  6.0000MHz
    {      60,    5,  240,    4,    1,   12    },        //  5.0000MHz
    {      60,    4,  240,    4,    1,   15    },        //  4.0000MHz
    {      60,    3,  240,    4,    1,   20    },        //  3.0000MHz
    {      60,    2,  240,    4,    1,   30    },        //  2.0000MHz
    {      60,    1,  240,    4,    1,   60    },        //  1.0000MHz
    {      72,   24,  288,    5,    1,    3    },        // 24.0000MHz
    {      72,   18,  288,    5,    1,    4    },        // 18.0000MHz
    {      72,   12,  288,    5,    1,    6    },        // 12.0000MHz
    {      72,    9,  288,    5,    1,    8    },        //  9.0000MHz
    {      72,    8,  288,    5,    1,    9    },        //  8.0000MHz
    {      72,    6,  288,    5,    1,   12    },        //  6.0000MHz
    {      72,    4,  288,    5,    1,   18    },        //  4.0000MHz
    {      72,    3,  288,    5,    1,   24    },        //  3.0000MHz
    {      72,    2,  288,    5,    1,   36    },        //  2.0000MHz
    {      72,    1,  288,    5,    1,   72    },        //  1.0000MHz
    {      84,   28,  168,    6,    0,    3    },        // 28.0000MHz
    {      84,   21,  168,    6,    0,    4    },        // 21.0000MHz
    {      84,   14,  168,    6,    0,    6    },        // 14.0000MHz
    {      84,   12,  168,    6,    0,    7    },        // 12.0000MHz
    {      84,    7,  168,    6,    0,   12    },        //  7.0000MHz
    {      84,    6,  168,    6,    0,   14    },        //  6.0000MHz
    {      84,    4,  168,    6,    0,   21    },        //  4.0000MHz
    {      84,    3,  168,    6,    0,   28    },        //  3.0000MHz
    {      84,    2,  168,    6,    0,   42    },        //  2.0000MHz
    {      84,    1,  168,    6,    0,   84    },        //  1.0000MHz
    {      96,   24,  192,    7,    0,    4    },        // 24.0000MHz
    {      96,   16,  192,    7,    0,    6    },        // 16.0000MHz
    {      96,   12,  192,    7,    0,    8    },        // 12.0000MHz
    {      96,    8,  192,    7,    0,   12    },        //  8.0000MHz
    {      96,    6,  192,    7,    0,   16    },        //  6.0000MHz
    {      96,    4,  192,    7,    0,   24    },        //  4.0000MHz
    {      96,    3,  192,    7,    0,   32    },        //  3.0000MHz
    {      96,    2,  192,    7,    0,   48    },        //  2.0000MHz
    {      96,    1,  192,    7,    0,   96    },        //  1.0000MHz
};
static const uint16_t config_tab_ct = sizeof(config_tab) / sizeof(LPC_8XX_PLL_T);

static inline void pllConfig(const LPC_8XX_PLL_T* pll_cfg)
{
    SysctlPowerUp(SYSCTL_SLPWAKE_IRC_PD);              /* turn on the IRC by clearing the power down bit */
    ClockSetSystemPLLSource(SYSCTL_PLLCLKSRC_IRC);      /* select PLL input to be IRC */
    ClockSetMainClockSource(SYSCTL_MAINCLKSRC_IRC);
    FmcSetFlashAccess(FLASHTIM_30MHZ_CPU);             /* setup FLASH access to 2 clocks (up to 30MHz) */
    SysctlPowerDown(SYSCTL_SLPWAKE_SYSPLL_PD);         /* power down PLL to change the PLL divider ratio */
    ClockSetupSystemPLL(pll_cfg->msel, pll_cfg->psel);  /* configure the PLL */
    SysctlPowerUp(SYSCTL_SLPWAKE_SYSPLL_PD);           /* turn on the PLL by clearing the power down bit */
    while (!ClockIsSystemPLLLocked()) {}                /* wait for PLL to lock */
    ClockSetSysClockDiv(pll_cfg->divider);              /* load the divider */
    ClockSetMainClockSource(SYSCTL_MAINCLKSRC_PLLOUT);  /* enable the new Frequency */
}

static inline bool IrcSetFreq(uint32_t main, uint32_t sys)
{
    uint16_t    freq_m = main/1000000;              /* main frequency in MHz */
    uint16_t    freq_s = sys/1000000;               /* system frequency in MHz */
    bool        found = false;                      /* frequencies found */
    uint32_t    i = 0;
    uint16_t config_tab_idx = 0;

    if (freq_s > 30)                                /* if system frequency is higher than 30MHz... */
        return false;                               /* ...don't attempt to set it */
    if (freq_m > 96)                                /* if main frequency is higher than 96MHz... */
        return false;                               /* ...don't attempt to set it */
    
    
    for (i=0; i<config_tab_ct; i++)                 /* loop through table */
    {               
        if ( (freq_m == config_tab[i].freq_main) && /* attempt to find a match */
             (freq_s == config_tab[i].freq_sys)  ) 
        {                                           
            config_tab_idx = i;                     /* save the data for later */
            found = true;                           /* set state to found */
            break;                                  /* go config the PLL */
        }
    }
    if (found == true)                              /* if a match has been found */
        pllConfig(&config_tab[config_tab_idx]);     /* configure the PLL */

    return found;                                   /* return operation status */
}

static inline void IrcSetFreqROM(uint32_t sys)
{
    uint32_t cmd[4], resp[2];

    SysctlPowerUp(SYSCTL_SLPWAKE_IRC_PD);          /* Turn on the IRC by clearing the power down bit */
    ClockSetSystemPLLSource(SYSCTL_PLLCLKSRC_IRC);  /* Select PLL input to be IRC */
    FmcSetFlashAccess(FLASHTIM_30MHZ_CPU);         /* Setup FLASH access to 2 clocks (up to 30MHz) */

    cmd[0] = ClockGetIntOscRate() / 1000;           /* in KHz */
    cmd[1] = sys / 1000;                            /* system clock rate in kHz */
    cmd[2] = CPU_FREQ_EQU;
    cmd[3] = sys / 10000;                           /* Timeout. See UM10601, section 23.4.1.3 for details */
    LPC_PWRD_API->setPll(cmd, resp);                /* Attempt to set the PLL */

    while (resp[0] != PLL_CMD_SUCCESS) {}           /* Dead loop on fail */
}

#endif