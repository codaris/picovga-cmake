
// ****************************************************************************
//
//                                 Main code
//
// ****************************************************************************


#include "picovga.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdio.h>
#include <hardware/structs/dma.h>
#include "vga_config.h"
#include "hardware/pio.h"

extern volatile uint32_t g_isr_count;       // how many times VgaLine() fired
extern volatile uint32_t g_last_scanline;   // last ScanLine observed in ISR
extern volatile uint32_t g_last_linetype;   // last linetype observed in ISR

// Draw box
ALIGNED u8 Box[512*400];

int main()
{
    // initialize videomode
	Video(DEV_VGA, RES_EGA, FORM_8BIT, Box);

	// draw text
	DrawText(&Canvas, "Hello World!", (512-12*8*4)/2, (400-8*4)/2,
		COL_WHITE, FontBoldB8x16, 16, 4, 4);
}
