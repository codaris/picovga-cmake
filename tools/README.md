# PicoVGA Tools

The `tools` folder contains the support programs used to prepare images, palettes, and sounds for use with the **PicoVGA** library. These tools convert standard file formats (BMP, WAV, ACT) into optimized C arrays that can be compiled directly into PicoVGA projects.  

The generated arrays provide graphics and audio data in formats tailored for the Raspberry Pi Pico’s hardware and the PicoVGA rendering pipeline. By using these utilities, you can ensure that assets created in common editors (e.g., Photoshop, GIMP, Audacity) are correctly formatted and ready to use without additional runtime conversion.

All tools are lightweight console applications that should compile for all platforms.  Building the library will build these applications into the `tools` folder.


* [picovga_img](#picovga_img--image-conversion-tool) – Image Conversion Tool
* [picovga_rle](#picovga_rle--rle-compression-tool) – RLE Compression Tool
* [picovga_snd](#picovga_snd--sound-import-tool) – Sound Import Tool
* [picvovga_pal332](#picvovga_pal332--picovga-8-bit-palette-generator) – PicoVGA 8-bit Palette Generator
* [palettes](#palettes-1) - A collection of `.act` palette files  for use in image editors.  

## picovga_img – Image Conversion Tool

**picovga_img** is a command-line utility that converts Windows BMP images into C array data for use with the PicoVGA library on the Raspberry Pi Pico. It ensures that images are properly formatted and optimized for 8-bit, 4-bit, 2-bit, or 1-bit palette graphics.

### Usage
```bash
picovga_img input.bmp output.cpp arrayname
```

- **input.bmp** – Source image file (must be a Windows BMP format).  
- **output.cpp** – Destination C++ file containing the image data.  
- **arrayname** – Name of the C++ array that will hold the image data.  

The tool reads the BMP image, validates its format, and writes the pixel data into a `const u8[]` array that can be directly included in PicoVGA projects.


### Supported Image Formats
- **8-bit palette BMP** – Uses a 256-color palette.  
- **4-bit palette BMP** – Supports 16-color palettes (e.g., CGA or ZX Spectrum).  
- **2-bit palette BMP** – Saved as a 4-bit BMP but recognized by picovga_img if the palette only contains 4 colors (CGA modes).  
- **1-bit palette BMP** – Monochrome images with 2 colors.  

All input images must be:
- **Windows BMP format**  
- **Uncompressed (BI_RGB)**  
- **Saved with flipped row order** (so that PicoVGA interprets the image correctly)  

### Palettes
When exporting from your image editor, always apply the correct palette (`.act` files) before saving:  

- **8-bit graphics** → `pal332.act` (332 RGB palette).  
- **4-bit graphics** → `pal4_PC.act` (CGA palettes) or `pal4_ZX.act` (ZX Spectrum).  
- **2-bit graphics** → `palcga*.act` (CGA palettes, modes 1–6).  
- **1-bit graphics** → `pal1.act` (black & white).  

⚠️ **Note:** BMP does not natively support 2-bit images. Save as a 4-bit BMP with a 4-color palette, and RaspPicoImg will automatically detect and convert it to 2-bit format.

### Output
The generated `.c` file contains:
- Image metadata (bit depth, width, height, pitch).  
- A `const u8[]` array with pixel data aligned to 4 bytes.  

Example excerpt:
```c
// format: 4-bit pixel graphics
// image width: 128 pixels
// image height: 64 lines
// image pitch: 64 bytes
const u8 myimage[8192] __attribute__ ((aligned(4))) = {
    0x12, 0x34, 0x56, 0x78, ...
};
```

This array can be included in your PicoVGA project and drawn directly to the screen.

## picovga_rle – RLE Compression Tool

**picovga_rle** is a command-line utility that compresses 8-bit PicoVGA images into a run-length encoded (RLE) format suitable for use with the PicoVGA library on the Raspberry Pi Pico. The compression significantly reduces image size while maintaining compatibility with the RLE PIO routines in PicoVGA.

### Usage
```bash
picovga_rle input.bmp output.c arrayname transparent_color
```

- **input.bmp** – Source image file (must be an 8-bit BMP using the PicoVGA palette `pal332.act`).  
- **output.cpp** – Destination C++ file containing the compressed image data.  
- **arrayname** – Name of the generated C array.  
- **transparent_color** – Index of the color to be used as transparency (0–255). Use `-1` for no transparency.  

The tool reads the BMP image, compresses it using RLE, and outputs a set of C arrays containing both pixel data and row offsets.

### Input Requirements
- **Format:** Windows BMP.  
- **Bit Depth:** 8-bit palettized (must use PicoVGA's `pal332.act`).  
- **Compression:** None (must be saved uncompressed).  
- **Row Order:** Reverse line order enabled.  

⚠️ If the input image does not meet these conditions, the tool will reject it.

### Transparency
The fourth parameter specifies which color index should be treated as transparent.  

- To enable transparency: supply the **palette index** of the color. For example, if a pixel color in Photoshop is `#8080FF`, locate it in `pal332.csv` to find the matching PicoVGA index.  
- To disable transparency: set the parameter to `-1`.  

Example:
```bash
picovga_rle sprite.bmp sprite.c mysprite 120
```
This command compresses `sprite.bmp`, outputs to `sprite.c`, creates an array named `mysprite`, and treats color index 120 as transparent.

### Output
The generated `.cpp` file contains:
- **Image metadata** – format, transparency, width, height, size, and compression ratio.  
- **Row offset table** – an array of `u16` values marking where each scanline begins in the compressed data.  
- **RLE data array** – compressed image data aligned to 4 bytes.  

Example excerpt:
```c
// format: RLE compression
// transparent color: 120
// image width: 64 pixels
// image height: 64 lines
// uncompressed size: 4096 bytes
// compressed size: 1536 bytes
// compression ratio: 37.5%

const u16 mysprite_rows[65] = {
    0x0000, 0x0012, 0x0028, ...
};

const u8 mysprite[1536] __attribute__ ((aligned(4))) = {
    0x34, 0x07, 0x12, 0x56, ...
};
```

### Internal Encoding
The RLE compression encodes pixel sequences into tokens:
- **skip** – Transparent runs of 2–257 pixels.  
- **skip1** – Single transparent pixel.  
- **run** – Repeated color runs of 3–258 pixels.  
- **raw / raw1** – Direct copies of pixel values (used when sequences are too short for run-length encoding).  

Each scanline is terminated with an `idle` command and aligned to 32-bit boundaries for efficient processing on the Pico.

### Compatibility Warning
The compressed output is tightly coupled with the **RLE PIO program** in PicoVGA. Since the instruction format may change between library versions, **always use picovga_rle from the same release as your PicoVGA library** to avoid incompatibility issues.

## picovga_snd – Sound Import Tool

**picovga_snd** is a command-line utility that converts WAV audio files into C array data for playback with the PicoVGA library on the Raspberry Pi Pico. It ensures that sound effects or music are properly formatted for the Pico’s audio playback routines.

### Usage
```bash
picovga_snd input.wav output.cpp arrayname
```

- **input.wav** – Source WAV file.  
- **output.cpp** – Destination C++ file containing the audio data array.  
- **arrayname** – Name of the generated C array.  

The tool validates the WAV file format and writes its sample data into a `const u8[]` array that can be directly included in PicoVGA projects.

### Input Requirements
The input WAV file must meet **strict format requirements**:
- **Format:** PCM (uncompressed).  
- **Channels:** Mono (1 channel).  
- **Bit depth:** 8-bit unsigned (values 0–255, centered at 128).  
- **Sample rate:** 22050 Hz.  

⚠️ If the file does not meet these conditions, the tool will reject it.

#### Recommended Editors
- **Audacity** (free) – provides full editing and sound effects, and supports exporting WAV in the correct format.  
- **Cool Edit** – a commercial editor that can also produce compatible WAV files.  

These tools allow trimming, resampling, and converting audio to the exact format needed for PicoVGA.

### Output
The generated `.cpp` file contains:
- A header comment describing the sound format.  
- A `const u8[]` array aligned to 4 bytes, containing all audio samples.  

Example excerpt:
```c
// sound format: PCM mono 8-bit 22050Hz
const u8 mysound[1024] __attribute__ ((aligned(4))) = {
    0x80, 0x82, 0x7E, 0x7C, ...
};
```

This array can be compiled into your PicoVGA program and played back using the sound routines in the library.

## picvovga_pal332 – PicoVGA 8-bit Palette Generator

**picvovga_pal332** is a utility program used to generate the standard 8-bit PicoVGA palette. This palette is the foundation for all 8-bit graphics in PicoVGA and defines a total of 256 colors based on a **3-3-2 bit RGB model**:
- **3 bits red (0–7 levels)**
- **3 bits green (0–7 levels)**
- **2 bits blue (0–3 levels)**

This RGB332 format allows compact color representation while providing a broad enough spectrum for retro-style graphics.

### Output Files
When you run **picvovga_pal332**, it generates two important files:

- **pal332.act** – Adobe Color Table file containing the 256-color PicoVGA palette. This file can be imported into image editors such as Photoshop or GIMP to ensure images are created using PicoVGA’s 8-bit colors.
- **pal332.csv** – A CSV table with detailed color information. Each row includes:
  - **Palette index (0–255)**
  - **RGB hex value**
  - **Individual red, green, and blue component values**

Example (excerpt from `pal332.csv`):
```csv
Index, HEX, R, G, B
0, #000000, 0, 0, 0
1, #000055, 0, 0, 85
2, #0000AA, 0, 0, 170
...
```

### Usage in Image Editors
- In **Photoshop** or **GIMP**, load `pal332.act` as the palette before saving your image as an 8-bit BMP. This ensures the image uses the exact PicoVGA colors.
- If you identify a color in an image by its **HEX code** (e.g., `#8080FF`), you can use `pal332.csv` to look up which PicoVGA color index corresponds to that HEX value.

This is especially useful when working with transparency or when preparing assets for use with other PicoVGA tools such as [picovga_img](#picovga_img--image-conversion-tool) or [picovga_rle](#picovga_rle--rle-compression-tool).

## Palettes
The PicoVGA project includes a set of predefined palettes located in the `tools\palettes` folder. These palettes (`*.act` files) can be used in Photoshop, GIMP, or other graphics editors to ensure images match PicoVGA’s supported color sets.

### Available Palettes
- **pal332.act** – The primary 8-bit PicoVGA palette. This file defines the 256 standard colors used by PicoVGA.  
- **pal4_PC.act** – Standard CGA 16-color palette.  
- **pal4_ZX.act** – ZX Spectrum–style 16-color palette.  
- **palcga\*.act** – Variants of CGA palettes for different modes (used for 2-bit conversions).  
- **pal1.act** – Black & white palette for 1-bit images.  

### Palette Details
The most important palette is **pal332.act**, which represents the 3-3-2 bit RGB layout (3 bits red, 3 bits green, 2 bits blue). It is generated by the `pal332.exe` tool and comes with an additional CSV file:

- **pal332.csv** – Contains detailed information about each color entry:
  - Color index (palette order number).  
  - RGB value of the color.  
  - Separate red, green, and blue component values.  

This CSV file can be opened in Excel, LibreOffice, or any text editor. It is especially useful if you want to map a color you’ve selected in Photoshop (by HEX code) to its exact PicoVGA color index. Simply search for the HEX value in `pal332.csv` and read the index number at the beginning of the corresponding line.

⚠️ **Tip:** Always apply the correct `.act` palette before saving your BMP images for conversion with `picovga_img`. This ensures the tool interprets the colors correctly.