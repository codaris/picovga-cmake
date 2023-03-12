# PicoVGA - VGA/TV display on Raspberry Pico

## About this Fork
This is a fork of the [PicoVGA project](https://github.com/Panda381/PicoVGA) created by Miroslav Nemecek (Panda38@seznam.cz).  It has been altered from the original to use the standard Linux-based  Raspberry Pi Pico SDK.  The header files have also been altered to support automatically generating this documentation.

## About PicoVGA

The PicoVGA library enables the Raspberry Pico to output to a VGA monitor or PAL/NTSC TV with ease, making it ideal for technical and gaming applications. It provides four graphic overlay layers with transparency and supports nearly 30 frame buffer formats that can be freely combined while using limited RAM memory. The output is limited to 8 bits, which helps to save on RAM.

The RP2040 processor has 264 KB of RAM, which is insufficient for higher resolution image output. Therefore, it's essential to use RAM sparingly. For technical practice and retro games (the processor cannot handle more advanced games), 8-bit graphics output in R3G3B2 format (red 3 bits, green 3 bits, and blue 2 bits) is adequate. Outputting in 16 or 24 bits is not practical since the Raspberry Pico does not have enough memory or power to handle such large amounts of data, except for short demos. The dithering technique can be used to achieve interesting display results even with 8-bit output.

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

## Documentaton

View the complete PicoVGA documentation by clicking the link below:

* [PicoVGA CMake Documentation](https://codaris.github.io/picovga-cmake/)

## Examples and Tutorials

To learn about installing and building the library and the examples, check out the **Getting Started** section in the documentation:

* [Getting Started](https://codaris.github.io/picovga-cmake/gettingstarted.html)

The library includes a comprehensive set of examples that demonstrate many of the library features:

* [Example projects](https://github.com/codaris/picovga-cmake/tree/main/examples)

* [Hello World project](https://github.com/codaris/picovga-helloworld)

To try out the examples, take 8 resistors and connect them to outputs GP0 to GP7 and the RGB connector of a VGA or SCART TV. Then, connect HSync (CSync) to GP8, headphones to GP19, and load the demo program via USB. If keyboard control is needed, a serial terminal program can be used, but most programs work without a keyboard.

For more information on connecting the Pico to a VGA display, check out the **Connections** documentation section:

* [Connections](https://codaris.github.io/picovga-cmake/connections)

## License terms

The PicoVGA library source code and the PicoVGA library sample programs are freely available for further use and modifications. This does not apply to certain graphics and sounds (such as the sounds in Pac-Man) and scene definitions in Sokoban, as these are subject to third party copyrights and may be subject to different distribution terms.

## Getting Help

You can get help with this library using the [Issues tab](https://github.com/Panda381/PicoVGA/issues) in the [original PicoVGA project](https://github.com/Panda381/PicoVGA).  For issues related to this fork of the library, please use the [Issues tab](https://github.com/codaris/picovga-cmake/issues) for PicoVGA-cmake. 

How to inform about found defects:

* First of all, please check project issues on GitHub. The issue you found might be already recorded.
* Check that the issue is reproducible and describe it.
* Ideally, create a small test program that exposes the problem.
