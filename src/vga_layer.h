/** 
 * @file 
 * @brief VGA layers
 * @author Miroslav Nemecek <Panda38@seznam.cz>
 * @see LayersGroup
*/

#ifndef _VGA_LAYER_H
#define _VGA_LAYER_H

// base layer commands
#define VGADARK(num,col) (((u32)(vga_offset_dark+BASE_OFFSET)<<27) | ((u32)(num)<<8) | (u32)(col)) // assemble control word of "dark" command
#define VGACMD(jmp,num) (((u32)(jmp)<<27) | (u32)(num)) // assemble control word

// --- overlapped layer init word (delay: use number of offset pixels * Vmode.cpp, num: number of pixels)

// init word of key color layer LAYERPROG_KEY
#define VGAKEY(delay,num,col) (((u32)((delay)+1)<<19) | ((u32)(col)<<11) | (u32)((num)-1))

// init word of mono layer LAYERPROG_MONO
#define VGAMONO(delay,num,col) (((u32)((delay)+0)<<20) | ((u32)(col)<<12) | ((u32)((num)-1)<<1) | B0)

// init word of color layer LAYERPROG_MONO
#define VGACOLOR(delay,num) (((u32)((delay)+2)<<20) | ((u32)0xff<<12) | ((u32)((num)-1)<<1) | 0)

// init word of black color layer LAYERPROG_BLACK
#define VGABLACK(delay,num) (((u32)((delay)+3)<<16) | (u32)((num)-1))

// init word of white color layer LAYERPROG_WHITE
#define VGAWHITE(delay,num) (((u32)((delay)+3)<<16) | (u32)((num)-1))

// init word of RLE layer LAYERPROG_RLE
#define VGARLE(delay) ((delay)+1)

// swap bytes of command
#define BYTESWAP(n) ((((n)&0xff)<<24)|(((n)&0xff00)<<8)|(((n)&0xff0000)>>8)|(((n)&0xff000000)>>24))

// align to multiple of 4
#define ALIGN4(x) ((x) & ~3)

// layer program descriptor
typedef struct {
	const u16*		ins;		// pointer to program instructions (NULL=layers is OFF)
	const struct pio_program* prg;		// pointer to program descriptor
	u8			length;		// program length (number of instructions)
	u8			wrap_target;	// offset of wrap target
	u8			wrap;		// offset of wrap end
	u8			idle;		// offset of idle
	u8			entry;		// offset of entry
	u8			maxidle;	// max. offset of idle to detect end of job
	u8			extranum;	// number of extra offsets
	u8			extra[2*16];	// extra offsets, pairs: offset, CPP-correction
} sLayerProg;

// layer program descriptors
extern const sLayerProg LayerProg[LAYERPROG_NUM];

// current layer program of overlapped layers
extern u8 LayerProgInx;		// index of current layer program (LAYERPROG_*, LAYERPROG_BASE = overlapped layers are OFF)
extern sLayerProg CurLayerProg;	// copy of current layer program

// layer mode descriptor
typedef struct {
	u8	prog;		// layer program (LAYERPROG_*)
	u8	mincpp;		// minimal clock cycles per pixel
	u8	maxcpp;		// maximal clock cycles per pixel
} sLayerMode;

// layer mode descriptors
extern const sLayerMode LayerMode[LAYERMODE_NUM];

// current layer mode of layers
extern u8 LayerModeInx[LAYERS];	// index of current layer mode (LAYERMODE_*)
extern sLayerMode CurLayerMode[LAYERS]; // copy of current layer mode
extern u8 LayerMask;	// mask of active layers

