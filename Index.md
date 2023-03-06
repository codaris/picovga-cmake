# Introduction {#mainpage}

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

test link LayerSpriteSetup()
