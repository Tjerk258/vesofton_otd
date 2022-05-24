
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
  
//VGA
#include "stm32_ub_vga_screen.h"

//DEBUGS
//#define DEBUG_FONT_NAME
//#define DEBUG_LINE_OFFSET
//#define DEBUG_LINE_DERIVATIVE
//#define DEBUG_LINE_VAR
//#define DEBUG_FIGURE_COR
//#define DEBUG_CIRCLE_PLAATS
//#define DEBUG_RECT_BOUNDS
//#define DEBUG_LIJN_DIKTE
//#define DEBUG_BITMAP_SIZE

//Defines
#define BEGGINING_OF_BITMAP 	3	//The first 3 bytes are reserved for Y and X of screen
#define BITMAP_WIDTH_HIGH		2	//The 3rd byte is the Width high
#define BITMAP_WIDTH_LOW		1	//The 2nd byte is the Width Low
#define BITMAP_LENGTH			0	//The first byte is the length of the bitmap.
#define FONT_TYPES				6	//The font type, from byte 6 is Consolas, else font type is Arial
#define BYTE_SIZE				8	//The size of a byte
#define FONT_NUMBER				2	//The amount of fonts, this can be expended.
#define FONT_NAME_SIZE			20	//The Size of fontname.
#define FONT_SIZE				1	//Size of font, 0=8 and 1=32
#define FONT_STYLE				2	//Style of font, 0=standard, 1=Italic and 2=Bold
#define SPACE_BETWEEN_LETTER 	2	//The space between the letter.
#define LETTER_BITS				31	//Letter bits
#define LETTER_WIDTH_BITS		32	//Character bits
#define FONT_SIZE_POSITION		3	//Position of font size in the array for each fonts.
#define COLOURMAX				255	//colour between 0 and 255
#define COLOURMIN				0	//Min colour digit.
#define LINE_WIDTH				10	//								<----*
#define X_BEGIN					0
#define Y_BEGIN					0
#define FIGURE_POINTS			5
#define RADIUS_INCREMENT_CIRCLE 3600	//Radius of circle


/**
 * @brief this function shows a graphics image file (bitmaps) on VGA display.
 *
 * @details Bitmap, method by which a display space (such as a graphics image file) is defined, including the colour of each of its pixels (or bits).
 *			Is an array of binary data representing the values of pixels in an image or display.
 *			This function has 3 variables, the number of the bitmap and the position of bitmap.
 *			Bitmap has 6 icons; smile, angry and the four arrows.
 *			The user can choose between smile=0, angry=1, left=2, up=3, right=4, right=5.
 *			Add more bitmap guide:
 *			Step 1: Add bitmap array into bitmap.h
 *			Step 2: Add 3 bytes at the position 0, 1 and 2 of array:
*				2a: Position 0   is the Y boundary in HEX.
 *				2b:	Position 1&2 are the X boundary in HEX.
 *			Step 3: At the bottom of bitmap.h add the names of bitmaps into the array list.
 *
 * @param nr is the bitmap number to display.
 * @param x_1up and y_1up is the left upper position of the bitmap
 * @retval 0
 * @author Djalil & Tjerk
 * @note Bitmap size must be smaller or equal to VGA resolution.
 * @warning
 *
 */

int drawBitmap(int nr, uint8_t x_1up, uint8_t y_1up);

/**
 * @brief 	This function prints the text on the screen.
 *
 * @details This function prints the text on the screen.
 * 			The user can choose between Arial= 0 en Consolas=1.
 * 			Each fonts have 3 styles: Standard, Italic and Bold
 * 			Each fonts have 2 sizes:  8, 32
 * 			Fontstyle Standard=0, Italic=1 and Bold=2.
 * 			Fontsize 8=0, 32=1.
 * 			Add more fonts:
 * 			Step 1: Import the header file into fonts folder.
 * 			Step 2: Add all the fonts into **fonts[].
 * 			Step 3: Add fontnames into font_name[][].
 * 			Step 4: Change the Define FONT_NUMBER
 *
 * @param x,y Is the position of the starting point of the first letter.
 * @param colour Is the fonts colour.
 * @param tekst[] Is an array with text.
 * @param fontname is the fonts: Arial and Consolas.
 * @param fontsize is the size of the font. The size can be chosen from 8 or 32. 0=8 and 1=32.
 * @param frontstyle is the style of fonts, this can be chosen of Italic, Bold.
 * @author Djalil & Tjerk
 * @retval
 * @note
 *
 * @warning
 */

int drawText(int x, int y, uint8_t kleur, char tekst[], char fontname[], uint8_t fontgrootte, uint8_t fontstyle);

