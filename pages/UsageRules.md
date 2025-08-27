# Usage Rules {#usagerules}

Image generation on the Raspberry Pi Pico with PicoVGA is highly demanding on processor resources. The VGA signal must always be generated on time, which means other processor activities must be carefully designed around it. The following principles are critical for stable and reliable operation of the library:

## Core Utilization
- The PicoVGA library always runs on the **second core (core 1)**, while your application code runs on the **first core (core 0)**. This separation ensures that rendering does not interfere with your main program logic.
- Rendering can fully saturate core 1, making it unsuitable for other tasks in most cases. Your main program should interact with PicoVGA by writing to frame buffers on core 0, while core 1 continuously handles video output without synchronization overhead.
- In lightweight modes (e.g., 8-bit graphics rendered via DMA transfers), core 1 may have spare capacity. Code dispatched to core 1 through the library should not use interrupts, be careful with the interpolation unit (its state is not preserved by the renderer), and never disable interrupts.

## Memory Rules
- All data accessed by PicoVGA (images, fonts, tile patterns, etc.) must be stored in **RAM**, not flash. Flash memory is too slow and will cause video dropouts.
- If assets are stored in external flash, copy them into a RAM buffer before passing them to the rendering functions.

## Rendering Performance
- Some modes (e.g., 8-bit DMA transfers) render very quickly, while others (e.g., sprite rendering in slow mode) are CPU-intensive.
- Rendering is performed per line. If a mode is too demanding, individual scanlines may fail to render on time, breaking video synchronization.
- **If rendering is too slow:**
  - Switch to a faster video mode.  
  - Reduce the resolution or rendered area.  
  - Mix modes (e.g., add tile borders around the display area).  
  - Increase the CPU clock speed.  

A good stress test is to render many sprites side by side horizontally, which creates the most demanding case.

## DMA Considerations
- PicoVGA uses DMA to stream pixel data into the PIO. Even though the PIO has a TX **FIFO**, competing DMA traffic can delay the render DMA and cause **video dropouts**.
- **Conflicts to watch:**
  - Large, fast **RAM↔RAM** transfers on other DMA channels.  
  - **QSPI flash** reads (e.g., XIP or DMA from external flash). In these cases, the non-render DMA may stall waiting on flash, effectively **blocking** the render DMA channel.
- Minimize or schedule other DMA operations so they do not overlap with active rendering.

## CPU Clock Frequency
- Before initializing video output, PicoVGA calculates and sets the required system clock frequency to ensure precise timing.
- You should print the calculated frequency to the console at startup to verify configuration.
- You may restrict the library from changing the system clock or limit its range. However, this can make some video modes unavailable or unstable.

## Memory Alignment
- Image buffers must be aligned to **4 bytes** (32-bit words).
- Image **segments must be horizontally aligned to 4 pixels**. This applies to the segment’s **X position**, **width**, **wrapping** (**wrapx**), and **horizontal offset** (**offx**). Vertical alignment has no such restriction.
- Pixel data is transferred to the PIO using 32‑bit DMA words; each word packs **4× 8‑bit pixels**, so horizontal data must start on a 4‑pixel boundary.
- Horizontal scrolling is limited to **4‑pixel steps**. Exceptions:
  - **Slow sprites** – software-rendered per scanline; can scroll at **1‑pixel** precision.
  - **Framebuffer software rendering** – drawing directly into video memory allows **any pixel coordinate**.

## PIO Usage
- PicoVGA exclusively uses **PIO0** for video output.
- The second controller, **PIO1**, remains free and can be used for other purposes in your program.

## Summary
To use PicoVGA effectively:
1. Treat core 1 as dedicated to rendering.  
2. Keep all rendering assets in RAM.  
3. Match your rendering mode to the available performance.  
4. Avoid DMA conflicts and verify clock settings.  
5. Respect memory alignment rules (including **wrapx** and **offx**) for stable operation.  

Following these principles ensures smooth VGA output and stable integration of PicoVGA into your Raspberry Pi Pico projects.

