
// ****************************************************************************
//
//                               VGA screen layout
//
// ****************************************************************************

#ifndef _VGA_SCREEN_H
#define _VGA_SCREEN_H

//!@addtogroup Screen Screen layout
//!@brief Defining the layout of the display
//!@details When displaying screen image, the default pointer is pScreen for the library. It points to the sScreen structure that 
//!describes the contents of the display. The Raspberry Pico has a limited RAM size and cannot accommodate a high resolution image. Therefore, the image must be composed of smaller segments to minimize the memory-intensive parts.
//!@note The following descriptions of the image format only apply to the base image layer 0. It is the only one that can contain 
//!segments in different formats. Overlay layers 1 through 3 are independent of the base layer format, sharing only the total 
//!screen area with the base layer but using their own image format.
//!@{

//! Video segment (on change update SSEGM_* in define.h)
typedef struct {
	u16	width;	//!< SSEGM_WIDTH width of this video segment in pixels (must be multiple of 4, 0=inactive segment)
	u16	wb;		//!< SSEGM_WB pitch - number of bytes between lines
	s16	offx;	//!< SSEGM_OFFX display offset at X direction (must be multiple of 4)
	s16	offy;	//!< SSEGM_OFFY display offset at Y direction
	u16	wrapx;	//!< SSEGM_WRAPX wrap width in X direction (number of pixels, must be multiply of 4 and > 0)
				//!<	text modes: wrapx must be multiply of 8
	u16	wrapy;	//!< SSEGM_WRAPY wrap width in Y direction (number of lines, cannot be 0)
	const void* data; //!< SSEGM_DATA pointer to video buffer with image data
	u8	form;	//!< SSEGM_FORM graphics format GF_*
	bool	dbly;	//!< SSEGM_DBLY double Y (2 scanlines per 1 image line)
	u16	par3;	//!< SSEGM_PAR3 parameter 3
	u32	par;	//!< SSEGM_PAR parameter 1
	u32	par2;	//!< SSEGM_PAR2 parameter 2
} sSegm;

//! Video strip (on change update SSTRIP_* in define.h)
typedef struct {
	u16	height;				//!< SSTRIP_HEIGHT height of this strip in number of scanlines
	u16	num;				//!< SSTRIP_NUM number of video segments
	sSegm	seg[SEGMAX];	//!< SSTRIP_SEG list of video segments
} sStrip;

//! Video screen (on change update SSCREEN_* in define.h)
typedef struct {
	u16	num;				//!< SSCREEN_NUM number of video strips
	u16	backup;				//!< SSCREEN_BACKUP backup number of video strips during display OFF
	sStrip	strip[STRIPMAX]; //!< SSCREEN_STRIP list of video strips
} sScreen;

extern sScreen Screen;		//!< Default video screen
extern sScreen* pScreen;	//!< Pointer to current video screen

/**
 * @brief Clear screen (set 0 strips, does not modify sprites)
 * @details Resets the display handler structures, clearing the display. At a minimum, this function should be called 
 * before initializing the videmode. It initializes the display content descriptor structure pointed to by pScreen 
 * (usually the default structure Screen of the library) by setting the number of segments to 0. The screen will be black 
 * until we fill it with content descriptors
 * @param s Pointer to screen to clear 
*/
void ScreenClear(sScreen* s);

/**
 * @brief Add empty strip to the screen 
 * @details This function adds a new horizontal bar of the specified number of video lines to the end of the screen definition. 
 * The maximum number of stripes is specified by the STRIPMAX constant (8 by default) in the vga_config.h file. Without added 
 * segments, the bar is empty (black).
 * @param s The screen to add strip
 * @param height The number of video lines in the strip
 * @returns Pointer to the new strip
*/
sStrip* ScreenAddStrip(sScreen* s, int height);

