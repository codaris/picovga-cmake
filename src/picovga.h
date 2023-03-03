
// ****************************************************************************
//                                 
//                           Global common definitions
//
// ****************************************************************************

// ----------------------------------------------------------------------------
//                              Base data types
// ----------------------------------------------------------------------------

#ifndef _PICOVGA_H
#define _PICOVGA_H

//!@addtogroup VideoInit Video Initialization
//!@addtogroup VideoMode Video mode configuration
//!@addtogroup Screen Screen layout

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed long int s32;
typedef unsigned long int u32;
typedef signed long long int s64;
typedef unsigned long long int u64;

typedef unsigned int uint;

typedef unsigned char Bool;
#define True 1
#define False 0

// NULL
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif
#endif

// I/O port prefix
#define __IO	volatile

// request to use inline
#define INLINE __attribute__((always_inline)) inline

// avoid to use inline
#define NOINLINE __attribute__((noinline))

// weak function
#define WEAK __attribute__((weak))

// align array to 4-bytes
#define ALIGNED __attribute__((aligned(4)))

#define LED_PIN 25

// ----------------------------------------------------------------------------
//                               Constants
// ----------------------------------------------------------------------------

#define	B0 (1<<0)
#define	B1 (1<<1)
#define	B2 (1<<2)
#define	B3 (1<<3)
#define	B4 (1<<4)
#define	B5 (1<<5)
#define	B6 (1<<6)
#define	B7 (1<<7)
#define	B8 (1U<<8)
#define	B9 (1U<<9)
#define	B10 (1U<<10)
#define	B11 (1U<<11)
#define	B12 (1U<<12)
#define	B13 (1U<<13)
#define	B14 (1U<<14)
#define	B15 (1U<<15)
#define B16 (1UL<<16)
#define B17 (1UL<<17)
#define B18 (1UL<<18)
#define	B19 (1UL<<19)
#define B20 (1UL<<20)
#define B21 (1UL<<21)
#define B22 (1UL<<22)
#define B23 (1UL<<23)
#define B24 (1UL<<24)
#define B25 (1UL<<25)
#define B26 (1UL<<26)
#define B27 (1UL<<27)
#define B28 (1UL<<28)
#define B29 (1UL<<29)
#define B30 (1UL<<30)
#define B31 (1UL<<31)

#define BIT(pos) (1UL<<(pos))

#define	BIGINT	0x40000000 // big int value

#define _T(a) a

#define PI 3.14159265358979324
#define PI2 (3.14159265358979324*2)

// ----------------------------------------------------------------------------
//                                   Includes
// ----------------------------------------------------------------------------

// fonts
extern const ALIGNED u8 FontBold8x8[2048];
extern const ALIGNED u8 FontBold8x14[3584];
extern const ALIGNED u8 FontBold8x16[4096];
extern const ALIGNED u8 FontBoldB8x14[3584];
extern const ALIGNED u8 FontBoldB8x16[4096];
extern const ALIGNED u8 FontGame8x8[2048];
extern const ALIGNED u8 FontIbm8x8[2048];
extern const ALIGNED u8 FontIbm8x14[3584];
extern const ALIGNED u8 FontIbm8x16[4096];
extern const ALIGNED u8 FontIbmTiny8x8[2048];
extern const ALIGNED u8 FontItalic8x8[2048];
extern const ALIGNED u8 FontThin8x8[2048];

// PicoVGA includes
#include "define.h"	// common definitions of C and ASM
#include "util/canvas.h" // canvas
#include "util/overclock.h" // overclock
#include "util/print.h" // print to attribute text buffer
#include "util/rand.h"	// random number generator
#include "util/mat2d.h" // 2D transformation matrix
#include "util/pwmsnd.h" // PWM sound output
#include "vga_pal.h"	// VGA colors and palettes
#include "vga_vmode.h"	// VGA videomodes
#include "vga_layer.h"	// VGA layers
#include "vga_screen.h" // VGA screen layout
#include "vga_util.h"	// VGA utilities
#include "vga.h"	 // VGA output

#endif