/**
 * @addtogroup LayersGroup
 * @details The display of the image by the PicoVGA library is performed by the PIO processor controller. PIO0 is used. 
 * The other controller, PIO1, is unused and can be used for other purposes. PIO0 contains a 4 state machines, SM0 to SM3. 
 * All PIO0 state machines use a common program of 32 instructions. Each state machine serves 1 overlay layer. SM0 services 
 * base layer 0, along with servicing the synchronization signal. The base layer service program consists of 15 instructions, 
 * starting at offset 17. This part of the program is immutable and is always used. However, the other 3 layers, 1 to 3, SM1 to SM3, 
 * use the other part of the program memory, 17 instructions starting at address 0. This part may change, depending on the mode 
 * of the overlay layers. All 3 overlay layers use a common program and must therefore operate in the same display mode. Some 
 * overlay modes use the same program and can be shared - see the table below for details.
 * @note Only base layer 0 can contain segments in different formats. Overlay layers 1 to 3 are independent of the base layer 
 * format, sharing only the total display area with the base layer, but using their own image format, for which only the 
 * coordinates and dimensions are specified. 
 * 
 * <h3>Overlay layers can use one of the following programs:</h3>
 * * <b>LAYERPROG_BASE</b> - The base layer 0 program. Cannot be used for overlay layers. Using the parameter 
 * for an overlay layer means that the layer is inactive (not using the program).
 * * <b>LAYERPROG_KEY</b> - Layer with key color. The specified color is replaced by transparency.
 * * <b>LAYERPROG_BLACK</b> - Transparency with black color. Black is replaced by transparency. Compared to the previous mode, 
 * the advantage is less demanding on processor speed.
 * * <b>LAYERPROG_WHITE</b> - transparency with white colour. It is faster like the previous function and is suitable for use
 * where black needs to be preserved but white can be omitted. When preparing the image, the image is not copied from Flash to 
 * RAM with the memcpy function, but the CopyWhiteImg() function is used. The function ensures that the pixels of the copied 
 * image are incremented by 1. This changes the white color (with a value of 255) to black (with a value of 0). From this point 
 * on, the image is treated as if it had transparency with black - e.g. the black color is specified for the sprite rendering 
 * function. Only when the image enters the program in PIO0, the program makes the pixel transparent as in the case of black, 
 * but at the same time decrements the pixel value. This reverts the colors back to the original value, the black color becomes 
 * black and the white color has been used as transparency.
 * * <b>LAYERPROG_MONO</b> - This programme includes 2 sub-programmes. The first is the display of a monochrome image. For each 
 * bit of image data, either the selected image color is displayed or the corresponding pixel is transparent. This mode is used 
 * in the Oscilloscope example to display a grid across the oscilloscope screen. The second subroutine is to display a color 
 * image without transparency. The color pixels are displayed as they are, with no transparency option, but the dimensions of 
 * the image rectangle and its coordinate on the display can be defined. Thus, a sort of analogy of a single rectangular sprite 
 * without transparency.
 * * <b>LAYERPROG_RLE</b> - RLE compression mode. RLE compression is not a universally valid format. It means that the data 
 * contains segment length information. In this case, the image data of PicoVGA library contain directly instructions for the 
 * PIO program. More specifically, the image data is interleaved with the jump addresses inside the program. The image is 
 * prepared using the RaspPicoRle program and is strongly coupled to the layer program used. If, for example, the instructions 
 * in the program were shifted, the RLE compression format would stop working. This is also why the program for base layer 0 
 * is placed at the end of the program memory and the overlay layer programs at the beginning - to reduce the chance that 
 * changes in the program will change the location of the program in memory, at which point RLE compression would stop working. 
 * After modifying the RLE program in PIO, the conversion program must also be updated.
 * 
 * The desired mode of each overlay layer is specified in the video mode definition using the VgaCfg() function. The layer mode 
 * is used to derive the program and function used to operate the layer rendering. Multiple layer modes can share the same 
 * program type. Layer modes have different state machine timing requirements. The configuration function takes this into 
 * account and adjusts the processor frequency accordingly.
 * 
 * <h3>Modes of overlay layers:</h3>
 * 
 * *WHITE modes using white transparent color require image preparation using CopyWhiteImg() as specified for LAYERPROG_WHITE.
 * * <b>LAYERMODE_BASE</b> - Indicates base layer mode 0. Cannot be used for an overlay layer, but is used to indicate an inactive 
 * disabled overlay layer.
 * * <b>LAYERMODE_KEY</b> - The layer with the specified key color.
 * * <b>LAYERMODE_BLACK</b> - Layer with black key color.
 * * <b>LAYERMODE_WHITE</b> - Layer with white key color.
 * * <b>LAYERMODE_MONO</b> - Monochromatic image.
 * * <b>LAYERMODE_COLOR</b> - Colour image (without transparency).
 * * <b>LAYERMODE_RLE</b> - Image with RLE compression.
 * * <b>LAYERMODE_SPRITEKEY</b> - Sprays with the specified key color.
 * * <b>LAYERMODE_SPRITEBLACK</b> - Sprays with black key color.
 * * <b>LAYERMODE_SPRITEWHITE</b> - Sprays with white key color.
 * * <b>LAYERMODE_FASTSPRITEKEY</b> - Fast sprites with the specified key colour.
 * * <b>LAYERMODE_FASTSPRITEBLACK</b> - Fast sprites with black key colour.
 * * <b>LAYERMODE_FASTSPRITEWHITE</b> - Fast sprites with white key colour.
 * * <b>LAYERMODE_PERSPKEY</b> - Image with transformation matrix with specified key color.
 * * <b>LAYERMODE_PERSPBLACK</b> - Image with transformation matrix with black key color.
 * * <b>LAYERMODE_PERSPWHITE</b> - Image with transformation matrix with white key color.
 * * <b>LAYERMODE_PERSP2KEY</b> - Image with transformation matrix with specified key color and doubled width.
 * * <b>LAYERMODE_PERSP2BLACK</b> - Image with transformation matrix with black key color and doubled width.
 * * <b>LAYERMODE_PERSP2WHITE</b> - Image with transformation matrix with white key color and doubled width.
 * 
 * <h3>Shared overlay modes</h3>
 *
 * Layer modes can only be combined together if they use the same program. CPP is the minimum required number of SMx clock
 * cycles per pixel.
 * |							|PROG_BASE  |PROG_KEY	|PROG_BLACK	|PROG_WHITE	|PROG_MONO	|PROG_RLE	|CPP	|
 * |----------------------------|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|:-----:|
 * |LAYERMODE_BASE 				| X			|			|			|			|  	  	  	| 			| 2		|
 * |LAYERMODE_KEY 	  			|			| X			|			|			|			| 			| 6		|
 * |LAYERMODE_BLACK 	  	  	|			|			| X 	  	|			|			|  	  		| 4		|
 * |LAYERMODE_WHITE 	  	  	|  			|			|			| X 		|			|			| 4		|
 * |LAYERMODE_MONO 	  	  		|  	  		|			|			|			| X 	  	| 			| 4		|
 * |LAYERMODE_COLOR 	  	  	|  	  		|			|			|			| X			| 	 	  	| 2		|
 * |LAYERMODE_RLE 	  	  		|  	  	  	|			|			|			|			| X			| 3		|
 * |LAYERMODE_SPRITEKEY 	  	|			| X 	  	|			|			|			|			| 6		|
 * |LAYERMODE_SPRITEBLACK		| 	  	  	|			| X			|			|			|			| 4		|
 * |LAYERMODE_SPRITEWHITE		| 	  	  	|			|			| X			|			|			| 4		|
 * |LAYERMODE_FASTSPRITEKEY		|			| X 	  	|			|			|			|			| 6		|
 * |LAYERMODE_FASTSPRITEBLACK	| 	  	  	|			| X			|			|			|			| 4		|
 * |LAYERMODE_FASTSPRITEWHITE	| 	  	  	|			|			| X			|			|			| 4		|
 * |LAYERMODE_PERSPKEY 	  		|			| X 	  	|			|			|			|			| 6		|
 * |LAYERMODE_PERSPBLACK 		| 	  	  	|			| X			|			|			|			| 4		|
 * |LAYERMODE_PERSPWHITE 		| 	  	  	|			|			| X			|			|			| 4		|
 * |LAYERMODE_PERSP2KEY 	  	|			| X 	  	|			|			|			|			| 6		|
 * |LAYERMODE_PERSP2BLACK 		| 	  	  	|			| X			|			|			|			| 4		|
 * |LAYERMODE_PERSP2WHITE 		| 	  	  	|			|			| X			|			|			| 4		|
 * 
 * <h3>Selection of write planes</h3>
 * 
 * By default, the image is output from the layers to all output pins. This can be changed by redefining the LayerFirstPin 
 * and LayerNumPin fields (in vga_layer.cpp). It is possible to specify for each layer separately which output pins will 
 * be written to. This can create a kind of pseudo-transparency. For example, one layer will render curves in red, another 
 * layer in green, and the colors will blend independently. When redefining the pins, however, you must take into account 
 * that the offset of the pin mapping will shift. The output will always start from the lowest bits of the pixel.
 * 
 * <h3>Configure overlay layers</h3>
 * 
 * The first step for setting up the overlay layer is to specify the layer mode for the VgaCfg() initialization function. 
 * The function detects the required program and the required timing. It does not check if the correct layer modes are 
 * combined together.
 *
 * The second step is to initialize the layer descriptor - the sLayer structure in the LayerScreen field. It is convenient 
 * to use the LayerSetup() initialization function for this.
 * @{ 
*/

