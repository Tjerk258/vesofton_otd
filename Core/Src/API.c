
/**
  ******************************************************************************
  * @file           : API.c
  * @brief          : Library for Graphics.
  ******************************************************************************
  */

#include "API.h"
#include "front_layer.h"

#include "error.h"
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

/**
 *@brief Weak decleared Draw pixel function for if the user wants to implement his own display interface.
 *
 *@details  By declaring this function in the user his own code the user can implement his own display interface code and still use this graphics library.
 *
 *
 *@param x x coordinate of the pixel
 *@param y y coordinate of the pixel
 *@param color color of the pixel
 *@author Tjerk ten Dam
 * */
__weak void drawPixel(uint16_t xp, uint16_t yp, uint8_t colour)
{
	UB_VGA_SetPixel(xp, yp, colour);
}

/**
 * @brief this function draws a single line from a to b
 *
 *@details 	This function starts with 5 variables, x and y coordinate for the begin and x and y coordinates for the end.
 *			The last variable as colour of the line.
 *			The function first calculates the offset of both x and y coordinates.
 *			When either offsets is equal to zero,the line becomes straight.
 *			If y offset is zero the function draws horizontal line, else a vertical line.
 *			In the situation that neither offset are zero,the function calculates the derivative of the line.
 *			The derivative of the line determines the angle that the line has.
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
 * @param colour colour of the line
 * @retval Error
 * @author Osman Pekcan
 * @note Possible to optimize this function, since there was a finite amount of time this project needed to handed in.
 * @warning It is possible to relocate the derivative calculation but when the x offset is zero, the calculate would have a division by zero.
 *
 */
