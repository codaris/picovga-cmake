
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
    stdio_init_all();
    sleep_ms(10000); // allow USB CDC to connect (helpful on some hosts)

    printf("\n\nPicoVGA test\n");

    // initialize videomode
	Video(DEV_VGA, RES_EGA, FORM_8BIT, Box);

    sleep_ms(1000);

	// draw text
	DrawText(&Canvas, "Hello World!", (512-12*8*4)/2, (400-8*4)/2,
		COL_WHITE, FontBoldB8x16, 16, 4, 4);

    uint32_t last = 0;
    absolute_time_t next = make_timeout_time_ms(1000);

    while (true) {
        if (absolute_time_diff_us(get_absolute_time(), next) <= 0) {
            uint32_t now = g_isr_count;
            uint32_t delta = now - last;
            last = now;

            printf("ISR/s=%lu  last_scanline=%lu  last_linetype=%lu\n",
                   (unsigned long)delta,
                   (unsigned long)g_last_scanline,
                   (unsigned long)g_last_linetype);

            uint32_t c = dma_hw->ch[VGA_DMA_PIO0].ctrl_trig;
            uint32_t i = dma_hw->ints0;
            printf("DMA_PIO0: BUSY=%u  AHB_ERR=%u  READ_ERR=%u  WRITE_ERR=%u  ints0=0x%08lx\n",
            (c >> DMA_CH0_CTRL_TRIG_BUSY_LSB) & 1,
            (c >> DMA_CH0_CTRL_TRIG_AHB_ERROR_LSB) & 1,
            (c >> DMA_CH0_CTRL_TRIG_READ_ERROR_LSB) & 1,
            (c >> DMA_CH0_CTRL_TRIG_WRITE_ERROR_LSB) & 1,
            (unsigned long)i);                   

            printf("DATA: cnt=%u rd=%08x wr=%08x ctrl=%08x\n",
                dma_hw->ch[VGA_DMA_PIO0].transfer_count,
                (unsigned)dma_hw->ch[VGA_DMA_PIO0].read_addr,
                (unsigned)&VGA_PIO->txf[VGA_SM(0)],
                dma_hw->ch[VGA_DMA_PIO0].ctrl_trig);
            printf("CB0:  cnt=%u rd=%08x wr=%08x ctrl=%08x\n",
                dma_hw->ch[VGA_DMA_CB0].transfer_count,
                (unsigned)dma_hw->ch[VGA_DMA_CB0].read_addr,
                (unsigned)&dma_hw->ch[VGA_DMA_PIO0].al3_transfer_count,
                dma_hw->ch[VGA_DMA_CB0].ctrl_trig);
            printf("PIO: fstat=%08x txlvl=%u sm0.addr=%02x\n",
                VGA_PIO->fstat,
                (unsigned)((VGA_PIO->flevel >> (VGA_SM0*8)) & 0x1f),
                VGA_PIO->sm[VGA_SM0].addr & 0x1f);

            next = make_timeout_time_ms(1000);
        }
        tight_loop_contents();
    }        
}
