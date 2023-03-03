
// ****************************************************************************
//
//                                 VGA videomodes
//
// ****************************************************************************

#ifndef _VGA_VMODE_H
#define _VGA_VMODE_H

//!@addtogroup VideoMode Video mode configuration
//!@brief Structures and functions for video modes
//!@details The video mode can be initialized either simply by the Video function or in more detail by the other functions.
//!@{

#define VIDEO_NAME_LEN	5	//!< length of video timing name

//! Video timings structure
typedef struct {
	// horizontal
	float	htot;		//!< Horizontal total scanline in [us]
	float	hfront;		//!< Horizontal front porch (after image, before HSYNC) in [us]
	float	hsync;		//!< Horizontal sync pulse in [us]
	float	hback;		//!< Horizontal back porch (after HSYNC, before image) in [us]
	float	hfull;		//!< Horizontal full visible in [us] (corresponding to 'wfull' pixels)

	// vertical
	u16	vtot;		//!< Vertical total scanlines (both subframes)
	u16	vmax;		//!< Vertical maximal height

	// subframe 1
	u16	vsync1;		//!< V sync (half-)pulses on subframe 1
	u16	vpost1;		//!< V sync post half-pulses on subframe 1
	u16	vback1;		//!< V back porch (after VSYNC, before image) on subframe 1
	u16	vact1;		//!< active visible scanlines, subframe 1
	u16	vfront1;	//!< V front porch (after image, before VSYNC) on subframe 1
	u16	vpre1;		//!< V sync pre half-pulses on subframe 1

	// subframe 2 (ignored if not interlaced)
	u16	vsync2;		//!< V sync half-pulses on subframe 2
	u16	vpost2;		//!< V sync post half-pulses on subframe 2
	u16	vback2;		//!< V back porch (after VSYNC, before image) on subframe 2
	u16	vact2;		//!< active visible scanlines, subframe 2
	u16	vfront2;	//!< V front porch (after image, before VSYNC) on subframe 2
	u16	vpre2;		//!< V sync pre half-pulses on subframe 2

	// name
	const char* name;	//!< video timing name (VIDEO_NAME_LEN characters + terminating 0)

	// flags
	bool	inter;		//!< interlaced (use subframes)
	bool	psync;		//!< positive synchronization
	bool	odd;		//!< first sub-frame is odd lines 1, 3, 5,... (PAL)
} sVideo;


// === TV videomodes

//! TV PAL interlaced 5:4 720x576 (4:3 768x576, 16:9 1024x576)
extern const sVideo VideoPAL;

//! TV PAL progressive 5:4 360x288 (4:3 384x288, 16:9 512x288)
extern const sVideo VideoPALp;

//! TV NTSC interlaced 4:3 640x480 (5:4 600x480, 16:9 848x480)
extern const sVideo VideoNTSC;

//! TV NTSC progressive 4:3 320x240 (5:4 300x240, 16:9 424x240)
extern const sVideo VideoNTSCp;

// === Monitor videomodes

//! EGA 8:5 640x400 (5:4 500x400, 4:3 528x400, 16:9 704x400), vert. 70 Hz, hor. 31.4685 kHz, pixel clock 25.175 MHz
extern const sVideo VideoEGA;

//! VGA 4:3 640x480 (16:9 848x480), vert. 60 Hz, hor. 31.4685 kHz, pixel clock 25.175 MHz
extern const sVideo VideoVGA;

//! SVGA 4:3 800x600 (16:9 1064x600), vert. 60 Hz, hor. 37.897 kHz, pixel clock 40 MHz
extern const sVideo VideoSVGA;

//! XGA 4:3 1024x768 (16:9 1360x768), vert. 60 Hz, hor. 48.36310 kHz, pixel clock 65 MHz
extern const sVideo VideoXGA;

//! VESA 4:3 1152x864, vert. 60 Hz, hor. 53.697 kHz, pixel clock 81.62 MHz
extern const sVideo VideoVESA;

//! HD 4:3 1280x960, vert. 53 Hz, hor. 51.858 kHz, pixel clock 102.1 MHz
extern const sVideo VideoHD;