int myLijntekenaar(uint16_t x_begin, uint16_t y_begin, uint16_t x_eind, uint16_t y_eind,uint8_t colour)
{
	if((x_begin < 0) || (y_begin < 0) || (x_eind > VGA_DISPLAY_X) || (y_eind > VGA_DISPLAY_Y))
	{
		softonErrorHandler(ERROR_LINE_OUT_OF_RANGE);
		return 9;
	}
	if (colour > COLOURMAX || colour < COLOURMIN)
	{
		softonErrorHandler(ERROR_LINE_COLOUR_OUT_OF_RANGE);
		return 11;
	}
	uint16_t i=0;
	float derivative = 0.0; // Float since the formula creates decimal numbers that are needed to calculate line_var
	int16_t x_offset=0, y_offset=0;
	uint16_t start_point = 0, end_point = 0;
	uint16_t line_var = 0; // The variable which is used to calculated increments of either x or y coordinates

	x_offset = x_begin - x_eind;// Offset is used to determine if the line is straight
	y_offset = y_begin - y_eind; // Offset is also used to calculated the derivative.

#ifdef DEBUG_OFFSET
	printf("Here value of x offset \t %d \n", x_offset);
	printf("Here value of y offset \t %d \n", y_offset);
#endif

	drawPixel(x_begin, y_begin, colour); // The arithmetic of the function something does not write the start point or end point.
	drawPixel(x_eind, y_eind, colour); // ""

	if (x_offset == 0 || y_offset == 0) // If the line is a line either one of the offset is zero.
	{
		if (x_offset == 0) // If the line is horizontal the offset from the x axis is zero.
		{
			if (y_offset > 0) // The orientation of the line determines where the code needs to start.
			{
				start_point = y_eind;
				end_point = y_begin;
			}
			else
			{
				start_point = y_begin;
				end_point = y_eind;
			}
			for (i = start_point; i < end_point + 1; i++)
			{
				drawPixel(x_begin, (start_point)+(i-start_point), colour);
			}
		}
		if (y_offset == 0) // If the line is vertical the offset from the y axis is zero
		{
			if (x_offset > 0)
			{
				start_point = x_eind;
				end_point = x_begin;
			}
			else
			{
				start_point = x_begin;
				end_point = x_eind;
			}
			for (i = start_point; i < end_point + 1; i++)
			{
				drawPixel((start_point)+(i - start_point), y_begin, colour);
			}
		}
	}
	else
	{
		derivative = (float)y_offset / (float)x_offset; // Calculate the derivative.
#ifdef DEBUG_DERIVATIVE
		printf("Here value of the derivative \t %.5f \n", derivative);
#endif
		if (fabs(derivative) >= 1) // Determines whether x or y value changes with the derivative.
		{							// Also the line_var calculation changes
			if (derivative > 0) // The polarity of the derivative will change the polarity parameter in line_var.
			{
				if (x_offset < 0) // The orientation of the line decides which parameter of the function is the start and end point of the loop.
				{
					start_point = y_begin;
					end_point = y_eind;
				}
				else
				{
					start_point = y_eind;
					end_point = y_begin;
				}
				for (i= start_point; i< end_point;i++)
				{
					line_var = round((1/derivative)*(i-y_begin))+ x_begin;
#ifdef DEBUG_LINE_VAR
				printf("lijn variable : \t %d\n", line_var);
#endif
					drawPixel(line_var, y_begin + (i-y_begin), colour);
				}
			}
			else
			{
				if (x_offset < 0)
				{
					start_point = y_eind;
					end_point = y_begin;
				}
				else
				{
					start_point = y_begin;
					end_point = y_eind;
				}
				for (i = start_point; i < end_point; i++)
				{
					line_var = x_begin - round((1/fabs(derivative)) * (i - y_begin));
#ifdef DEBUG_LINE_VAR
					printf("lijn variable : \t %d\n", line_var);
#endif
					drawPixel(line_var, y_begin + (i-y_begin), colour);
				}
			}
		}
		else
		{
			if (derivative > 0)
			{
				if (x_offset < 0)
				{
					start_point = x_begin;
					end_point = x_eind;
				}
				else
				{
					start_point = x_eind;
					end_point = x_begin;
				}
				for (i = start_point; i < end_point; i++)
				{
					line_var = round(derivative * (i - x_begin)) + y_begin;
#ifdef DEBUG_LINE_VAR
					printf("lijn variable : \t %d\n", line_var);
#endif
					drawPixel(x_begin+(i-x_begin), line_var, colour);
				}
			}
			else
			{
				if (x_offset < 0)
				{
					start_point = x_begin;
					end_point = x_eind;
				}
				else
				{
					start_point = x_eind;
					end_point = x_begin;
				}
				for (i = start_point; i < end_point; i++)
				{
					line_var = y_begin + round(fabs(derivative)*(i-x_eind));
#ifdef DEBUG_LINE_VAR
					printf("lijn variable : \t %d\n", line_var);
#endif
					drawPixel(x_eind-(i-x_begin), line_var, colour);
				}
			}
		}
	}
	return 0;
}

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
 *@param mid_lijn If mid_lijn is equal to one,the function draws a black line with the original coordinates.
 *@see myLijntekenaar()
 *@retval Error
 *@author Osman Pekcan
 */
int drawLines(uint16_t x_begin, uint16_t y_begin, uint16_t x_eind, uint16_t y_eind, uint8_t colour, uint8_t lijn_dikte, uint8_t mid_lijn)
{
	uint8_t i = 0; uint8_t lijnwaarde = 0; float derivative = 0.0;
	lijnwaarde = lijn_dikte / 2; // Since the function wants to put original x and y coordinates as the middle line.
	derivative = (float)(y_begin - y_eind) / (float)(x_begin - x_eind); // Needed to know whether the line multiplication is in x or y axis.
#ifdef DEBUG_LIJN_DIKTE
		printf("waarde lijn dikte is %d\n", lijn_dikte);
		printf("waarde lijn waarde is %d\n", lijnwaarde);
#endif
	if(lijn_dikte==1) myLijntekenaar(x_begin, y_begin, x_eind, y_eind, colour);// If line width is just one, the function does not need to loop the line function.
	else
	{
		if (fabs(derivative) < 1)
		{
			if (((x_begin+lijn_dikte) > VGA_DISPLAY_X) || ((x_begin-lijn_dikte) < X_BEGIN))
			{
				softonErrorHandler(ERROR_LINE_WIDTH_OUT_OF_RANGE);
				return 12;
			}
		}
		else
		{
			if (((y_begin-lijnwaarde) > VGA_DISPLAY_Y) || ((y_begin-lijnwaarde) < Y_BEGIN))
				{
					softonErrorHandler(ERROR_LINE_WIDTH_OUT_OF_RANGE);
					return 12;
				}
		}
			for (i = 0; i < lijn_dikte; i++)
			{ // The derivative defines whether the line multiplication is in x or y axis.
				if (fabs(derivative) > 1) myLijntekenaar(x_begin + (-lijnwaarde + i), y_begin, x_eind + (-lijnwaarde + i), y_eind,colour);
				else myLijntekenaar(x_begin, y_begin + (-lijnwaarde + i), x_eind, y_eind + (-lijnwaarde + i),colour);
			}
		if(mid_lijn==1) myLijntekenaar(x_begin, y_begin, x_eind, y_eind,VGA_COL_BLACK); // if the user wants a new line in the middle write new line
	}
	return 0;
}

