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
 * The other controller, PIO1, is unused and can be used for other purposes. PIO0 contains a 4 state machine, SM0 to SM3. 
 * All PIO0 state machines use a common program of 32 instructions. Each state machine serves 1 overlay layer. SM0 services 
 * base layer 0, along with servicing the synchronization signal. The base layer service program consists of 15 instructions, 
 * starting at offset 17. This part of the program is immutable and is always used. The other 3 layers, 1 to 3, SM1 to SM3, 
 * use the other part of the program memory, 17 instructions starting at address 0. This part may change, depending on the mode 
 * of the overlay layers. All 3 overlay layers use a common program and must therefore operate in the same display mode. Some 
 * overlay modes use the same program and can be shared - see the table below for details.
 * @note Only base layer 0 can contain segments in different formats. Overlay layers 1 to 3 are independent of the base layer 
 * format, sharing only the total display area with the base layer, but using their own image format, for which only the 
 * coordinates and dimensions are specified. 
 * @par 
 * Overlay layers can use one of the following programs:
 * * <b>LAYERPROG_BASE</b> - The base layer 0 program. Cannot be used for overlay layers. Using the parameter 
 * for an overlay layer means that the layer is inactive (not using the program).
 * * <b>LAYERPROG_KEY</b> - Layer with key color. The specified color is replaced by transparency.
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