/**
 * @brief Add empty segment to video strip; returns pointer to the segment and initialises it to defaults
 * @details This function adds a new image segment of the specified width to the end of the strip. The segment will contain 
 * one image format. For the vast majority of formats, the width must be a multiple of 4 (a multiple of 4 pixels).
 * @param strip The strip to add the segment to
 * @param width The width of the segment in pixels (for many formats must be a multiple of 4)
 * @returns Pointer to new segment initialized to defaults
 */ 
sSegm* ScreenAddSegm(sStrip* strip, int width);

/**
 * @brief Set video segment to simple color format GF_COLOR
 * @param segm Segment to configure 
 * @param col1 Color pattern 4-pixels even line (use macro MULTICOL)
 * @param col2 Color pattern 4-pixels odd line (use macro MULTICOL)
*/
void ScreenSegmColor(sSegm* segm, u32 col1, u32 col2);

/**
 * @brief Set video segment to gradient with 1 line
 * @details The segment will be filled with a color gradient (GF_GRAD1). The gradient is 1 line of 8-bit pixels. 
 * @note The gradient can be scrolled horizontally with the offx parameter.
 * @param segm Segment to configure 
 * @param data Pointer to data buffer with gradient
 * @param wb Length of buffer
*/
void ScreenSegmGrad1(sSegm* segm, const void* data, int wb);

/**
 * @brief Set video segment to gradient with 2 lines
 * @details  Gradient with 2 lines, even and odd (GF_GRAD2).
 * @note  To scroll gradient, set virtual dimension wrapx, then shift offx
 * @param segm Segment to configure 
 * @param data Pointer to data buffer with gradient
 * @param wb Length of buffer
*/
void ScreenSegmGrad2(sSegm* segm, const void* data, int wb);

/**
 * @brief Set video segment to native 8-bit graphics (R3G3B2)
 * @details 8-bit graphics 256 colors (GF_GRAPH8). Each pixel is 1 byte. This mode is one of the fastest, the data is simply sent 
 * from the frame buffer to the PIO controller using a DMA transfer. However, it is also one of the most memory intensive. 
 * Really, the memory can hold a maximum image resolution of 512x400 pixels (EGA video mode).
 * @note To scroll image, set virtual dimension wrapx and wrapy, then shift offx and offy.
 * @param segm Segment to configure 
 * @param data Pointer to data buffer
 * @param wb Line length in bytes
*/
void ScreenSegmGraph8(sSegm* segm, const void* data, int wb);

/**
 * @brief Generate 16-color palette translation table
 * @details Generates a palette translation table for the @link ScreenSegmGraph4() function. The translation table is 256 entries of 
 * 16 bits, so it takes 512 bytes in memory. The table is used during display for internal purposes, must be aligned to 4 bytes, 
 * and must be available for the entire time the segment is displayed. The input to the function is the palette table, which is 
 * 16 color entries of 1 byte.
 * @param trans Pointer to destination palette translation table (u16 trans[256])
 * @param pal Pointer to source palette of 16 colors (u8 pal[16])
*/
void GenPal16Trans(u16* trans, const u8* pal);

/**
 * @brief Set video segment to 4-bit palette graphics
 * @details 4-bit palette graphics 16 colors (GF_GRAPH4). There are 2 pixels in 1 byte (the first pixel is in the higher 4 bits 
 * of the byte). The function requires a palette translation table.
 * @note To scroll image, set virtual dimension wrapx and wrapy, then shift offx and offy.
 * @param segm Segment to configure 
 * @param data Pointer to data buffer
 * @param trans Pointer to 16-color palette translation table (generated with GenPal16Trans function)
 * @param wb The line length in bytes
*/
void ScreenSegmGraph4(sSegm* segm, const void* data, const void* trans, int wb);