/**
 * @brief This function draws a rectangle either filled or not.
 *
 * @details This function draw either a filled or unfilled rectangle, using filled parameter to decide which one.
 * 			If it filled, its loops from y axis, drawing lines (using mylijntekenaar) from x axis.
 * 			If it unfilled draws four lines of the unfilled rectangle
 *
 *@param x_pos,y_pos Upper left position of the rectangle.
 *@param length,width Length and width of the rectangle.
 *@param colour colour of rectangle.
 *@param filled Parameter that determines whether the rectangle is filled or not
 *@param rectborder Parameter that determines if the function draws a border around the filled rectangle.
 *@param border_colour The color value of the border.
 *@retval Error
 *
 *@author Osman Pekcan
 */
int drawRect(uint16_t x_pos, uint16_t y_pos, uint16_t length, uint16_t width, uint8_t colour, uint8_t filled,uint8_t rectborder,uint8_t border_colour)
{
	if(((x_pos+length) > VGA_DISPLAY_X) || ((y_pos+width) > VGA_DISPLAY_Y) || ((x_pos+length) < X_BEGIN) || ((y_pos+width) < Y_BEGIN))
	{
		softonErrorHandler(ERROR_RECT_OUT_OF_RANGE);
		return 13;
	}
	if (filled > 1 || filled < 0)
	{
		softonErrorHandler(ERROR_FILLED_OUT_OF_RANGE);
		return 15;
	}
	if (colour > COLOURMAX || colour < COLOURMIN || border_colour > COLOURMAX || border_colour < COLOURMIN)
	{
		softonErrorHandler(ERROR_FONT_COLOUR_OUT_OF_RANGE);
		return 4;
	}
	uint16_t i = 0;
	if(filled == 0)
	{
		for (i = y_pos; i < width +y_pos; i++) // Loops around the y axis
			myLijntekenaar(x_pos, i, x_pos + length-1, i, colour); // Draws around the x axis
	}
	if (rectborder == 1 && filled ==0 )
	{
		for (i = y_pos; i < width +y_pos; i++) // Loops around the y axis
			myLijntekenaar(x_pos, i, x_pos + length-1, i, colour); // Draws around the x axis
		for (i = 0; i <= 1; i++)
		{
			myLijntekenaar(x_pos, y_pos+(width-1)*i, x_pos + length-1, y_pos+(width-1)*i,border_colour); // Draws a horizontal line.
			myLijntekenaar(x_pos + (length -1) * i, y_pos, x_pos + (length-1 ) * i,y_pos+width-1,border_colour); //Draws a Vertical line.
		}
	}
	else
	{
		for (i = 0; i <= 1; i++)
		{
			myLijntekenaar(x_pos, y_pos+(width-1)*i, x_pos + length-1, y_pos+(width-1)*i, colour); // Draws a horizontal line.
			myLijntekenaar(x_pos + (length -1) * i, y_pos, x_pos + (length-1 ) * i,y_pos+width-1, colour); //Draws a Vertical line.
		}
	}

	return 0;
}

