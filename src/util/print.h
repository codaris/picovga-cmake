/** 
 * @file 
 * @brief Print to attribute text buffer
 * @author Miroslav Nemecek <Panda38@seznam.cz>
 * @see TextGroup
*/

#ifndef _PRINT_H
#define _PRINT_H

/**
 * @addtogroup TextGroup
 * @details The functions for printing text are used to output text to the text frame buffer. Currently supported buffer 
 * formats are GF_ATEXT (text with color attribute) and GF_MTEXT (mono text).
 * @{
*/

// text colors (if using PC CGA colors)
#define PC_BLACK	0
#define PC_BLUE		1
#define PC_GREEN	2
#define PC_CYAN		3
#define PC_RED		4
#define PC_MAGENTA	5
#define PC_BROWN	6
#define PC_LTGRAY	7
#define PC_GRAY		8
#define PC_LTBLUE	9
#define PC_LTGREEN	10
#define PC_LTCYAN	11
#define PC_LTRED	12
#define PC_LTMAGENTA	13
#define PC_YELLOW	14
#define PC_WHITE	15

// compose PC color
#define PC_COLOR(bg,fg) (((bg)<<4)|(fg))
#define PC_FGCOLOR(color) ((color) & 0b1111)  // Added by WV
#define PC_BGCOLOR(color) ((color) >> 4)    // Added by WV

// ASCII characters
#define CHAR_CR	'\r'
#define CHAR_LF	'\n'
#define CHAR_TAB '\t'
#define CHAR_FRAME 16	///< Frame base
#define FRAME_L	B0	    ///< Frame left flag
#define FRAME_U	B1	    ///< Frame up flag
#define FRAME_R B2	    ///< Frame right flag
#define FRAME_D B3	    ///< Frame down flag

#define CHAR_FRAME_FIRST 17     ///< First frame character
#define CHAR_FRAME_LAST 31      ///< Last frame character
#define CHAR_VLINE (CHAR_FRAME|FRAME_U|FRAME_D)     ///< Vertical line
#define CHAR_HLINE (CHAR_FRAME|FRAME_L|FRAME_R)     ///< Horizontal line

// Current print buffer
extern u8* PrintBuf;

// Size of print buffer
extern int PrintBufW, PrintBufH, PrintBufWB;

// Print position
extern int PrintX, PrintY;

// Current print color
extern u8 PrintCol;

/**
 * @brief Setup print service 
 * @details Initialization of the text printing service. The function is passed a pointer to the text frame buffer and 
 * its dimensions. If the line length in bytes is less than twice the width, the mono text format GF_MTEXT is selected, 
 * otherwise the format with the GF_ATEXT attributes is used. This function is automatically called when the video mode 
 * is initialized using the Video() function.
 * @param buf Pointer to buffer
 * @param bufw Buffer width in characters
 * @param bufh Buffer height in characters
 * @param bufwb Buffer width in bytes (if bufwb < 2*bufw, use mono text) 
*/
void PrintSetup(u8* buf, int bufw, int bufh, int bufwb);

/**
 * @brief Clear the text buffer with the currently selected color.
*/
void PrintClear();

/**
 * @brief Move the pointer to the beginning of the first line.
*/
void PrintHome();

/**
 * @brief Set print position
 * @param x Column position
 * @param y Row position
*/
void PrintSetPos(int x, int y);

/**
 * @brief Shift relative print position
 * @param x Add column position
 * @param y Add row position
*/
void PrintAddPos(int x, int y);

/**
 * @brief Set print color (2x4 bits of colors)
 * @param col Color - Use the PC_COLOR macro
*/
void PrintSetCol(u8 col);

/**
 * @brief Print character, not using control characters
 * @param ch Character to print
*/
void PrintChar0(char ch);
 
/**
 * @brief Print character, using control characters CR, LF, TAB
 * @param ch Character to print
*/
void PrintChar(char ch);

/**
 * @brief Print space character 
*/
void PrintSpc();

/**
 * @brief Printing spaces up to the specified position
 * @param pos Position
*/
void PrintSpcTo(int pos);

/**
 * @brief Print repeated character
 * @param ch Character
 * @param num Number of times to repeat
*/
void PrintCharRep(char ch, int num);

/**
 * @brief Print repeated space
 * @param num Number of times to repeat
*/
void PrintSpcRep(int num);

/**
 * @brief Print a string
 * @param text String to print
*/
void PrintText(const char* text);

/**
 * @brief Print horizontal line into screen, using current color
 * @details Horizontal line drawing. Line drawing characters with code 17 to 31 are used for drawing, as overridden in the 
 * PicoVGA library fonts. When drawing, the line is combined with the characters already in the print buffer so that the lines 
 * are properly joined and overlapped. The function does not treat overflows outside the allowed display range.
 * @note Must not stretch outside valid range
 * @param x Column position
 * @param y Row position
 * @param w Width of line
*/
void PrintHLine(int x, int y, int w);

/**
 * @brief Print vertical line into screen, using current color 
 * @details Vertical line drawing. Line drawing characters with code 17 to 31 are used for drawing, as overridden in the 
 * PicoVGA library fonts. When drawing, the line is combined with the characters already in the print buffer so that the lines 
 * are properly joined and overlapped. The function does not treat overflows outside the allowed display range.
 * @note Must not stretch outside valid range
 * @param x Column position
 * @param y Row position
 * @param h Height of line
*/
void PrintVLine(int x, int y, int h);

/**
 * @brief Print frame, using current color
 * @param x Column position
 * @param y Row position
 * @param w Width of line
 * @param h Height of line
*/
void PrintFrame(int x, int y, int w, int h);

/// @}

#endif // _PRINT_H