/// Layer screen descriptor (on change update SLAYER_* in define.h)
typedef struct {
	const u8*	img;	///< Pointer to image in current layer format, or sprite list
	const void*	par;	///< Additional parameter (RLE index table, integer transformation matrix)
	u32		init;		///< Init word sent on start of scanline (start X coordinate)
	u32		keycol;		///< Key color
	u16		trans;		///< Trans count
	s16		x;			///< Start X coordinate
	s16		y;			///< Start Y coordinate
	u16		w;			///< Width in pixels
	u16		h;			///< Height
	u16		wb;			///< Image width in bytes (pitch of lines)
	u8		mode;		///< Layer mode
	s8		horiz;		///< Horizon of perspective projection/4 (only with LAYERMODE_PERSP* modes, 0=no perspecitve, <0 ceilling)
	u8		xbits;		///< Number of bits of width of source image (only with LAYERMODE_PERSP* modes)
	u8		ybits;		///< Number of bits of height of source image (only with LAYERMODE_PERSP* modes)
	u16		spritenum; 	///< Number of sprites
	Bool	on;			///< Layer is ON
	u8		cpp;		///< Current clock pulses per pixel (used to calculate X coordinate)
} sLayer;

/// Sprite (on change update SSPRITE_* in define.h)
typedef struct {
	u8*	img;	///< SSPRITE_IMG pointer to image data
	u8*	x0;		///< SSPRITE_X0 pointer to array of start of lines, or fast sprite start of lines/4
	u8*	w0;		///< SSPRITE_W0 pointer to array of length of lines, or fast sprite length of lines/4
	u32	keycol;	///< SSPRITE_KEYCOL key color
	s16	x;		///< SSPRITE_X sprite X-coordinate on the screen
	s16	y;		///< SSPRITE_Y sprite Y-coordinate on the screen
	u16	w;		///< SSPRITE_W sprite width (slow sprite: max. width 255)
	u16	h;		///< SSPRITE_H sprite height
	u16	wb;		///< SSPRITE_WB sprite pitch (number of bytes between lines)
	u16	res;	///< Reserved, structure align
} sSprite;