/**
 * @brief This function draws a circle
 *
 * @details By using **elementary** mathematics the function draw a circle.
 * 			The for loop draws points of the circle until it drew the whole circle.
 * 			The for loop goes through every angle between 0 - 2 PI radius
 *
 *@param x_pos,y_pos These are the x and y coordinates of the middle of the circle.
 *@param radius This is the radius of the circle.
 *@param colour This is the colour of the circle.
 *@param lradius This is the lower boundary of radius
 *
 *<a href="https://opentextbc.ca/precalculusopenstax/chapter/unit-circle-sine-and-cosine-functions/">mathematic proof</a>
 *
 *@retval Error
 *
 *@author Osman Pekcan
 */
int drawCircle(uint16_t x_pos, uint16_t y_pos, uint8_t radius, uint8_t colour,uint8_t lradius)
{
	uint16_t i=0; // Float because it hold division of PI which are decimal numbers.
	uint8_t j=0;
	int32_t plaats_x = 0, plaats_y = 0;
	if((x_pos-radius < 0) || (y_pos-radius < 0) || (x_pos+radius > VGA_DISPLAY_X) ||  (y_pos+radius > VGA_DISPLAY_Y))
	{
		softonErrorHandler(ERROR_CIRCLE_OUT_OF_RANGE);
		return 17;
	}
	if (colour > COLOURMAX || colour < COLOURMIN)
	{
		softonErrorHandler(ERROR_FONT_COLOUR_OUT_OF_RANGE);
		return 4;
	}
	for (i = 0; i < 2*M_PI*RADIUS_INCREMENT_CIRCLE; i += M_PI)
	{   // Needs an addition because the original formula makes a circle start at point (0,0)
		for(j=lradius;j<=radius;j++) // lower boundarie of the radius
		{
			plaats_x = x_pos+round(j * cos((float)i/RADIUS_INCREMENT_CIRCLE)); // X = r*cosine(θ)
			plaats_y = y_pos+round(j * sin((float)i/RADIUS_INCREMENT_CIRCLE));  // Y = r*sine(θ)
			drawPixel(plaats_x, plaats_y, colour);
		}
#ifdef DEBUG_CIRCLE_PLAATS
		if(i=M_PI) printf("plaats x is \t %d \n plaats y is \t %d",plaats_x, plaats_y);
#endif
	}
	return 0;
}
/**
 * @brief This functions draw a figure with X amount of points
 *
 * @details With the function mylijntekenaar,this function draws multiple line that are chained to each other.
 * 			With va_list the argument after nr_pointsgiven are saved in a list.
 * 			Using va_arg the argument are put into two array.figure_ram_x and figure_ram_y.
 * 			with arithmetic code the argument that represent x coordinate are put into figure_ram_x.
 * 			likewise for the y coordinates.
 * 			with these to arrays the function can draw its figure with a for loop.
 * @param colour This parameter is for colour of the lines.
 * @param lijn_dikte The variable that dictate how big the line width is.
 * @param nr_pointgiven Locked the number of points
 *@retval Error
 *
 * @author Osman Pekcan
 */
