/** 
 * @file 
 * @brief Overclock
 * @author Miroslav Nemecek <Panda38@seznam.cz>
 * @see OverclockGroup
*/

#ifndef _OVERCLOCK_H
#define _OVERCLOCK_H

#include "pico/stdlib.h"

/**
 * @addtogroup OverclockGroup
 * @details Some display functions may be CPU speed intensive and may require overclocking to a higher speed. It should be 
 * understood that overclocking places the processor in areas where proper function is not guaranteed. The PicoVGA library 
 * allows you to control the overclocking of the processor, according to the desired video mode. The minimum and maximum 
 * processor frequency can be specified in the VgaCfg function. By default, the library allows a range of 120 to 270 MHz. 
 * However, it may happen that at higher frequencies the processor will not operate correctly and it may be necessary to 
 * lower the upper limit.
 * The searched processor frequency can be set with the set_sys_clock_pll() function.
 * @{
*/

/**
 * @brief Search PLL setup
 * @details Function for finding the optimal setting of the PLL system clock generator. The function is used to specify the 
 * desired output frequency, the input frequency of the crystal (12 MHz in Raspberry Pico), the minimum and maximum frequency 
 * of the VCO oscillator. The output is the parameters for setting the PLL oscillator. The function returns True if it was 
 * able to find a setting for the exact value of the desired frequency. Otherwise, it searches for the setting for the closest 
 * frequency and returns False.
 * @param reqkhz Required output frequency in kHz
 * @param input PLL input frequency in kHz (default 12000, or use clock_get_hz(clk_ref)/1000)
 * @param vcomin Minimal VCO frequency in kHz (default 400000)
 * @param vcomax Maximal VCO frequency in kHz (default 1600000)
 * @param lowvco Prefer low VCO (lower power but more jiter)
 * @param outkhz Output achieved frequency in kHz (0=not found)
 * @param outvco Output VCO frequency in kHz
 * @param outfbdiv Output fbdiv (16..320)
 * @param outpd1 Output postdiv1 (1..7)
 * @param outpd2 Output postdiv2 (1..7)
 * @returns True if precise frequency has been found, or near frequency used otherwise.
*/
bool vcocalc(u32 reqkhz, u32 input, u32 vcomin, u32 vcomax, bool lowvco,
		u32* outkhz, u32* outvco, u16* outfbdiv, u8* outpd1, u8* outpd2);

/**
 * @brief Find PLL generator settings with default parameters. (use set_sys_clock_pll to set sysclock)
 * @param reqkhz Required frequency in kHz
 * @param outkhz Output achieved frequency in kHz (0=not found)
 * @param outvco Output VCO frequency in kHz
 * @param outfbdiv Output fbdiv (16..320)
 * @param outpd1 Output postdiv1 (1..7)
 * @param outpd2 Output postdiv2 (1..7)
 * @returns True if precise frequency has been found, or near frequency used otherwise.
*/
bool FindSysClock(u32 reqkhz, u32* outkhz, u32* outvco, u16* outfbdiv, u8* outpd1, u8* outpd2);

/**
 * @brief Setting the interface speed for external flash.
 * @param baud Flash SSI speed (4 default, <4 faster, >4 slower)
*/
void __not_in_flash_func(FlashSpeedSetup)(int baud);

/// @}

#endif // _OVERCLOCK_H
