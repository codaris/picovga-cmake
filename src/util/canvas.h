/**
 * @file
 * @brief Canvas
 * @author Miroslav Nemecek <Panda38@seznam.cz>
 * @see CanvasGroup
*/

#ifndef _CANVAS_H
#define _CANVAS_H

#define DRAW_HWINTER	1	// 1=use hardware interpolator to draw images

/**
 * @addtogroup CanvasGroup
 * @brief Drawing board for shapes and images
 * @details Canvas is a drawing board. It is a support library for working with graphical surfaces and images.
 * The sCanvas structure is a set of parameters that describe the graphical surface, for use
 * in drawing functions. A graphical surface can be either a graphical frame buffer or an image, even in Flash. To draw in a
 * graphical surface, first attach a canvas to it as a definition describing the structure of the area. Likewise, if you want
 * to draw an image to the surface, first create a canvas for the image with its parameters. The parameters are a pointer to
 * the image data, the image dimensions, and the format. The drawing area can be a graphic area with a depth of 1, 2, 4, 8 bits
 * or with attributes. In the case of drawing an image to a canvas, the source and target canvas must have the same format.
 * In the case of transformation matrices, only an 8-bit graphic format can be drawn.
 * @note In PicoVGA, a default canvas @link Canvas @endlink is available. A graphic frame buffer is automatically attached to it when
 * initialized with the Video() function. Otherwise, it can be used arbitrarily in the program.
 * @{
*/

// canvas format
//   Note: do not use enum, symbols could not be used by the preprocessor
#define CANVAS_8	0	///< 8-bit pixels
#define CANVAS_4	1	///< 4-bit pixels
#define CANVAS_2	2	///< 2-bit pixels
#define CANVAS_1	3	// 1-bit pixels
#define CANVAS_PLANE2	4	///< 4 colors on 2 planes
#define CANVAS_ATTRIB8	5	///< 2x4 bit color attributes per 8x8 pixel sample
							///< draw functions: bit 0..3 = draw color
							///< bit 4 = draw color is background color

/// Canvas descriptor
typedef struct {
	u8*	img;		///< Image data
	u8*	img2;		///< Image data 2 (2nd plane of CANVAS_PLANE2, attributes of CANVAS_ATTRIB8)
	int	w;			///< Width
	int	h;			///< Height
	int	wb;			///< Pitch (bytes between lines)
	u8	format;		///< Canvas format CANVAS_*
} sCanvas;

/**
 * @brief Draw rectangle
 * @param canvas Canvas
 * @param x Horizontal position
 * @param y Veritical position
 * @param w Width
 * @param h Height
 * @param col Color
*/
void DrawRect(sCanvas* canvas, int x, int y, int w, int h, u8 col);

/**
 * @brief Draw frame of 1 pixel thickness
 * @param canvas Canvas
 * @param x Horizontal position
 * @param y Veritical position
 * @param w Width
 * @param h Height
 * @param col Color
*/
void DrawFrame(sCanvas* canvas, int x, int y, int w, int h, u8 col);

/**
 * @brief Clear canvas (fill with black color)
 * @param canvas Canvas
*/
void DrawClear(sCanvas* canvas);

/**
 * @brief Draw a pixel
 * @param canvas Canvas
 * @param x Horizontal position
 * @param y Veritical position
 * @param col Color
*/
void DrawPoint(sCanvas* canvas, int x, int y, u8 col);

/**
 * @brief Draw a line
 * @param canvas Canvas
 * @param x1 Horizontal start position
 * @param y1 Veritical start position
 * @param x2 Horizontal end position
 * @param y2 Veritical end position
 * @param col Color
*/
void DrawLine(sCanvas* canvas, int x1, int y1, int x2, int y2, u8 col);

/**
 * @brief Draw filled circle
 * @param canvas Canvas
 * @param x0 Horizontal center coordinate
 * @param y0 Veritical center coordinate
 * @param r Radius
 * @param col Color (with CANVAS_ATTRIB8 format: bit 0..3 = draw color, bit 4 = draw color is background color)
 * @param mask Mask.  Specifies, using bits 0 to 7, which eighths of the circle are drawn.
 * <pre>
 *         . B2|B1 .
 *       B3 .  |  . B0
 *       ------o------
 *       B4 .  |  . B7
 *         . B5|B6 .
 * </pre>
*/
void DrawFillCircle(sCanvas* canvas, int x0, int y0, int r, u8 col, u8 mask=0xff);

/**
 * @brief Draw circle
 * @param canvas Canvas
 * @param x0 Horizontal center coordinate
 * @param y0 Veritical center coordinate
 * @param r Radius
 * @param col Color (with CANVAS_ATTRIB8 format: bit 0..3 = draw color, bit 4 = draw color is background color)
 * @param mask Mask.  Specifies, using bits 0 to 7, which eighths of the circle are drawn.
 * <pre>
 *         . B2|B1 .
 *       B3 .  |  . B0
 *       ------o------
 *       B4 .  |  . B7
 *         . B5|B6 .
 * </pre>
*/
void DrawCircle(sCanvas* canvas, int x0, int y0, int r, u8 col, u8 mask=0xff);