int drawFigure(uint8_t colour, uint8_t lijn_dikte, uint8_t nr_pointsgiven,...)
{
	if (colour > COLOURMAX || colour < COLOURMIN)
	{
		softonErrorHandler(ERROR_FIGURE_COLOUR_OUT_OF_RANGE);
		return 18;
	}
	uint8_t i = 0;
	int figure_ram_x[nr_pointsgiven]; // Array where the loop can easily find the x coordinates
	int figure_ram_y[nr_pointsgiven]; // Array where the loop can easily find the y coordinates
	va_list argumenten;

	memset(figure_ram_x, 0, nr_pointsgiven+1); // Filled array with 0
	memset(figure_ram_y, 0, nr_pointsgiven+1);

	va_start (argumenten, nr_pointsgiven); // All arguments after nr_pointsgiven are saved in va_list argumenten.
	for (i = 0; i < nr_pointsgiven*2; i++)
	{
		if (i % 2 != 0) figure_ram_y[(i / 2)] = va_arg(argumenten, int); // Every odd number of coordinate arguments are saved in the y array
		else figure_ram_x[(i / 2)] = va_arg(argumenten, int); // The even number of arguments of coordinate are saved to x array
	}
	va_end(argumenten); // To clean up va_list argumenten.
#ifdef DEBUG_FIGURE_COR
	for (i = 0; i < nr_pointsgiven; i++)
	{
		printf("X \t %d ", figure_ram_x[i]);
		puts("");
	}
	for (i = 0; i < nr_pointsgiven; i++)
	{
		printf(" Y \t %d", figure_ram_y[i]);
		puts("");
	}
#endif
	for (i = 0; i < nr_pointsgiven-1; i++)
		drawLines(figure_ram_x[i], figure_ram_y[i], figure_ram_x[i+1], figure_ram_y[i+1], colour,lijn_dikte,0); // Draws a line with coordinates from the array's
	return 0;
}

/**
 *@brief Draw bitmap function, this function draws the bitmap; smiley, angry and the four arrows on the screen.
 *
 *@details  Bitmap has 6 icons; smiley, angry and the four arrows.
 *			smiley_map=0, angry_map=1, Arrow left=2, Arrow up=
 *			The user can choose between smiley=0, angry=1, left=2, up=3, right=4, right=5.
 *			Add more bitmapguide:
 *			Step 1: Add bitmap array into bitmap.h
 *			Step 2: At the buttom of bitmap.h change the array and add the name of bitmap.
 *
 *
 *@param nr is the bitmap number to draw.
 *@param x_1up and y_1up is the position of the bitmap
 *@retval Error
 *@author Djalil & Tjerk
 * */
int drawBitmap(int nr, uint8_t x_1up, uint8_t y_1up)
{

	int i, j, sizebitmaps = 0;
	const uint8_t *bitmap = bitmaps[nr];
	uint16_t width = (uint16_t)(bitmap[BITMAP_WIDTH_HIGH] | (bitmap[BITMAP_WIDTH_LOW]<<8)); //Shift 8 bits is needed to calculate the the width of bitmaps.
	uint8_t length = (uint8_t)(bitmap[BITMAP_LENGTH]);

	sizebitmaps = sizeof(bitmaps) / sizeof(bitmaps[0]);

	if (nr > sizebitmaps || nr < 0)
	{
		softonErrorHandler(ERROR_BITMAP_NOT_FOUND);
		return 1;
	}
#ifdef DEBUG_BITMAP_SIZE
	printf("%d \t", sizebitmaps);
	printf("The width of bitmap is: \t %d\n", (uint16_t)width);
	printf("The length of bitmap is: \t %d\n", (uint8_t)length);
#endif
	if ((x_1up < X_BEGIN) || (y_1up < Y_BEGIN) || (y_1up+length > VGA_DISPLAY_Y) || (x_1up+width > VGA_DISPLAY_X))
	{
		softonErrorHandler(ERROR_BITMAP_POSITION_OUT_OF_RANGE);
		return 3;
	}
	if ((x_1up > VGA_DISPLAY_X) || (x_1up < 0))
	{
		softonErrorHandler(ERROR_BITMAP_OUT_OF_RANGE);
		return 2;
	}
	for (i= 0; i < bitmap[0]; i++)	//Bitmaps first byte is the Y boundary.
	{
		for(j=0; j < width; j++)	//The first byte of the bitmap is the Y-axis and the other 2 bytes are SUM of the X-axis.
		{
			drawPixel(j+x_1up, i+y_1up, bitmap[j+i*(width)+ BEGGINING_OF_BITMAP]); //Bytes to set the beginning of the bitmap.
		}
	}
	return 0;
}

/**@brief Draw text function, this function prints the text on the screen.
 *
 * @details This function prints/draws the text on the screen.
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
 *@param x, y Is the position of the starting point of the first letter.
 *@param colour Is the fonts colour.
 *@param tekst[] Is an array with text.
 *@param fontname Can be chosen from fonts of Arial and Consolas.
 *@param fontsize is the size of the font. The size can be chosen from 8 or 32. 0 = 8 and 1 = 32.
 *@param frontstyle is the style of fonts, this can be chosen of Italic, Bold.
 *@retval Error
 *@author Djalil & Tjerk
*/

