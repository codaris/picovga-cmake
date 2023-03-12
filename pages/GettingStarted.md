# Getting Started {#gettingstarted}

## Installing PicoVGA

1. Make sure you have the [Pico SDK](https://github.com/raspberrypi/pico-sdk) installed.

2. Clone the PicoVGA repository  
~~~
git clone https://github.com/codaris/picovga-cmake.git
~~~

3. Set `PICOVGA_PATH` to the PicoVGA directory in your environment, or pass it (`-DPICOVGA_PATH=`) to cmake later.

## Building the Examples

The PicoVGA project comes with a comprehensive set of example programs that demonstate many of the features of the library.  These examples are located in the [`examples`](https://github.com/codaris/picovga-cmake/tree/main/examples) folder of the PicoVGA project.

To create the makefiles, run this CMake command from the main PicoVGA folder:

~~~
cmake .
~~~

Then to build all the example projects at once, you run make (please note this might take a long time):

~~~
make
~~~

This will generate a `.uf2` file for every example program in the root folder of each example.  

If you want to build a single example program, you can run make for just that example:

~~~
cd examples/vga_hello
make
~~~

If you don't want to mix the build files with the rest of the code, you can specify a separate build folder when running CMake:

```
 cmake . -Bbuild
```

This will generate all the makefiles and build outputs into the `build` folder.

After you build one or more example files, the compiled output will be generated as `program_name.uf2` file where `program_name` is the name of the example.  They are compiled for a VGA monitor and USB serial keyboard input.  Load them into the Pico by copying the `uf2` on the Pico when it's in bootloader mode (hold the bootsel button when connecting to your computer).

Many of the examples use a USB serial connection for controls.

## Integrating PicoVGA into Your Project

The easiest way to incorporate the PicoVGA library into a project is to examine or copy the [sample project](https://github.com/codaris/picovga-helloworld).

To add PicoVGA to an existing project you must do the following:

1. Copy the `picovga_import.cmake` file from the PicoVGA library folder into the root of your project.

2. Copy the `vga_config.h` file from the the PicoVGA library folder into the source or include files folder in your project.

3. Include that file in your `CMakeLists.txt` file:  
~~~
include(picovga_import.cmake)  
~~~

4. For every target that uses PicoVGA, add PicoVGA to that target with the `add_picovga()` macro in the `CMakeLists.txt` file:  
~~~
# Add PicoVGA to the target (in this case "helloworld")
add_picovga(helloworld)
~~~

5. Ensure that the folder containing the `vga_config.h` is included in the target include directories in `CMakeLists.txt`:  
~~~
target_include_directories(helloworld PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)
~~~ 

Run the command `cmake .` to generate the makefiles for the project and `make` to build the project.

## Configuring PicoVGA

The `vga_config.h` contains the PicoVGA library settings, such as the size of the render buffers. You usually do not need to pay attention to this file. You usually only have to modify it in the following cases:

* When you use a display resolution greater than 640x480 pixels. Typically, the configuration file sets the maximum resolution to 640x480. This must be adjusted at higher resolutions to allow the library to reserve larger buffers for rendering functions.
* If there is not enough RAM. There is still some headroom where you can save some memory. First, you can reduce the MAXX, MAXY, and MAXLINE resolution settings down to a real values. Next, you can reduce the number of LAYERS down to the actual value used (in the range of 1 to 4). Finally, you can reduce the number of segments and stripes to the actual value SEGMAX and STRIPMAX (minimum is 1).
*  The third case is to use of a large number of display stripes and segments. Normally, the values here are set to 8 stripes (=horizontal strips) and 8 segments (=vertical division of each strip).

If you have an older monitor that requires VGA VSync, uncomment the line the `CMakeLists.txt` file that sets the vsync pin:

~~~
# If monitor requires vsync, set the vsync pin.
add_compile_definitions(VGA_GPIO_VSYNC=9)
~~~

Vsync can use any pin on the Pico (the default is 9)