//! Required configuration to initialize VGA output
typedef struct {
	u16	width;				//!< Width in pixels
	u16	height;				//!< Height in lines
	u16	wfull;				//!< Width of full screen, corresponding to 'hfull' time (0=use 'width' parameter)
	const sVideo* video;	//!< Used video timings
	u32	freq;				//!< Required minimal system frequency in kHz (real frequency can be higher)
	u32	fmax;				//!< Maximal system frequency in kHz (limit resolution if needed)
	u8	mode[LAYERS_MAX];	//!< Modes of overlapped layers 0..3 LAYERMODE_* (LAYERMODE_BASE = layer is off)
							//!<  - mode of layer 0 is ignored (always use LAYERMODE_BASE)
							//!<  - all overlapped layers must use same layer program
	bool	dbly;			//!< double in Y direction
	bool	lockfreq;		//!< Lock required frequency, do not change it
} sVgaCfg;

//! Videomode table - used to setup video driver
typedef struct {
	// screen resolution
	u16	width;		//!< Screen width in pixels
	u16	height; 	//!< Screen height in lines
	u16	wfull;		//!< Screen width of full screen (corresponding to 'hfull' time)
	u16	wmax;		//!< Screen maximal width (corresponding to 'hmax' time)

	// setup PLL system clock
	u32	freq;		//!< system clock frequency in kHz
	u32	vco;		//!< VCO frequency in kHz
	u16	fbdiv;		//!< fbdiv PLL divider
	u8	pd1;		//!< postdiv1
	u8	pd2;		//!< postdiv2

	// setup PIO state machine	
	u16	div;				//!< PIO divide base state machine clock
	u16	cpp;				//!< State machine clocks per pixel
	u8	prog;				//!< Layer program LAYERPROG_*
	u8	mode[LAYERS_MAX]; 	//!< mode of layer 0..3 LAYERMODE_* (LAYERMODE_BASE = layer is off or base layer)

	// horizontal timings
	u16	htot;		//!< Total state machine clocks per line
	u16	hfront;		//!< H front porch in state machine clocks (min. 2)
	u16	hsync;		//!< H sync pulse in state machine clocks (min. 4)
	u16	hback;		//!< H back porch in state machine clocks (min. 13)
	float hfreq;	//!< Horizontal frequency in [Hz]

	// vertical timings
	u16	vtot;		//!< Total scanlines (both sub-frames)
	u16	vmax;		//!< Maximal height
	float vfreq;	//!< Vertical frequency in [Hz]

	// subframe 1
	u16	vsync1;		//!< V sync (half-)pulses on subframe 1
	u16	vpost1;		//!< V sync post (half-)pulses on subframe 1
	u16	vback1;		//!< V back porch (after VSYNC, before image) on subframe 1
	u16	vact1;		//!< active visible scanlines, subframe 1
	u16	vfront1;	//!< V front porch (after image, before VSYNC) on subframe 1
	u16	vpre1;		//!< V sync pre (half-)pulses on subframe 1
	u16	vfirst1;	//!< first active scanline, subframe 1

	// subframe 2 (ignored if not interlaced)
	u16	vsync2;		//!< V sync half-pulses on subframe 2
	u16	vpost2;		//!< V sync post half-pulses on subframe 2
	u16	vback2;		//!< V back porch (after VSYNC, before image) on subframe 2
	u16	vact2;		//!< active visible scanlines, subframe 2
	u16	vfront2;	//!< V front porch (after image, before VSYNC) on subframe 2
	u16	vpre2;		//!< V sync pre half-pulses on subframe 2
	u16	vfirst2;	//!< first active scanline, subframe 2

	// name
	const char* name;	//!< Video timing name (VIDEO_NAME_LEN characters + terminating 0)

	// flags
	bool lockfreq;	//!< Lock current frequency, do not change it
	bool dbly;		//!< Double scanlines
	bool inter;		//!< Interlaced (use sub-frames)
	bool psync;		//!< Positive synchronization
	bool odd;		//!< First sub-frame is odd lines 1, 3, 5,... (PAL)
} sVmode;

//! Output device
enum {
	DEV_PAL = 0,	//!< PAL TV
	DEV_NTSC,		//!< NTSC TV
	DEV_VGA,		//!< VGA monitor

	DEV_MAX
};

//! Preset videomode resolution
enum {
	RES_ZX = 0,	//!< 256x192
	RES_CGA,	//!< 320x200
	RES_QVGA,	//!< 320x240
	RES_EGA,	//!< 512x400
	RES_VGA,	//!< 640x480
	RES_SVGA,	//!< 800x600 (not for TV device)
	RES_XGA,	//!< 1024x768 (not for TV device)
	RES_HD,		//!< 1280x960 (not for TV device)

	RES_MAX
};

