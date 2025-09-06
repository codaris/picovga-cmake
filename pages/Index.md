# Introduction {#mainpage}

## About this Fork

This is a fork of the original [PicoVGA project](https://github.com/Panda381/PicoVGA) by Miroslav Nemecek  (Panda38@seznam.cz).  

Changes in this fork:

* Uses the standard **Linux-based Raspberry Pi Pico SDK** toolchain (CMake).
* Header files are updated to **auto-generate documentation**.
* **Now supports both RP2040 and RP2350** devices with the same source tree.
* Tested with [Raspberry Pi Pico SDK 2.2.0](https://github.com/raspberrypi/pico-sdk).
* Full [Change Log](https://github.com/codaris/picovga-cmake/CHANGELOG.md)

## What is PicoVGA?

The PicoVGA library enables the Raspberry Pi Pico output to VGA or PAL/NTSC TVs.  It is great for retro-inspired computing projects like pixel-art games, emulators, and interfacing with homebrew computers.  The library provides one base layer plus three overlays with transparency and supports nearly 30 framebuffer formats that can be freely combined -- all while keeping RAM use low. 

On the RP2040 (264 KB RAM) and the RP2350 (520 KB RAM), limited RAM makes high-resolution framebuffers impractical. PicoVGA embraces those constraints by targeting 8-bit R3G3B2 color, tile/text formats, and layered sprites to deliver crisp, retro visuals with a small memory footprint and deterministic timing. 

## Features

* **Layers:** 1 base + 3 overlay layers with transparency (driven by PIO0).
* **Color:** 8-bit R3G3B2 output.
* **Outputs:**
  * VGA: from \~256×192 up to 1280×960 (mode-dependent).
  * TV: PAL/NTSC interlaced up to 1024×576 or 848×480.
* **Framebuffers:** \~30 formats (8/4/2/1-bit graphics, tiles, text, charts/special).
* **Palettes:** For text modes & limited-bit-depth graphics.
* **Composability:** Mix formats in strips or segments within a single frame.
* **Transparency** with selectable key color modes.
* **Sprites:** Hardware sprites in overlay layers.
* **Color Planes:** Layer output only to designated output pins.
* **RLE image compression** for drawings and static art.
* **Automatic configuration** of the video mode according to the specified resolution and timing
* **Automatic overclocking** according to the desired resolution
* **Uses only 2nd core.** The 1st core is reserved for the main program 
* **Audio:** Optional PWM audio.

## Supported MCUs & boards

* **RP2040** (e.g., Raspberry Pi Pico, Pico W, and compatible boards)
* **RP2350** (e.g., Raspberry Pi Pico 2, Pico 2 W, etc.)

The library auto-detects the MCU via the Pico SDK configuration. In CMake, set `PICO_BOARD` to your actual board (e.g., `pico`, `pico_w`, or an RP2350 board such as `pimoroni_pga2350`). No code changes required.

## Examples and Tutorials

To learn about installing and building the library and the examples, check out the *[Getting Started](@ref gettingstarted) section in this documentation.

The library includes a comprehensive set of examples that demonstrate many of the library features:

* [Example projects](https://github.com/codaris/picovga-cmake/tree/main/examples)

* [Hello World project](https://github.com/codaris/picovga-helloworld)

To try out the examples, take 8 resistors and connect them to outputs GP0 to GP7 and the RGB connector of a VGA or SCART TV. Then, connect HSync (CSync) to GP8, headphones to GP19, and load the demo program via USB. If keyboard control is needed, a serial terminal program can be used, but most programs work without a keyboard.

For more information on connecting the Pico to a VGA display, check out the [Connections](@ref connections) documentation section.

## Tools

The `tools` folder contains the support programs used to prepare images, palettes, and sounds for use with the **PicoVGA** library.

* [Tools and Palettes](@ref tools)

## License terms

The PicoVGA library source code and the PicoVGA library sample programs are freely available for further use and modifications. This does not apply to certain graphics and sounds (such as the sounds in Pac-Man) and scene definitions in Sokoban, as these are subject to third party copyrights and may be subject to different distribution terms.

## Getting Help

You can get help with this library using the [Issues tab](https://github.com/Panda381/PicoVGA/issues) in the [original PicoVGA project](https://github.com/Panda381/PicoVGA).  For issues related to this fork of the library, please use the [Issues tab](https://github.com/codaris/picovga-cmake/issues) for PicoVGA-cmake. 

How to inform about found defects:

* First of all, please check project issues on GitHub. The issue you found might be already recorded.
* Check that the issue is reproducible and describe it.
* Ideally, create a small test program that exposes the problem.

