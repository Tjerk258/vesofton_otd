
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
#define RADIUS_INCREMENT_CIRCLE 3600

 //Prototypes function
void drawBitmap(int nr, int x_1up, int y_1up);
void drawText(int x, int y, char kleur, char tekst[], char fontname[], char fontgrootte, char fontstyle);

/**
 * @brief this function draws a single line from a to b
 *
 *@details 	This function starts with 5 variables, x and y coordinate for the begin and x and y coordinates for the end.
 *			The last variable as color of the line.
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
 * @param kleur Color of the line
 * @retval None
 * @author Osman Pekcan
 * @note Possible to optimize this function, since there was a finite amount of time this project needed to handed in.
 * @warning It is possible to relocate the derivative calculation but when the x offset is zero, the calculate would have a division by zero.
 *
 */

void myLijntekenaar(uint16_t x_begin, uint16_t y_begin, uint16_t x_eind, uint16_t y_eind,uint8_t kleur);

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
void drawLines( uint16_t x_begin, uint16_t y_begin, uint16_t x_eind, uint16_t y_eind,uint8_t kleur,uint8_t lijn_dikte);

/**
 * @brief This function draws a rectangle either filled or not.
 *
 * @details This function draw either a filled or unfilled rectangle, using filled parameter to decide which one.
 * 			If it filled, its loops from y axis, drawing lines (using mylijntekenaar) from x axis.
 * 			If it unfilled draws four lines of the unfilled rectangle
 *
 *@param x_pos,y_pos Upper left position of the rectangle.
 *@param length,width Length and width of the rectangle.
 *@param kleur Color of rectangle.
 *@param filled Parameter that determines whether the rectangle is filled or not
 *@retval None
 *
 *@author Osman Pekcan
 */
void drawRect(uint16_t x_pos,uint16_t y_pos,uint16_t length,uint16_t width,uint8_t kleur,uint8_t filled);

/**
 * @brief This function draws a circle
 *
 * @details By using **elementary** mathematics the function draw a circle.
 * 			The for loop draws points of the circle until it drew the whole circle.
 * 			The for loop goes through every angle between 0 - 2 PI radius
 *
 *@param x_pos,y_pos These are the x and y coordinates of the middle of the circle.
 *@param radius This is the radius of the circle.
 *@param kleur This is the color of the circle
 *<a href="https://opentextbc.ca/precalculusopenstax/chapter/unit-circle-sine-and-cosine-functions/">mathematic proof</a>  
 *[mathematic proof](https://opentextbc.ca/precalculusopenstax/chapter/unit-circle-sine-and-cosine-functions/)
 *@retval None
 *
 *@author Osman Pekcan
 */
void drawCircle(uint16_t x_pos, uint16_t y_pos,uint8_t radius,uint8_t kleur);
/**
 * @brief This functions draw a figure with X amount of points
 *
 * @details With the function mylijntekenaar,this function draws multiple line that are chained to each other.
 * 			With va_list the argument after nr_pointsgiven are saved in a list.
 * 			Using va_arg the argument are put into two array.figure_ram_x and figure_ram_y.
 * 			with arithmetic code the argument that represent x coordinate are put into figure_ram_x.
 * 			likewise for the y coordinates.
 * 			with these to arrays the function can draw its figure with a for loop.
 * @param kleur This parameter is for color of the lines
 * @param nr_pointgiven Locked the number of points
 *@retval None
 *
 * @author Osman Pekcan
 */
void drawFigure(uint8_t kleur,uint8_t nr_pointsgiven,...);