int drawText(int x, int y, uint8_t colour, char tekst[], char fontname[], uint8_t fontsize, uint8_t fontstyle, uint8_t spaces, uint8_t linefeed)
{
	if (((x < 0) || (x > VGA_DISPLAY_X)) || ((y < 0) || (y > VGA_DISPLAY_Y)))
	{
		softonErrorHandler(ERROR_FONT_OUT_OF_RANGE);
		return 6;
	}
	if (colour > COLOURMAX || colour < COLOURMIN)
	{
		softonErrorHandler(ERROR_FONT_COLOUR_OUT_OF_RANGE);
		return 4;
	}
	if (fontsize > FONT_SIZE)
	{
		softonErrorHandler(ERROR_FONTSIZE_OUT_OF_RANGE);
		return 7;
	}
	if (fontstyle > FONT_STYLE)
	{
		softonErrorHandler(ERROR_FONTSTYLE_OUT_OF_RANGE);
		return 8;
	}
  
	int i, j, k, l = 0;
    int x_old = 0;
	const char *letter;		//Pointer to the array of letter
	char width;				//The width of every letter can be different.

	const char **fonts[] = {Arial_8_addr, Arial_32_addr, Arial_Italic_8_addr, Arial_Italic_32_addr, Arial_Bold_8_addr, Arial_Bold_32_addr,
			Consolas_8_addr, Consolas_32_addr, Consolas_Italic_8_addr, Consolas_Italic_32_addr, Consolas_Bold_8_addr, Consolas_Bold_32_addr};

	char font_name[FONT_NUMBER][FONT_NAME_SIZE] = {"arial", "consolas"};	//Names of fonts in array.
	const char **font;
	const char *width_array;
	for(i = 0; i<FONT_NUMBER+1; i++)
	{
		if (i == FONT_NUMBER)
		{
			softonErrorHandler(ERROR_FONT_NOT_FOUND);
			return 5;
		}
		if(!strcmp(font_name[i], fontname))			//If (font_name==font_name) output is 0.
		{
			font = fonts[i*FONT_TYPES+fontsize+fontstyle*FONT_SIZE];
			width_array = *font;
#ifdef DEBUG_FONT_NAME
			printf("The font name is: ");
			puts(font_name[i]);
			printf("The font width is: ");
			puts(width_array);
#endif
			break;
		}
	}
	for(i = 0; i < strlen(tekst); i++)
	{
		letter = font[tekst[i]-LETTER_BITS];				//Letter bits (= 31)
		width = width_array[tekst[i]-LETTER_WIDTH_BITS];	//letter width (= 32)
		if ((width+x_old+x) > VGA_DISPLAY_X && linefeed)
		{
			x_old=0;
			if (fontsize ==1)
			{
				y += 32;
			}
			else
			{
				y += 8;
			}
		}
		for(j=0; j < 1 +fontsize*FONT_SIZE_POSITION; j++)	//Fonts size is 4th position in array (FONT_SIZE_POSITION = 3).
		{
			for (k=0; k < width; k++)
			{
				for(l=0; l < BYTE_SIZE; l++)
				{
					if ((letter[j*width+k] >> l) & 0x01)	//Compare the LSB with 0x01 (AND) if so, print pixel (font) on the screen.
					{

						drawPixel(x+x_old + k, y+j*BYTE_SIZE+l, colour);
					}
				}
			}
		}
		x_old += k + spaces;	//Space between the letters.
	}
	return 0;
}

