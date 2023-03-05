
// ****************************************************************************
//
//                           VGA colors and palettes
//
// ****************************************************************************

#ifndef _VGA_PAL_H
#define _VGA_PAL_H

/**
 * @addtogroup Colors
 * @{
*/

/// Multiply color pattern (used in mode GF_COLOR)
#define MULTICOL(a,b,c,d) ((a)|((b)<<8)|((c)<<16)|((d)<<24)) 

// CGA colors
#define CGACOL_0	0	///< CGA 0x000000 black
#define CGACOL_1	2	///< CGA 0x0000C3 dark blue
#define CGACOL_2	20	///< CGA 0x00C300 dark green
#define CGACOL_3	22	///< CGA 0x00C3C3 dark cyan
#define CGACOL_4	160	///< CGA 0xC30000 dark red
#define CGACOL_5	162	///< CGA 0xC300C3 dark magenta
#define CGACOL_6	168	///< CGA 0xC35400 brown
#define CGACOL_7	182	///< CGA 0xC3C3C3 light gray
#define CGACOL_8	73	///< CGA 0x545454 dark gray
#define CGACOL_9	75	///< CGA 0x5454FF light blue
#define CGACOL_10	93	///< CGA 0x54FF54 light green
#define CGACOL_11	95	///< CGA 0x54FFFF light cyan
#define CGACOL_12	233	///< CGA 0xFF5454 light red
#define CGACOL_13	235	///< CGA 0xFF54FF light magenta
#define CGACOL_14	253	///< CGA 0xFFFF54 yellow
#define CGACOL_15	255	///< CGA 0xFFFFFF white

// ZX Spectrum color
#define ZXCOL_0		0	///< ZX Spectrum 0x000000 black
#define ZXCOL_1		2	///< ZX Spectrum 0x0000C3 dark blue
#define ZXCOL_2		160	///< ZX Spectrum 0xC30000 dark red
#define ZXCOL_3		162	///< ZX Spectrum 0xC300C3 dark magenta
#define ZXCOL_4		20	///< ZX Spectrum 0x00C300 dark green
#define ZXCOL_5		22	///< ZX Spectrum 0x00C3C3 dark cyan
#define ZXCOL_6		180	///< ZX Spectrum 0xC3C300 dark yellow
#define ZXCOL_7		182	///< ZX Spectrum 0xC3C3C3 light gray
#define ZXCOL_8		73	///< ZX Spectrum 0x545454 dark gray
#define ZXCOL_9		3	///< ZX Spectrum 0x0000FF light blue
#define ZXCOL_10	224	///< ZX Spectrum 0xFF0000 light red
#define ZXCOL_11	227	///< ZX Spectrum 0xFF00FF light magenta
#define ZXCOL_12	28	///< ZX Spectrum 0x00FF00 light green
#define ZXCOL_13	31	///< ZX Spectrum 0x00FFFF light cyan
#define ZXCOL_14	252	///< ZX Spectrum 0xFFFF00 yellow
#define ZXCOL_15	255	///< ZX Spectrum 0xFFFFFF white

// Colors
//	GP0 ... B0 ... VGA B0 blue
//	GP1 ... B1 ... VGA B1
//	GP2 ... B2 ... VGA G0 green
//	GP3 ... B3 ... VGA G1
//	GP4 ... B4 ... VGA G2
//	GP5 ... B5 ... VGA R0 red
//	GP6 ... B6 ... VGA R1
//	GP7 ... B7 ... VGA R2

#define COL_BLACK	0

#define COL_DARKBLUE	B0
#define COL_SEMIBLUE	B1
#define COL_BLUE	(B0+B1)
#define COL_MOREBLUE	(COL_BLUE+B3+B6)
#define COL_LIGHTBLUE	(COL_BLUE+B4+B7)

#define COL_DARKGREEN	B3
#define COL_SEMIGREEN	B4
#define COL_GREEN	(B2+B3+B4)
#define COL_MOREGREEN	(COL_GREEN+B0+B6)
#define COL_LIGHTGREEN	(COL_GREEN+B1+B7)

#define COL_DARKRED	B6
#define COL_SEMIRED	B7
#define COL_RED		(B5+B6+B7)
#define COL_MORERED	(COL_RED+B0+B3)
#define COL_LIGHTRED	(COL_RED+B1+B4)

#define COL_DARKCYAN	(B0+B3)
#define COL_SEMICYAN	(B1+B4)
#define COL_CYAN	(B0+B1+B2+B3+B4)

#define COL_DARKMAGENTA	(B0+B6)
#define COL_SEMIMAGENTA	(B1+B7)
#define COL_MAGENTA	(B0+B1+B5+B6+B7)

#define COL_DARKYELLOW	(B3+B6)
#define COL_SEMIYELLOW	(B4+B7)
#define COL_YELLOW	(B2+B3+B4+B5+B6+B7)

#define COL_GRAY0	0
#define COL_GRAY1	(B2+B5)
#define COL_GRAY2	(B0+B3+B6)
#define COL_GRAY3	(B0+B2+B3+B5+B6)
#define COL_GRAY4	(B1+B4+B7)
#define COL_GRAY5	(B1+B2+B4+B5+B7)
#define COL_GRAY6	(B0+B1+B3+B4+B6+B7)
#define COL_GRAY7	(B0+B1+B2+B3+B4+B5+B6+B7)

#define COL_WHITE	COL_GRAY7

/// compose color from RGB
#define COLRGB(r,g,b) ((u8)(((r)&0xe0)|(((g)&0xe0)>>3)|((b)>>6)))

/// default 16-color palettes (CGA colors)
extern u8 DefPal16[16];     // - do not set "const", to stay in faster RAM

/// ZX Spectrum color palettes
extern u8 ZXPal16[16];      // - do not set "const", to stay in faster RAM

// 4-color palettes (CGA colors) 
// - do not set "const", to stay in faster RAM
extern u8 PalCGA1[4]; ///< 4-color CGA palette 0, low intensity (black, dark green, brown)
extern u8 PalCGA2[4]; ///< 4-color CGA palette 0, high intensity (black, light green, light red, yellow)
extern u8 PalCGA3[4]; ///< 4-color CGA palette 1, low intensity (black, dark cyan, dark magenta, light gray)
extern u8 PalCGA4[4]; ///< 4-color CGA palette 1, high intensity (black, light cyan, light magenta, white)
extern u8 PalCGA5[4]; ///< 4-color CGA palette 1, low intensity (black, dark cyan, dark red, light gray)
extern u8 PalCGA6[4]; ///< 4-color CGA palette 1, high intensity (black, light cyan, light red, white)

// 4-color palette translation table
//extern u32 Pal4Trans[256];
//extern u32 Pal4Plane[256];

// 16-color palette translation table
//extern u16 Pal16Trans[256];
//extern u16 ZX16Trans[256];

// values of color components
extern u8 RGVal[8];     ///< Values of Red and Green components
extern u8 BVal[4];      ///< Values of Blue components

/**
 * @brief Distance of 2 colors in 332 format (R3G3B2)
 * @param col1 First color
 * @param col2 Second color
 * @returns Distance value 0..195075
*/
int ColDist(u8 col1, u8 col2);

/**
 * @brief Generate gradient
 * @param dst Destination
 * @param w Width
*/
void GenGrad(u8* dst, int w);

/// @}

#endif // _VGA_PAL_H