/**
 * @brief Generate palette 4 translation table for function
 * @details  Generate a palette translation table for the @link ScreenSegmGraph2() function. The translation table is 256 entries with 
 * a size of 32 bits, so it takes 1024 bytes in memory. The table is used during display for internal purposes, must be aligned 
 * to 4 bytes, and must be available for the entire time the segment is displayed. The input to the function is the palette table,
 * which is 4 color entries of 1 byte.
 * @param trans Pointer to destination palette translation table (u32 trans[256])
 * @param pal Pointer to source palette of 4 colors (u8 pal[4]) 
*/
void GenPal4Trans(u32* trans, const u8* pal);

/**
 * @brief Set video segment to 2-bit palette graphics
 * @details 
 * @note To scroll image, set virtual dimension wrapx and wrapy, then shift offx and offy. 
 * @param segm Segment to configure
 * @param data Pointer to data buffer
 * @param trans Pointer to 4-color palette translation table (generated with GenPal4Trans function)
 * @param wb The line length in bytes
*/
void ScreenSegmGraph2(sSegm* segm, const void* data, const void* trans, int wb);

/**
 * @brief Set video segment to 1-bit palette graphics
 * @details 1-bit mono graphics 2 colors (GF_GRAPH1). There are 8 pixels in 1 byte (first pixel in the highest bit). The function requires background color 
 * and foreground color.
 * @note To scroll image, set virtual dimension wrapx and wrapy, then shift offx and offy.
 * @param segm Segment to configure
 * @param data Pointer to data buffer
 * @param bg Background color
 * @param fg Foreground color 
 * @param wb The line length in bytes
*/
void ScreenSegmGraph1(sSegm* segm, const void* data, u8 bg, u8 fg, int wb);

/**
 * @brief Set video segment to 8-pixel mono text
 * @details Mono text (GF_MTEXT). For mono text, the foreground and background color is valid for the entire segment. 
 * In the display memory there are single characters, 1 byte is one character.
 * @param segm Segment to configure
 * @param data Pointer to text buffer
 * @param font Pointer to 1-bit font of 256 characters of width 8 (total width of image 2048 pixels)
 * @param fontheight Font height
 * @param bg Background color
 * @param fg Foregound color
 * @param wb The line length in bytes
*/
void ScreenSegmMText(sSegm* segm, const void* data, const void* font, u16 fontheight, u8 bg, u8 fg, int wb);

/**
 * @brief Set video segment to 8-pixel attribute text
 * @details Attribute text (GF_ATEXT). In attribute text, each character is a pair of bytes. The first byte is the ASCII 
 * value of the character, the second byte is the color attribute. The higher 4 bits of the attribute represent the background 
 * color, the lower 4 bits of the attribute represent the foreground color. The colors are translated from a palette table of 
 * 16 colors.
 * @param segm Segment to configure
 * @param data Pointer to text buffer (character + 2x4 bit attributes)
 * @param font Pointer to 1-bit font of 256 characters of width 8 (total width of image 2048 pixels)
 * @param fontheight Font height
 * @param pal Pointer to palette of 16 colors
 * @param wb The line length in bytes
*/
void ScreenSegmAText(sSegm* segm, const void* data, const void* font, u16 fontheight, const void* pal, int wb);

/**
 * @brief Set video segment to 8-pixel foreground color text
 * @details Text with foreground color (GF_FTEXT). In text with foreground, each character is represented by a pair of bytes. 
 * The first byte is ASCII value of the character, the second byte is foreground color. The background color is common, specified 
 * by the 'bg' parameter. 
 * @note Library's default fonts include an inverted lower half of the font in the upper half (bit 7 set) - this can provide a 
 * character with an optional background color.
 * @param segm Segment to configure
 * @param data Pointer to text buffer (character + foreground color)
 * @param font Pointer to 1-bit font of 256 characters of width 8 (total width of image 2048 pixels)
 * @param fontheight Font height
 * @param bg Background color
 * @param wb The line length in bytes
*/
void ScreenSegmFText(sSegm* segm, const void* data, const void* font, u16 fontheight, u8 bg, int wb);