/**
 * @brief This function draws a circle
 *
 * @details By using **elementary** mathematics the function draw a circle.
 * 			The for loop draws points of the circle until it drew the whole circle.
 * 			The for loop goes through every angle between 0 - 2 PI radius
 *
 *@param x_pos,y_pos These are the x and y coordinates of the middle of the circle.
 *@param radius This is the radius of the circle.
 *@param angle the angle where to start and stop the circle
 *@param colour This is the colour of the circle
 *<a href="https://opentextbc.ca/precalculusopenstax/chapter/unit-circle-sine-and-cosine-functions/">mathematic proof</a>
 *@retval Error
 *
 *@author Osman Pekcan
 */
int drawCircleplus(uint16_t x_pos, uint16_t y_pos, uint8_t l_radius,uint8_t h_radius,uint16_t l_angle,uint16_t h_angle,uint8_t colour)
{
	uint16_t i=0; // Float because it hold division of PI which are decimal numbers.
	uint8_t j=0;
	int32_t plaats_x = 0, plaats_y = 0;

	if((x_pos-h_radius < 0) || (y_pos-h_radius < 0) || (x_pos+h_radius > VGA_DISPLAY_X) ||  (y_pos+h_radius > VGA_DISPLAY_Y))
	{
		softonErrorHandler(ERROR_CIRCLE_OUT_OF_RANGE);
		return 17;
	}
	if(l_radius > h_radius)
	{
		softonErrorHandler(ERROR_CIRCLE_WRONG_RADIUS);
		return 21;
	}
	if (l_angle > 360 || h_angle > 360)
	{
		softonErrorHandler(ERROR_CIRCLE_OUT_OF_ANGLE);
		return 22;
	}
	if (colour > COLOURMAX || colour < COLOURMIN)
	{
		softonErrorHandler(ERROR_FONT_COLOUR_OUT_OF_RANGE);
		return 23;
	}
#ifdef DEBUG_ANGLE_OF_CIRCLE
	printf("lower boundary \t %d \n higher boundary \t %d \n ", l_angle, h_angle);
#endif
	for(i=l_angle*2*M_PI;i<h_angle*2*M_PI;i += M_PI)
	{ // Loop from lower angle to higher angle
		for(j=l_radius;j<=h_radius;j++) // From lower boundary of the radius to the higher boundary
		{
			plaats_x = x_pos+round(j * cos((float)i/RADIUS_INCREMENT_CIRCLE)); // X = r*cosine(θ)
			plaats_y = y_pos+round(j * sin(-(float)i/RADIUS_INCREMENT_CIRCLE));  // Y = r*sine(θ)
			drawPixel(plaats_x, plaats_y, colour);
		}
	}
	return 0;
}

/**
 * @brief This function draws an parallelogram using length,width and an angle.
 *
 * @param x_pos X coordinate of top left corner
 * @param y_pos Y coordinate of top left corner
 * @param length The length of the parallelogram
 * @param width The width of the parallelogram
 * @param angle The angle of the bottom corner
 * @param colour Colour of the parallelogram
 * @retval Error
 * @author Osman Pekcan
 */
int drawParallelogram(uint16_t x_pos,uint16_t y_pos,uint16_t length,uint16_t width,uint8_t angle,uint8_t colour)
{
	if ((x_pos+width > 320) || (y_pos+length > 240))
	{
		softonErrorHandler(ERROR_PARALLELOGRAM_OUT_OF_RANGE);
		return 23;
	}
	if (angle < 0 || angle > 360)
	{
		softonErrorHandler(ERROR_PARALLELOGRAM_OUT_OF_ANGLE);
		return 24;
	}
	uint8_t x_corner=0,y_corner =0,i=0;

	y_corner = y_pos + length; // Y coordinate of the bottom left corner is simple calculated since the length is given.
	x_corner = x_pos - round((float)x_pos/tan(((float)angle/(float)HALF_CIRCLE_DEGREE)*M_PI)); // X coordinate of bottom left corner is x coordinate of top left corner minus adjacent of a triangle.

	#ifdef DEBUG_CORNER_PARALLELOGRAM
	printf("x corner is \t %d \n y corner is \t %d \n",x_corner,y_corner);
#endif
	for(i=0;i<width;i++)
		myLijntekenaar(x_pos+i,y_pos,x_corner+i,y_corner,colour);
	return 0;
}
