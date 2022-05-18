#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>

//Bitmap header
#include "bitmap.h"
//Fonts headers
#include "fonts/Arial_32.h"
#include "fonts/Arial_8.h"
#include "fonts/Arial_Italic_32.h"
#include "fonts/Arial_Italic_8.h"
#include "fonts/Arial_Bold_32.h"
#include "fonts/Arial_Bold_8.h"
#include "fonts/Consolas_32.h"
#include "fonts/Consolas_8.h"
#include "fonts/Consolas_Italic_32.h"
#include "fonts/Consolas_Italic_8.h"
#include "fonts/Consolas_Bold_32.h"
#include "fonts/Consolas_Bold_8.h"
//VGA
#include "stm32_ub_vga_screen.h"

//Error header
#include "error.h"

//Defines
#define BEGGINING_OF_BITMAP 	3	//The first 3 bytes are reserved for Y and X of screen
#define BITMAP_WIDTH_HIGH		2	//The 3rd byte is the Width high
#define BITMAP_WIDTH_LOW		1	//The 2nd byte is the Width Low
#define FONT_TYPES				6	//The font type, from byte 6 is Consolas, else font type is Arial
#define FONT_SIZE				2	//The font size is 2 different sizes
#define BYTE_SIZE				8	//The size of a byte
#define FONT_NUMBER				2	//The amount of fonts, this can be expended.
#define FONT_NAME_SIZE			20	//The Size of fontname.
#define SPACE_BETWEEN_LETTER 	2	//The space between the letter.
#define LETTER_BITS				31	//Letter bits
#define LETTER_WIDTH_BITS		32	//Character bits
#define FONT_SIZE_POSITION		3	//Position of font size in the array for each fonts.

//DEBUGS
//#define DEBUG_FONT_NAME

//Prototypes function
void drawBitmap(int nr, int x_1up, int y_1up);
void drawText(int x, int y, char kleur, char tekst[], char fontname[], char fontgrootte, char fontstyle);