/**
 * @brief Set video segment to 8-pixel color text
 * @details Text with color (GF_CTEXT). For text with color, each character occupies 3 bytes. The first byte is the ASCII value 
 * of the character, the second byte is the background color, and the third byte is the foreground color.
 * @param segm Segment to configure
 * @param data Pointer to text buffer (character + background color + foreground color)
 * @param font Pointer to 1-bit font of 256 characters of width 8 (total width of image 2048 pixels)
 * @param fontheight Font height
 * @param wb The line length in bytes
*/
void ScreenSegmCText(sSegm* segm, const void* data, const void* font, u16 fontheight, int wb);

/**
 * @brief Set video segment to 8-pixel gradient color text
 * @details Text with gradient (GF_GTEXT). In this mode, each character is represented by 1 byte in memory and the background 
 * color is specified by the 'bg' parameter, similar to the mono text. Instead of the foreground color, there is a parameter 
 * 'grad', which is a pointer to a color gradient of length equal to the graphic length of the line of text (e.g. for 40 
 * characters, the gradient is 320 bytes). The foreground color for each pixel of the character is taken from the gradient table.
 * @param segm Segment to configure
 * @param data Pointer to text buffer (character + foreground color)
 * @param font Pointer to 1-bit font of 256 characters of width 8 (total width of image 2048 pixels)
 * @param fontheight Font height
 * @param bg Background color
 * @param grad Pointer to array of gradient colors
 * @param wb The line length in bytes
*/
void ScreenSegmGText(sSegm* segm, const void* data, const void* font, u8 fontheight, u8 bg, const void* grad, int wb);

/**
 * @brief Set video segment to 8-pixel double gradient color text
 * @details Double gradient text (GF_DTEXT). The function is identical to the previous function, except that each character pixel 
 * is generated as 2 image pixels. Thus, the character has twice the width. It is the only text mode that allows displaying 
 * characters with double width. The color gradient works similarly here, but 1 byte of the gradient represents 1 pixel of the 
 * character (as in the previous function), not 1 pixel displayed. Thus a line of 40 characters again requires a gradient of 
 * 320 bytes.
 * @param segm Segment to configure
 * @param data Pointer to text buffer (character + foreground color)
 * @param font Pointer to 1-bit font of 256 characters of width 8 (total width of image 2048 pixels)
 * @param fontheight Font height
 * @param bg Background color
 * @param grad Pointer to array of gradient colors
 * @param wb The line length in bytes
*/
void ScreenSegmDText(sSegm* segm, const void* data, const void* font, u8 fontheight, u8 bg, const void* grad, int wb);

/**
 * @brief Set video segment to tiles
 * @details Tiles in column (GF_TILE). Tiles are image segments of the specified size (tile width and height are 'w' and 'h'). 
 * The tile patterns are arranged in a single image. In this case, into a column of width 1 tile. The 'tiles' parameter is a 
 * pointer to the image of the tile column. The 'data' parameter is a pointer to an array of bytes, where each byte represents 
 * number of displayed tile. Thus, there can be a maximum of 256 tiles. The 'wb' parameter refers to the length of the row of 
 * the index array (not the length of the tile image). The width of a tile must be a multiple of 4, at least 8. Tiles allow 
 * efficient display of image information by allowing the image to repeat. Thus, high image resolution can be achieved with 
 * low memory requirements. 
 * @param segm Segment to configure
 * @param data Pointer to tile map buffer (with tile indices)
 * @param tiles Pointer to 1 column of tiles, 1 pixel = 8 bits
 * @param w tile width (must be multiple of 4)
 * @param h tile height
 * @param wb Number of bytes between tile map rows
*/
void ScreenSegmTile(sSegm* segm, const void* data, const void* tiles, int w, int h, int wb);