/// Current layer screens
extern sLayer LayerScreen[LAYERS]; 

/// Index of first pin of layer (base layer should stay VGA_GPIO_FIRST)
extern u8 LayerFirstPin[LAYERS_MAX];

/// Number of pins of overlapped layer (base layer should stay VGA_GPIO_OUTNUM)
extern u8 LayerNumPin[LAYERS_MAX];

/**
 * @brief Set overlapped layer 1..3 ON 
 * @param inx Layer index
*/
void LayerOn(u8 inx);

/**
 * @brief Set overlapped layer 1..3 OFF 
 * @param inx Layer index
*/
void LayerOff(u8 inx);

/**
 * @brief Set coordinate X of overlapped layer
 * @param inx Layer index
 * @param x X coordinate
*/
void LayerSetX(u8 inx, s16 x);

/**
 * @brief Set coordinate Y of overlapped layer
 * @param inx Layer index
 * @param y Y coordinate
*/
void LayerSetY(u8 inx, s16 y);
  
/**
 * @brief Set width of image of overlapped layer
 * @note Uses auto pitch wb (full line). Set custom wb after calling this function.
 * @param inx Layer index
 * @param w Width
*/
void LayerSetW(u8 inx, u16 w);

/**
 * @brief Set height of image of overlapped layer
 * @param inx Layer index
 * @param h Height
*/
void LayerSetH(u8 inx, u16 h);

/**
 * @brief Setup overlapped layer 1..3 (not for sprites or perspective mode)
 * @details  The function sets the dimensions of the image and its address. The coordinates are cleared. The position of the 
 * image on the screen can be set by the LayetSetX() and LayerSetY() functions. The coordinates do not depend on the graphic 
 * modes of the base layer and refer to the upper left corner of the active screen area. After initialization, the layer remains 
 * disabled. Layer visibility must be turned on by calling the LayerOn() function.
 * @param inx Layer index 1..3
 * @param img Pointer to image data
 * @param vmode Pointer to initialized video configuration
 * @param w Image width in pixels (must be multiple of 4)
 * @param h Image height
 * @param col Key color (Needed for LAYERMODE_KEY and LAYERMODE_MONO. For both *BLACK and *WHITE modes, specify COL_BLACK or 0)
 * @param par Additional data (RLE index table, integer transformation matrix)
*/
void LayerSetup(u8 inx, const u8* img, const sVmode* vmode, u16 w, u16 h, u8 col = 0, const void* par = NULL);