/**
 * @brief this function draws a single line from a to b
 *
 *@details 	This function starts with 5 variables, x and y coordinate for the begin and x and y coordinates for the end.
 *			The last variable as colour of the line.
 *			The function first calculates the offset of both x and y coordinates.
 *			When either offsets is equal to zero,the line becomes straight.
 *			If y offset is zero the function draws horizontal line, else a vertical line.
 *			In the situation that neither offset are zero,the function calculates the derivative of the line.
 *			The derivative of the line determines the agle that the line has.
 *			A derivative value lower than one has a small angle.
 *			If the angle is *small* (derivative<1) the y coordinates is calculated with the derivative.
 * 			If the angle is *big* (derivative>1) it is the inverse of the calculation of the smaller angle.
 * 			After the function looks whether the derivative is higher than one,the function looks if the derivative is positive or negative.
 * 			This determines if some parameter is positive or negative.
 * 			Lastly the function looks at orientation of the line with respect to the x axis, which decides which parameter is the start point and end point of the calculation.
 *
 *
 * @param x_begin,y_begin Coordinates where the line starts.
 * @param x_eind,y_eind Coordinates where the line ends.
 * @param kleur colour of the line
 * @retval None
 * @author Osman Pekcan
 * @note Possible to optimize this function, since there was a finite amount of time this project needed to handed in.
 * @warning It is possible to relocate the derivative calculation but when the x offset is zero, the calculate would have a division by zero.
 *
 */

int myLijntekenaar(uint16_t x_begin, uint16_t y_begin, uint16_t x_eind, uint16_t y_eind,uint8_t kleur);

/**
 * @brief This function draws multiple lines using mylijntekenaar function.
 *
 * @details By repeating the function mylijntekenaar, this draws multiple lines.
 * 			To do this it checks the parameter which concludes the width of the sum of lines.
 * 			If it is one, the function just calls the function mylijntekenaar once.
 * 			Else draws the lines around the middle line(original x and y positions).
 * 			For the function to know whether to draw extra line in the x axis or y axis it looks at the derivative.
 * 			If the derivative is higher than one its draw from the x axis, else its draws from the y axis
 *
 *@param lijn_dikte The variable that dictate how big the line width is.
 *@see myLijntekenaar(uint16_t x_begin, uint16_t y_begin, uint16_t x_eind, uint16_t y_eind,uint8_t kleur)
 *@retval None
 *@author Osman Pekcan
 */
int drawLines( uint16_t x_begin, uint16_t y_begin, uint16_t x_eind, uint16_t y_eind,uint8_t kleur,uint8_t lijn_dikte);

/**
 * @brief This function draws a rectangle either filled or not.
 *
 * @details This function draw either a filled or unfilled rectangle, using filled parameter to decide which one.
 * 			If it filled, its loops from y axis, drawing lines (using mylijntekenaar) from x axis.
 * 			If it unfilled draws four lines of the unfilled rectangle
 *
 *@param x_pos,y_pos Upper left position of the rectangle.
 *@param length,width Length and width of the rectangle.
 *@param kleur colour of rectangle.
 *@param filled Parameter that determines whether the rectangle is filled or not
 *@retval None
 *
 *@author Osman Pekcan
 */
int drawRect(uint16_t x_pos,uint16_t y_pos,uint16_t length,uint16_t width,uint8_t kleur,uint8_t filled);

/**
 * @brief This function draws a circle
 *
 * @details By using **elementary** mathematics the function draw a circle.
 * 			The for loop draws points of the circle until it drew the whole circle.
 * 			The for loop goes through every angle between 0 - 2 PI radius
 *
 *@param x_pos,y_pos These are the x and y coordinates of the middle of the circle.
 *@param radius This is the radius of the circle.
 *@param kleur This is the colour of the circle
 *<a href="https://opentextbc.ca/precalculusopenstax/chapter/unit-circle-sine-and-cosine-functions/">mathematic proof</a>
 *@retval None
 *
 *@author Osman Pekcan
 */
int drawCircle(uint16_t x_pos, uint16_t y_pos,uint8_t radius,uint8_t kleur);
/**
 * @brief This functions draw a figure with X amount of points
 *
 * @details With the function mylijntekenaar,this function draws multiple line that are chained to each other.
 * 			With va_list the argument after nr_pointsgiven are saved in a list.
 * 			Using va_arg the argument are put into two array.figure_ram_x and figure_ram_y.
 * 			with arithmetic code the argument that represent x coordinate are put into figure_ram_x.
 * 			likewise for the y coordinates.
 * 			with these to arrays the function can draw its figure with a for loop.
 * @param kleur This parameter is for colour of the lines
 * @param nr_pointgiven Locked the number of points
 *@retval None
 *
 * @author Osman Pekcan
 */
int drawFigure(uint8_t kleur,uint8_t nr_pointsgiven,...);