/**
 * @brief Set video segment to alternate tiles
 * @details Tiles in a row (GF_TILE2). This function is an alternative to @link ScreenSegmTile(), except that the tile patterns 
 * are arranged in a single row in the image. This may be more convenient when creating a tile image, however, you must 
 * additionally specify the parameter 'tilewb' representing the line length of the tile image. 
 * Usually tilewb = number of tiles * tile width.
 * @param segm Segment to configure
 * @param data Pointer to tile map buffer (with tile indices)
 * @param tiles Pointer to 1 row of tiles, 1 pixel = 8 bits
 * @param w tile width (must be multiple of 4)
 * @param h tile height
 * @param tilewb Tile width bytes (usually tile width * number of tiles)
 * @param wb Number of bytes between tile map rows
*/
void ScreenSegmTile2(sSegm* segm, const void* data, const void* tiles, int w, int h, int tilewb, int wb);

/**
 * @brief Set video segment to level graph GF_LEVEL
 * @details  Level display segment (GF_LEVEL). This segment is used to display graphs. The input is an array of 'data' bytes of 
 * length corresponding to the width of the array in pixels. The byte value represents the height of the graph at the given X 
 * coordinate. The display will show a foreground or background color depending on whether the displayed pixel lies above or 
 * below the value from the data array. The 'zero' parameter specifies the height of the reference zero. Zero does not imply 
 * negative numbers in the data, the numbers are still given as unsigned (with zero at the bottom). Starting from reference zero, 
 * the background and foreground colour is swapped. This results in the graph looking visually symmetrical around the reference 
 * zero. You can see the appearance of the segment in the Oscilloscope sample program (lower curve).
 * @param segm Segment to configure
 * @param data Pointer to buffer with line samples 0..255
 * @param zero Y zero level
 * @param bg Background color
 * @param fg Foregound color
*/
void ScreenSegmLevel(sSegm* segm, const void* data, u8 zero, u8 bg, u8 fg);

/**
 * @brief Set video segment to leve gradient graph GF_LEVELGRAD
 * @details Level display segment with gradient (GF_LEVELGRAD). This segment is used to display graphs, similar to the previous 
 * function. It differs in that the color is given as a vertical gradient with a height corresponding to the height of the segment. 
 * If a pixel lies below the data value, the color from the first gradient is used. Otherwise, the second gradient is used. 
 * An example use case can be seen in the Level Meter sample program, to display the spectrum.
 * @param segm Segment to configure
 * @param data Pointer to buffer with values 0..255 of 4-pixels in rows
 * @param sample1 Scanline sample < data
 * @param sample2 Scanline sample >= data
*/
void ScreenSegmLevelGrad(sSegm* segm, const void* data, const void* sample1, const void* sample2);

/**
 * @brief Set video segment to oscilloscope 1-pixel graph GF_OSCIL
 * @details Oscilloscope waveform display segment (GF_OSCIL). The segment is similar in function to the level display segment. 
 * It differs in that the curve is displayed as a line of 'pixh' pixel thickness. This function is already more demanding and 
 * may not be able to service the full width of the image.
 * @param segm Segment to configure
 * @param data Pointer to buffer with line samples 0..255
 * @param bg Background color
 * @param fg Foregound color
 * @param pixh Height of pixels - 1
*/
void ScreenSegmOscil(sSegm* segm, const void* data, u8 bg, u8 fg, int pixh);

/** 
 * @brief Set video segment to oscilloscope line graph GF_OSCLIN
 * @details Oscilloscope continuous waveform segment (GF_OSCLINE). The curve is displayed as a continuous line with a thickness 
 * of 1 pixel. This mode is already very demanding to render and is therefore accelerated by halving the horizontal resolution 
 * (renders points 2 pixels wide).
 * @param segm Segment to configure
 * @param data Pointer to buffer with line samples 0..255
 * @param bg Background color
 * @param fg Foregound color
*/
void ScreenSegmOscLine(sSegm* segm, const void* data, u8 bg, u8 fg);