/**
 * @brief Setup overlapped layer 1..3 for LAYERMODE_PERSP* modes
 * @details In contrast to the LayerSetup() function, the dimensions of the source image in number of bits (the image dimensions 
 * must be a power of 2), the height of the horizon/4 (for a negative value the floor turns into a ceiling, for zero the 
 * perspective transformation is not applied) and the pointer to the transformation matrix in integer form are also specified.
 * @param inx Layer index 1..3
 * @param img Pointer to source image data (image width and height must be power of 2)
 * @param vmode Pointer to initialized video configuration
 * @param w Destination image width in pixels (must be multiple of 4)
 * @param h Destination image height
 * @param xbits Number of bits of width of source image
 * @param ybits Number of bits of height of source image
 * @param horiz Horizon of perspective projection/4 (0=no perspecitve, <0 ceilling)
 * @param mat Integer transformation matrix
 * @param col Key color (needed for LAYERMODE_PERSPKEY layer mode)
*/
void LayerPerspSetup(u8 inx, const u8* img, const sVmode* vmode, u16 w, u16 h, u8 xbits, u8 ybits,
	s8 horiz, const int* mat, u8 col = 0);

/// @}

/**
 * @addtogroup SpriteGroup
 * @details Sprites can be used in overlay planes with KEY, BLACK and WHITE programs. There are two ways to use the sprites:
 * 
 * 1. Slow sprites, LAYERMODE_SPRITE* modes. Sprites are software generated. The line rendering function first clears the line 
 * buffer with a transparent color and then sequentially passes through the array of sprites. It looks for which sprites overlap 
 * a given Y address and, if so, renders the line into the buffer. Sprites in this mode have the advantage that they can overlap 
 * arbitrarily (the order of overlapping is based on the order of location in the address array) and can scroll subtly pixel by 
 * pixel. The main disadvantage is the high rendering overhead. Even a small number of sprites can cause a line rendering time
 * overflow and thus an video dropout. However, it is important to note that the number of sprites (and their dimensions) on the 
 * same video line is involved. Sprites at distant Y-coordinates are not affected. To check if the rendering function will 
 * handle a given number of sprites, place the sprites horizontally next to each other. Conversely, if you want to ensure low 
 * rendering requirements, ensure that the sprites are not in the same vertical Y coordinates. Or reduce the width of the sprites.
 * 
 * 2. Fast sprites, LAYERMODE_FASTSPRITE* modes. Sprites are not software rendered to the render buffer, but are sent directly to 
 * PIO via DMA transfer. This makes the rendering of sprites very fast and allows multiple sprites to be displayed side by side. 
 * Of course, this brings disadvantages on the other side. The X-coordinate of the sprites and their width must be a multiple of 4,
 * and the sprites cannot be scrolled finely on the screen (does not apply to the Y-coordinate). But most importantly, the sprites 
 * cannot directly overlap. One sprite can continue rendering where the previous sprite left off. Thus, the previous sprite can cut
 * off the beginning of the next sprite. There is a treatment that can slightly improve the situation. To improve overlays (and 
 * speed up rendering), the sprite includes a table that indicates how many pixels from the edge the opaque sprite line starts 
 * and how long it is. The SpritePrepLines() function can be used to generate the table. For fast sprites, this information must be 
 * a multiple of 4. Thus, if we ensure that the beginnings and ends of the image lines start and end at multiples of 4, the 
 * sprites will overlap almost correctly (unless they have internal transparency). Otherwise, transparent holes may appear at 
 * the point of overlap. One of the requirements for fast sprites is that the list of sprites must be sorted by the X coordinate. 
 * The SortSprite() support function is used for this purpose.
 * 
 * When using sprites, the first step will be to specify the LAYERMODE_*SPRITE* layer mode for the VgaCfg() initialization 
 * function.
 * 
 * The second step will be to build an array of sprite pattern line starts and lengths using the SpritePrepLines() function. 
 * The function will be passed a pointer to the image of each sprite (only 8-bit sprites are supported), the image dimensions, 
 * the pointers to the array of origin and line lengths (the array dimensions correspond to the height of the sprite), and the 
 * key transparency color. The function searches for line starts and line ends and writes them into the fields. The 'fast' 
 * parameter specifies whether the tables are generated for fast sprites, in which case the line starts and lengths are divided 
 * by 4. For slow sprites, the sprite width must be limited to 255 pixels.
 * 
 * The third step is to build a list of sprites and initialize the sprites - especially the pointer to the image, the dimensions 
 * and coordinates of the sprites. The sprite list is an array of pointers to the sprite. Each sprite can only be in the list 
 * once, but multiple sprite can share the same sprite image and the same array of line starts and lengths. Slow sprites can have 
 * coordinates outside the allowed range (they will be cropped), but for fast sprites I recommend not to exceed the horizontal 
 * limits of the screen, the cropping of the image is not yet properly tuned and the program might crash.
 * 
 * While the sprites don't have a parameter to turn them off, they can be turned off by setting the Y coordinate out off screen. 
 * During rendering, visible sprites are searched for by the Y coordinate, an invalid Y coordinate will ensure that the sprite 
 * is safely disabled.
 * 
 * Fast sprites require sorting the list by the X coordinate. This is done by the SortSprite() function, which is passed a pointer 
 * to the list of sprites and the number of sprites in the list. This function should be called whenever you change the X 
 * coordinate of the sprite. Transient conditions (e.g. momentary mis-overlapping of sprites) do not matter, they are just 
 * short-term optical errors, they do not compromise the program. The function sorts using the bubble method, so it is quite 
 * slow, but so far it does not seem to harm anything (there are not many sprays).
 * 
 * The last step is the initialization of the layer with the sprite. The function was described in the previous chapter.
 * 
 * The next step is to turn on layer visibility with LayerOn() and control the sprites by changing their X and Y coordinates and 
 * changing their img images.
 * 
 * @{
*/

