# PicoVGA - VGA/TV display on Raspberry Pico

## About this Fork
This is a fork of the [PicoVGA project](https://github.com/Panda381/PicoVGA) created by Miroslav Nemecek (Panda38@seznam.cz).  It has been altered from the original to use the standard Linux-based Pico SDK.

This fork was created to support the Pico W hardware not supported by SDK included in the original PicoVGA project.   

## About PicoVGA

The PicoVGA library enables the Raspberry Pico to output to a VGA monitor or PAL/NTSC TV with ease, making it ideal for technical and gaming applications. It provides four graphic overlay layers with transparency and supports nearly 30 frame buffer formats that can be freely combined while using limited RAM memory. The output is limited to 8 bits, which helps to save on RAM.

The RP2040 processor has 264 KB of RAM, which is insufficient for higher resolution image output. Therefore, it's essential to use RAM sparingly. For technical practice and retro games (as the processor cannot handle more advanced games), 8-bit graphics output in R3G3B2 format (red 3 bits, green 3 bits, and blue 2 bits) is adequate. Outputting in 16 or 24 bits is not practical since the Raspberry Pico does not have enough memory or power to handle such large amounts of data, except for short demos. The dithering technique can be used to achieve interesting display results even with 8-bit output.

To try out the library, the simplest approach is to take 8 resistors and connect them to outputs GP0 to GP7 and the RGB connector of a VGA or SCART TV. Then, connect HSync (CSync) to GP8, headphones to GP19, and load the demo program via USB. The library package comes with pre-compiled programs. If keyboard control is needed, a console program such as begPutty can be used, but most programs work without a keyboard.

![](www/img/PicoVGA_diagram2.jpg)

*License terms*: The PicoVGA library source code and the PicoVGA library sample programs are freely available for further use and modifications. This does not apply to certain graphics and sounds (such as the sounds in Pac-Man) and scene definitions in Sokoban, as these are subject to third party copyrights and may be subject to different distribution terms.

## Features

* 1 base layer and 3 overlay layers with transparency, using the PIO0 module
* 8-bit output in R3G3B2 format
* VGA monitor output in 256x192 to 1280x960 resolution output to a TV in PAL or NTSC interlaced mode at resolutions up to 1024x576 or 848x480
* Nearly 30 frame buffer formats: 8/4/2/1 bit graphics, tiles, text, special formats (charts)
* Colour palettes for text modes and graphics formats with limited bit depth
* Frame buffers of different formats can be combined together in strips and segments in the image
* RLE image compression (suitable for drawings)
* Transparency modes with selectable key colour
* Hardware sprites in overlay layers
* Layer output only to designated output pins (color planes)
* Automatic configuration of the video mode according to the specified resolution and timing
* Automatic overclocking of the processor according to the desired resolution
* The library uses the 2nd core of the processor, the 1st core is reserved for the main program 
* Additional PWM audio output (not required)

## Documentation


## Usage rules

Generating images on the Raspberry Pico is limited by the processor's utilization, and other processor activities must be given lower priority. When using the PicoVGA library, there are several principles to keep in mind:

The library always runs on the second core of the processor while the program runs on the first core. Rendering the image can overload the CPU core and make it unusable for other purposes. However, separating core functions has the advantage of preventing mutual interference between cores, which eliminates the need for mutual locking. The first core simply writes to the frame buffers, while the second core displays the contents of the frame buffers without any communication between them. This makes the overall work easier and faster.

If the second core is not very busy (e.g. when displaying 8-bit graphics that are simply transferred using DMA transfer), it can also be used for the main program work. However, some limitations should be taken into account - the program in the second core should not use interrupts (it would interfere with the rendering function), the interpolation unit should be used with caution (the rendering function does not save its state) and it must not disable interrupts.

An important rule is that all data to be accessed by the PicoVGA library must be stored in RAM. External flash memory is slow and cannot be used for rendering functions. For example, if an image in the flash is to be displayed, it must first be copied to a buffer in RAM, and then a pointer to the RAM copy of the image should be passed to the rendering function. If a pointer to the image in flash were passed to it, slow access to flash would cause video dropouts. In addition to images, this also applies to fonts and tile patterns, for example.

The limited rendering speed must be taken into account when scheduling screen layout. Some modes render very fast (e.g. 8-bit graphics are just transferred from the frame buffer using DMA) and some modes are very rendering intensive - e.g. rendering sprites in slow mode. When using demanding rendering, some video lines may not render fast enough in the required time and the video image will break (drop out of sync). In such cases, it is necessary to use another mode, or to reduce the rendered area (add other modes, faster ones - e.g. add tile controls on the sides of the screen), reduce the screen resolution or increase the CPU clock speed. Video lines are rendered separately and therefore it is always just content on one video line about, video lines do not affect each other. For example, you can test the speed of sprite rendering by placing all the sprites horizontally next to each other (the most challenging case) and check if the video synchronization fails.

Care must also be taken when using DMA transfer. DMA is used to transfer data to the PIO. Although the transfer uses a FIFO cache, using a different DMA channel may cause the render DMA channel to be delayed and thus cause the video to drop out. A DMA overload can occur, for example, when a large block of data in RAM is transferred quickly. However, the biggest load is the DMA transfer of data from flash memory. In this case, the DMA channel waits for data to be read from flash via QSPI and thus blocks the DMA render channel.

The CPU clock frequency must also be subordinated to the image generator. Before initializing the video node, the library calculates the required system clock frequency so that the timing matches the requirements and the processor speed is sufficient for the required image resolution. It is a good idea to initially print out the calculated clock frequency for checking on the console. It is possible to prohibit the library from changing the system clock, or to prescribe only a certain range, in which case some modes may be unreachable (or the video image may break up).

Image buffers must be aligned to 4 bytes (32-bit CPU word) and image segments must be horizontally aligned to 4 pixels - this refers to the horizontal position of the segment, its width, alignment (wrapx) and offset (offx). Alignment does not apply to the vertical direction. This restriction is necessary because the image information is transferred to the PIO controller using a 32-bit DMA transfer, and this must be aligned to a 32-bit word. One 32-bit word contains 4 pixels (1 pixel has 8 bits), so the horizontal data in the image must also be aligned to 4 pixels. So you cannot do fine horizontal scrolling of the image in 1 pixel increments (the restriction does not apply to vertical scrolling), but only in 4 pixel increments. The exception to this is slow sprites, which are software rendered to the video line and can therefore be scrolled in 1 pixel increments. Similarly, the restriction does not apply to software rendering to framebuffer (e.g. rendering an image to video memory can be done to any coordinate).

 cmake . -Bbuild -DCMAKE_BUILD_TYPE=Debug