/**
 * @brief Generate palette 4-color translation table for function @link ScreenSegmPlane2()
 * @details Generate a palette translation table for the @link ScreenSegmPlane2() function. The translation table is 256 entries of 
 * 32 bits, so it takes 1024 bytes in memory. The table is used during display for internal purposes, must be aligned to 4 bytes, 
 * and must be available for the entire time the segment is displayed. The input to the function is the palette table, which is 
 * 4 color entries of 1 byte.  Although there is no program in the PicoVGA library utilities that prepares an image in 2-plane 
 * mode, there is an internal function Plane2Conv that converts a 4-color image to 2-plane mode. Thus, the image is attached to 
 * the program as a 4-color image, and the conversion function is used to prepare a copy in RAM.
 * @param trans Pointer to destination palette translation table (u32 trans[256])
 * @param pal Pointer to source palette of 4 colors (u8 pal[4])
*/
void GenPal4Plane(u32* trans, const u8* pal);

// set video segment to 4-color on 2-planes graphics
//   data = pointer to data buffer
//   plane = offset of 2nd graphics plane (in bytes), size of one graphics plane
//   trans = pointer to 4-color palette translation table (generated with GenPal4Plane function)
//   wb = pitch - number of bytes between lines
// To scroll image, set virtual dimension wrapx and wrapy, then shift offx and offy.
void ScreenSegmPlane2(sSegm* segm, const void* data, int plane, const void* trans, int wb);

// set video segment to 2x4 bit color attribute per 8x8 pixel sample graphics
//   data = pointer to data buffer with mono pixels
//   attr = pointer to color attributes
//   pal = pointer to 16-color palette table
//   wb = pitch - number of bytes between lines
// To scroll image, set virtual dimension wrapx and wrapy, then shift offx and offy.
void ScreenSegmAttrib8(sSegm* segm, const void* data, const void* attr, const u8* pal, int wb);

// set video segment to horizontal progress indicator GF_PROGRESS
//   data = pointer to buffer with values 0..255 of 4-pixels in rows
//   sample1 = scanline sample < data
//   sample2 = scanline sample >= data
void ScreenSegmProgress(sSegm* segm, const void* data, const void* sample1, const void* sample2);

// set video segment to 8-bit graphics with 2D matrix transformation
//   data = pointer to image data (width and height of image must be power of 2)
//   mat = pointer to array of 6 matrix integer parameters m11, m12...m23 (exported with ExportInt function)
//   xbits = number of bits of image width (image width must be power of 2 and must be = pitch width bytes)
//   ybits = number of bits of image height (image height must be power of 2)
// Use default settings of parameters: offx = 0, offy = 0, wrapx = segment width, wrapy = segment height
void ScreenSegmGraph8Mat(sSegm* segm, const void* data, const int* mat, u16 xbits, u16 ybits);

// set video segment to 8-bit graphics with perspective projection
//   data = pointer to image data (width and height of image must be power of 2)
//   mat = pointer to array of 6 matrix integer parameters m11, m12...m23 (exported with ExportInt function)
//   xbits = number of bits of image width (image width must be power of 2 and must be = pitch width bytes)
//   ybits = number of bits of image height (image height must be power of 2)
//   horiz = horizon offset
// Use default settings of parameters: offx = 0, offy = 0, wrapx = segment width, wrapy = segment height
void ScreenSegmGraph8Persp(sSegm* segm, const void* data, const int* mat, u16 xbits, u16 ybits, u16 horiz);

// set video segment to tiles with perspective
//   map = pointer to tile map with tile indices (width and height must be power of 2)
//   tiles = pointer to 1 column of square tiles, 1 pixel = 8 bits (width and height must be power of 2)
//   mat = pointer to array of 6 matrix integer parameters m11, m12...m23 (exported with ExportInt function)
//   mapwbits = number of bits of tile map width
//   maphbits = number of bits of tile map height
//   tilebits = number of bits of tile width and height
//   horizon = horizon offset/4 (0=do not use perspective projection, <0=vertical flip to display ceiling)
// Use default settings of parameters: offx = 0, offy = 0, wrapx = segment width, wrapy = segment height
void ScreenSegmTilePersp(sSegm* segm, const u8* map, const u8* tiles, const int* mat, 
	u8 mapwbits, u8 maphbits, u8 tilebits, s8 horizon);

