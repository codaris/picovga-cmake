#include "main.h"

// format: 8-bit pixel graphics
// image width: 8 pixels
// image height: 136 lines
// image pitch: 8 bytes
const u8 TilesImg[1088] __attribute__ ((aligned(4))) = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x10, 0x10, 0x10, 0x5D, 0x10, 0x10, 0x10, 0x5D, 0x10, 0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
	0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x5D, 0x10, 0x10, 0x10, 
	0x10, 0x5D, 0x10, 0x10, 0x10, 0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
	0x10, 0x10, 0x5D, 0x10, 0x5D, 0x10, 0x10, 0x5D, 0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
	0x10, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x5D, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 
	0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 
	0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 
	0xFD, 0xFD, 0x00, 0x00, 0x00, 0x00, 0xFD, 0xFD, 0x5D, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x10, 
	0x10, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x5D, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 
	0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x90, 0x90, 0xFD, 0xFD, 0x90, 0x90, 0xFD, 
	0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 
	0xFD, 0xFD, 0x00, 0x00, 0x00, 0x00, 0xFD, 0xFD, 0x5D, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x10, 
	0x10, 0x10, 0x10, 0x5D, 0xFD, 0xFD, 0xFD, 0xFD, 0x10, 0x5D, 0x10, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 
	0x5D, 0x10, 0x10, 0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0x10, 0x10, 0x10, 0xFD, 0x00, 0xFD, 0xFD, 0xFD, 
	0x10, 0x5D, 0x10, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x10, 0x10, 0x10, 0xFD, 0x00, 0xFD, 0xFD, 0xFD, 
	0x10, 0x10, 0x5D, 0xFD, 0xFD, 0x00, 0x00, 0x00, 0x5D, 0x10, 0x10, 0x10, 0xFD, 0xFD, 0xFD, 0xFD, 
	0xFD, 0xFD, 0x10, 0x5D, 0x10, 0x10, 0x10, 0x5D, 0xFD, 0xFD, 0xFD, 0x10, 0x10, 0x10, 0x10, 0x10, 
	0xFD, 0x00, 0xFD, 0x10, 0x10, 0x10, 0x5D, 0x10, 0xFD, 0x00, 0xFD, 0x10, 0x5D, 0x10, 0x10, 0x10, 
	0xFD, 0xFD, 0xFD, 0x10, 0x10, 0x5D, 0x10, 0x10, 0xFD, 0x00, 0xFD, 0x10, 0x10, 0x10, 0x10, 0x10, 
	0x00, 0xFD, 0xFD, 0x10, 0x5D, 0x10, 0x10, 0x5D, 0xFD, 0xFD, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
	0x10, 0x10, 0x10, 0x5D, 0x10, 0x10, 0xFD, 0xFD, 0x10, 0x5D, 0x10, 0x10, 0x10, 0xFD, 0xFD, 0xFD, 
	0x5D, 0x10, 0x10, 0x10, 0x10, 0xFD, 0x00, 0xFD, 0x10, 0x10, 0x10, 0x10, 0x5D, 0xFD, 0x00, 0xFD, 
	0x10, 0x5D, 0x10, 0x10, 0x10, 0xFD, 0xFD, 0xFD, 0x10, 0x10, 0x10, 0x10, 0x10, 0xFD, 0x00, 0xFD, 
	0x10, 0x10, 0x5D, 0x10, 0x5D, 0xFD, 0xFD, 0x00, 0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0xFD, 0xFD, 
	0xFD, 0xFD, 0xFD, 0xFD, 0x10, 0x10, 0x10, 0x5D, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x10, 0x10, 0x10, 
	0xFD, 0xFD, 0xFD, 0x00, 0xFD, 0x10, 0x5D, 0x10, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 0x10, 0x10, 0x10, 
	0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x5D, 0x10, 0x10, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 0x10, 0x10, 0x10, 
	0x00, 0x00, 0x00, 0xFD, 0xFD, 0x10, 0x10, 0x5D, 0xFD, 0xFD, 0xFD, 0xFD, 0x10, 0x10, 0x10, 0x10, 
	0x10, 0x10, 0x10, 0x5D, 0x10, 0x10, 0x10, 0x5D, 0x10, 0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
	0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x5D, 0x10, 0x10, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x10, 
	0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 
	0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 
	0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0x00, 0x00, 0x00, 0x00, 0xFD, 0xFD, 
	0x5D, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x10, 0x10, 0x10, 0x10, 0x10, 0x5D, 0x10, 0x10, 0x10, 
	0x10, 0x5D, 0x10, 0x10, 0x10, 0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
	0x10, 0x10, 0x5D, 0x10, 0x5D, 0x10, 0x10, 0x5D, 0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
	0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 
	0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0x00, 0x00, 0x00, 0x00, 0xFD, 0xFD, 
	0x10, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
	0x10, 0x10, 0x5D, 0x10, 0x5D, 0x10, 0x10, 0x5D, 0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
	0x10, 0x10, 0x10, 0x5D, 0x10, 0x10, 0x10, 0x5D, 0x10, 0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
	0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x5D, 0x10, 0x10, 0x10, 
	0x10, 0x5D, 0x10, 0x10, 0x10, 0x5D, 0x10, 0x10, 0x10, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x10, 
	0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 0xFD, 0xFD, 0xFD, 0x00, 0xFD, 
	0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x90, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0xFD, 0xFD, 0x02, 
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x90, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
};