/**
 * @brief Draw text (transparent background)
 * @param canvas Canvas
 * @param text C string to draw
 * @param x Horizontal position
 * @param y Verticle position
 * @param col Text color
 * @param font Pointer to 1-bit font
 * @param fontheight Height of font in pixels (default 8)
 * @param scalex Magnification scale in X dimension
 * @param scaley Magnification scale in Y dimension
*/
void DrawText(sCanvas* canvas, const char* text, int x, int y, u8 col,
	const void* font, int fontheight=8, int scalex=1, int scaley=1);

/**
 * @brief Draw text with background color
 * @param canvas Canvas
 * @param text C string to draw
 * @param x Horizontal position
 * @param y Verticle position
 * @param col Text color
 * @param bgcol Background color
 * @param font Pointer to 1-bit font
 * @param fontheight Height of font in pixels (default 8)
 * @param scalex Magnification scale in X dimension
 * @param scaley Magnification scale in Y dimension
*/
void DrawTextBg(sCanvas* canvas, const char* text, int x, int y, u8 col, u8 bgcol,
	const void* font, int fontheight=8, int scalex=1, int scaley=1);

/**
 * @brief Draw image (without transparency)
 * @param canvas Destination canvas
 * @param src Source canvas
 * @param xd Destination horizontal postion
 * @param yd Destination vertical position
 * @param xs Source horizontal position
 * @param ys Source vertical position
 * @param w Width
 * @param h Height
*/
void DrawImg(sCanvas* canvas, sCanvas* src, int xd, int yd, int xs, int ys, int w, int h);

/**
 * @brief Draw image with transparency
 * @note Source and destination must have same format.  CANVAS_ATTRIB8 format replaced by DrawImg() function.
 * @param canvas Destination canvas
 * @param src Source canvas
 * @param xd Destination horizontal postion
 * @param yd Destination vertical position
 * @param xs Source horizontal position
 * @param ys Source vertical position
 * @param w Width
 * @param h Height
 * @param col Transparency key color
*/
void DrawBlit(sCanvas* canvas, sCanvas* src, int xd, int yd, int xs, int ys, int w, int h, u8 col);

/// DrawImgMat mode
enum {
	DRAWIMG_WRAP,		///< Wrap image
	DRAWIMG_NOBORDER,	///< No border (transparent border)
	DRAWIMG_CLAMP,		///< Clamp image (use last pixel as border)
	DRAWING_COLOR,		///< Color border
	DRAWIMG_TRANSP,		///< Transparent image with key color
	DRAWIMG_PERSP,		///< Perspective floor
};

/**
 * @brief Draw 8-bit image with 2D transformation matrix
 * @note To wrap and perspective mode: Width and height of source image must be power of 2.
 * @param canvas Destination canvas
 * @param src Source canvas with image
 * @param x Destination horizontal postion
 * @param y Destination vertical position
 * @param w Destination width
 * @param h Destination height
 * @param m Transformation matrix (should be prepared using cMat2Df::PrepDrawImg() function)
 * @param mode Mode enum value
 * @param color Key or border color
*/
void DrawImgMat(sCanvas* canvas, const sCanvas* src, int x, int y, int w, int h,
	const class cMat2Df* m, u8 mode, u8 color);

/**
 * @brief Draw tile map using perspective projection
 * @param canvas Destination canvas
 * @param src Source canvas with column of 8-bit square tiles (width = tile size, must be power of 2)
 * @param map Byte map of tile indices
 * @param mapwbits Number of bits of map width (number of tiles; width must be power of 2)
 * @param maphbits Number of bits of map height (number of tiles; height must be power of 2)
 * @param tilebits Number of bits of tile size (e.g. 5 = tile 32x32 pixel)
 * @param x Destination horizontal postion
 * @param y Destination vertical position
 * @param w Destination width
 * @param h Destination height
 * @param mat Transformation matrix (should be prepared using cMat2Df::PrepDrawImg() function)
 * @param horizon Horizon offset (0 = do not use perspective projection)
*/
void DrawTileMap(sCanvas* canvas, const sCanvas* src, const u8* map, int mapwbits, int maphbits,
	int tilebits, int x, int y, int w, int h, const cMat2Df* mat, u8 horizon);

/**
 * @brief Draw image line interpolated
 * @note Overflow in X direction is not checked
 * @param canvas Destination canvas (8-bit pixel format)
 * @param src Source canvas (source image in 8-bit pixel format)
 * @param xd Destination horizontal postion
 * @param yd Destination vertical position
 * @param xs Source horizontal position
 * @param ys Source vertical position
 * @param wd Destination width
 * @param ws Source width
*/
void DrawImgLine(sCanvas* canvas, sCanvas* src, int xd, int yd, int xs, int ys, int wd, int ws);

/// @}

#endif // _CANVAS_H