// set video segment to tiles with perspective, 1.5 pixels
//   map = pointer to tile map with tile indices (width and height must be power of 2)
//   tiles = pointer to 1 column of square tiles, 1 pixel = 8 bits (width and height must be power of 2)
//   mat = pointer to array of 6 matrix integer parameters m11, m12...m23 (exported with ExportInt function)
//   mapwbits = number of bits of tile map width
//   maphbits = number of bits of tile map height
//   tilebits = number of bits of tile width and height
//   horizon = horizon offset/4 (0=do not use perspective projection, <0=vertical flip to display ceiling)
// Use default settings of parameters: offx = 0, offy = 0, wrapx = segment width, wrapy = segment height
void ScreenSegmTilePersp15(sSegm* segm, const u8* map, const u8* tiles, const int* mat, 
	u8 mapwbits, u8 maphbits, u8 tilebits, s8 horizon);

// set video segment to tiles with perspective, double pixels
//   map = pointer to tile map with tile indices (width and height must be power of 2)
//   tiles = pointer to 1 column of square tiles, 1 pixel = 8 bits (width and height must be power of 2)
//   mat = pointer to array of 6 matrix integer parameters m11, m12...m23 (exported with ExportInt function)
//   mapwbits = number of bits of tile map width
//   maphbits = number of bits of tile map height
//   tilebits = number of bits of tile width and height
//   horizon = horizon offset/4 (0=do not use perspective projection, <0=vertical flip to display ceiling)
// Use default settings of parameters: offx = 0, offy = 0, wrapx = segment width, wrapy = segment height
void ScreenSegmTilePersp2(sSegm* segm, const u8* map, const u8* tiles, const int* mat, 
	u8 mapwbits, u8 maphbits, u8 tilebits, s8 horizon);

// set video segment to tiles with perspective, triple pixels
//   map = pointer to tile map with tile indices (width and height must be power of 2)
//   tiles = pointer to 1 column of square tiles, 1 pixel = 8 bits (width and height must be power of 2)
//   mat = pointer to array of 6 matrix integer parameters m11, m12...m23 (exported with ExportInt function)
//   mapwbits = number of bits of tile map width
//   maphbits = number of bits of tile map height
//   tilebits = number of bits of tile width and height
//   horizon = horizon offset/4 (0=do not use perspective projection, <0=vertical flip to display ceiling)
// Use default settings of parameters: offx = 0, offy = 0, wrapx = segment width, wrapy = segment height
void ScreenSegmTilePersp3(sSegm* segm, const u8* map, const u8* tiles, const int* mat, 
	u8 mapwbits, u8 maphbits, u8 tilebits, s8 horizon);

// set video segment to tiles with perspective, quadruple pixels
//   map = pointer to tile map with tile indices (width and height must be power of 2)
//   tiles = pointer to 1 column of square tiles, 1 pixel = 8 bits (width and height must be power of 2)
//   mat = pointer to array of 6 matrix integer parameters m11, m12...m23 (exported with ExportInt function)
//   mapwbits = number of bits of tile map width
//   maphbits = number of bits of tile map height
//   tilebits = number of bits of tile width and height
//   horizon = horizon offset/4 (0=do not use perspective projection, <0=vertical flip to display ceiling)
// Use default settings of parameters: offx = 0, offy = 0, wrapx = segment width, wrapy = segment height
void ScreenSegmTilePersp4(sSegm* segm, const u8* map, const u8* tiles, const int* mat, 
	u8 mapwbits, u8 maphbits, u8 tilebits, s8 horizon);

//!@}

#endif // _VGA_SCREEN_H