/**
 * @brief Setup overlapped layer 1..3 for LAYERMODE_SPRITE* and LAYERMODE_FASTSPRITE* modes
 * @details It differs from the other setup functions by specifying the coordinate of the sprite area, the pointer to the 
 * sprite address array and the number of sprites.
 * @param inx Layer index 1..3
 * @param sprite Pointer to list of sprites (array of pointers to sprites; sorted by X on LAYERMODE_FASTSPRITE* modes)
 * @param spritenum Number of sprites in the list (to turn sprite off, you can set its coordinate Y out of the screen)
 * @param vmode Pointer to initialized video configuration
 * @param x Start coordinate X of area with sprites
 * @param y Start coordinate Y of area with sprites
 * @param w Width of area with sprites (must be multiple of 4)
 * @param h Height of area with sprites
 * @param col Key color (needed for LAYERMODE_SPRITEKEY and LAYERMODE_FASTSPRITEKEY layer mode)
 * @see LayersGroup
*/
void LayerSpriteSetup(u8 inx, sSprite** sprite, u16 spritenum, const sVmode* vmode,
	s16 x, s16 y, u16 w, u16 h, u8 col = 0);

/**
 * @brief Prepare array of start and length of lines (detects transparent pixels)
 * @details The function will be passed a pointer to the image of each sprite (only 8-bit sprites are supported), the image 
 * dimensions, the pointers to the array of origin and line lengths (the array dimensions correspond to the height of the sprite), 
 * and the key transparency color. The function searches for line starts and line ends and writes them into the fields. 
 * The 'fast' parameter specifies whether the tables are generated for fast sprites, in which case the line starts and lengths 
 * are divided by 4. For slow sprites, the sprite width must be limited to 255 pixels.
 * @param img Pointer to image
 * @param x0 Array of start of lines
 * @param w0 Array of length of lines
 * @param w Sprite width (slow sprite: max. width 255)
 * @param h Sprite height
 * @param wb Sprite pitch (bytes between lines)
 * @param col Key color
 * @param fast Fast sprite, divide start and length of line by 4
*/
void SpritePrepLines(const u8* img, u8* x0, u8* w0, u16 w, u16 h, u16 wb, u8 col, Bool fast);

/**
 * @brief Sort fast sprite list by X coordinate
 * @details Fast sprites require sorting the list by the X coordinate. Pass a pointer to the list of sprites and the number of 
 * sprites in the list. This function should be called whenever you change the X coordinate of the sprite. Transient conditions 
 * (e.g. momentary mis-overlapping of sprites) do not matter, they are just short-term optical errors, they do not compromise 
 * the program. The function sorts using the bubble method, so it is quite slow, but so far it does not seem to harm anything 
 * (there are not many sprays).
 * @param list Sprite list
 * @param num Number of sprites
*/
void SortSprite(sSprite** list, int num);

/// @}

#endif // _VGA_LAYER_H