//! Graphics formats
enum {
	FORM_8BIT = 0,	//!< 8-bit pixel graphics (up to EGA resolution)
	FORM_4BIT,		//!< 4-bit pixel graphics (up to SVGA graphics)
	FORM_MONO,		//!< 1-bit pixel graphics
	FORM_TILE8,		//!< 8x8 tiles
	FORM_TILE12,	//!< 12x12 tiles
	FORM_TILE16,	//!< 16x16 tiles
	FORM_TILE24,	//!< 24x24 tiles
	FORM_TILE32,	//!< 32x32 tiles
	FORM_TILE48,	//!< 48x48 tiles
	FORM_TILE64,	//!< 64x64 tiles
	FORM_MTEXT8,	//!< mono text with font 8x8
	FORM_MTEXT16,	//!< mono text with font 8x16
	FORM_TEXT8,		//!< attribute text with font 8x8
	FORM_TEXT16,	//!< attribute text with font 8x16
	FORM_RLE,		//!< images with RLE compression (on overlapped layer 1)

	FORM_MAX
};

extern sVmode Vmode;	//!< Videomode setup
extern sVgaCfg Cfg;		//!< Required configuration
extern sCanvas Canvas;  //!< Canvas of draw box

//! 16-color palette translation table
extern u16 Pal16Trans[256];

/**
 * @brief Initialize configuration structure to VGA defaults
 * @details The function presets the structure to the default parameters: 640x480 resolution, VGA display, 
 * processor frequency 120 to 270 MHz.
 * @param cfg Configuration to modify
*/
void VgaCfgDef(sVgaCfg* cfg);

/**
 * @brief Debug print videomode setup
 * @param vmode Video mode table
*/
void VgaPrintCfg(const sVmode* vmode);

/**
 * @brief Calculate the structure for setting up the video mode.
 * @details The sVgaCfg structure contains the required properties of the video mode: the display resolution, 
 * the minimum processor frequency and the timing of the sVideo signal, possibly also the required overlay mode. 
 * You can first call the VgaCfgDef function, which presets the structure to the default parameters. The VgaCfg 
 * function prepares the sVmode descriptor structure, which is later passed to the init function. 
 * At this point no operations are taking place only the necessary settings are being calculated. After the calculation, 
 * some items of the sVmode structure can be adjusted. In the library there are global structures Cfg and Vmode that can 
 * be used for the function. The required screen resolution and signal timing are two independent properties. 
 * For timing, you are limited only by the number of video lines of the image, but otherwise you can set any screen resolution 
 * within them. For example, for PAL and NTSC video, you can set a VGA video resolution. To make the program versatile so that 
 * it can be run on both a VGA monitor and a TV, use a VGA resolution of 640x480 or 320x240 (or 512x400 and 256x192, due to RAM 
 * limitations). When changing the display, just select VGA/PAL or NTSC timing, the resolution does not change for the program.
 * @param cfg Source configuration structure
 * @param vmode Destination videomode setup for driver
*/
void VgaCfg(const sVgaCfg* cfg, sVmode* vmode);

/**
 * @brief Simplified initialization of the video mode
 * @details This function incorporates all the video initialization and configuration functions -- this one call initializes the 
 * video mode and starts the library. 
 * It supports only 1 display segment and has a limited repertoire of formats and resolutions, but may be sufficient in some cases. 
 * The function only needs to pass a pointer to the frame buffer, which is a u8 array of sufficient size for the image data. 
 * The function uses the library's default global structures (Cfg, Vmode, Canvas), otherwise the program can use the default global 
 * structures arbitrarily. When using the Video function, the initialization functions are not needed.
 * @param dev Output device
 * @param res Resolution
 * @param form Graphics format
 * @param buf Pointer to frame buffer (must be aligned to 4-bites, use ALIGNED attribute) 
 * @param buf2 Pointer to additional buffer:<br> 
 * <b>FORM_TILE*:</b> Pointer to column of tiles 32x32 in 8-bit graphics<br> 
 * <b>FORM_TEXT:</b> Pointer to font 8x16 or 8x8 (size 4 KB or 2 KB, ALIGNED attribute, should be in RAM) copy font to 4KB or 2 KB RAM buffer with ALIGNED attribute text uses color attributes PC_*<br>
 * <b>FORM_RLE:</b> Pointer to image rows (ALIGNED attribute, should be in RAM)
 */
void Video(u8 dev, u8 res, u8 form, u8* buf, const void* buf2 = FontBoldB8x16);

//!@}

#endif // _VGA_VMODE_H
