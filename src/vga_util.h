/** 
 * @file 
 * @brief VGA utilities
 * @author Miroslav Nemecek <Panda38@seznam.cz>
 * @see VideoModeGroup
*/

#ifndef _VGA_UTIL_H
#define _VGA_UTIL_H

/**
 * @addtogroup UtilsGroup
 * @brief Utility functions
 * @{
*/

/**
 * @brief Convert image from 16-color to 8x8 attribute format
 * @param dst   Destination image
 * @param attr  Destination attribute data
 * @param src   Source image
 * @param w     Image width
 * @param h     Image height
 * @param pal   Palette
*/
void Attr8Conv(u8* dst, u8* attr, const u8* src, int w, int h, const u8* pal);

/** 
 * @brief Convert image from 4-color to 2-plane format (width must be multiply of 8)
 * @param plane0 First plane destination
 * @param plane1 Second plane destionation
 * @param src Soure image
 * @param w Image width
 * @param h Image height
*/
void Plane2Conv(u8* plane0, u8* plane1, const u8* src, int w, int h);

/** 
 * @brief Invert image
 * @param dst Image data
 * @param num Length of image in bytes
*/
void ImgInvert(u8* dst, int num);

/**
 * @brief Decode unsigned number into ASCIIZ text buffer
 * @param buf Destination buffer
 * @param num Number to decode
 * @returns Number of digits
*/
int DecUNum(char* buf, u32 num);

/**
 * @brief Decode signed number into ASCIIZ text buffer
 * @param buf Destination buffer
 * @param num Number to decode
 * @returns Number of digits
*/
int DecNum(char* buf, s32 num);

/**
 * @brief Prepare image with white key transparency (copy and increment pixels)
 * @param dst Destination image
 * @param src Source image
 * @param num Number of bytes to copy
*/
void CopyWhiteImg(u8* dst, const u8* src, int num);

/// @}

#endif // _VGA_UTIL_H
