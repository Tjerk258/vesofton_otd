
/**
* @file  front_layer.c
* @author Tjerk ten Dam
* @version 1.0
*
* @section LICENSE
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* @section DESCRIPTION
*
* The time class represents a moment of time.
*/

#include "front_layer.h"
#include "usart.h"
#include "error.h"
#include "logic_layer.h"

input_vars input;

/**
 * @brief Function for initialisatie of the UART.
 *
 * @details First the function empties out the buffer and initialist the HAL UART
 *
 *@author Tjerk ten Dam
 */
void FL_UART_Init()
{
	int i;

	for(i = 0; i < LINE_BUFLEN; i++)
		input.line_rx_buffer[i] = 0;

	// Reset some stuff
	input.byte_buffer_rx[0] = 0;
	input.char_counter = 0;
	input.command_execute_flag = FALSE;

	// HAl wants a memory location to store the charachter it receives from the UART
	// We will pass it an array, but we will not use it. We declare our own variable in the interupt handler
	// See stm32f4xx_it.c
	HAL_UART_Receive_IT(&huart2, input.byte_buffer_rx, BYTE_BUFLEN);
}

void softonErrorHandler(uint8_t error)
{
	error_on_screen(error);
	switch(error)
	{
	case ERROR_BITMAP_NOT_FOUND:
		puts("The number of bitmap you have chosen doesn't exist!");
		break;
	case ERROR_BITMAP_OUT_OF_RANGE:
		puts("Bitmap out of range!");
		break;
	case ERROR_BITMAP_POSITION_OUT_OF_RANGE:
		puts("Bitmap positioning out of range!");
		break;
	case ERROR_FONT_NOT_FOUND:
		puts("Font not found!");
		break;
	case ERROR_FONT_OUT_OF_RANGE:
		puts("Font out of range!");
		break;
	case ERROR_FONTSIZE_OUT_OF_RANGE:
		puts("Font size out of range!");
		break;
	case ERROR_FONTSTYLE_OUT_OF_RANGE:
		puts("Font style out of range!");
		break;
	case ERROR_LINE_OUT_OF_RANGE:
		puts("Line out of range!");
		break;
	case ERROR_LINE_LENGTH_OUT_OF_RANGE:
		puts("Line length out of range");
		break;
	case ERROR_LINE_COLOUR_OUT_OF_RANGE:
		puts("Line colour out of range!");
		break;
	case ERROR_LINE_WIDTH_OUT_OF_RANGE:
		puts("Line width out of range!");
		break;
	case ERROR_RECT_OUT_OF_RANGE:
		puts("Rectangle out of range!");
		break;
	case ERROR_RECT_COLOUR_OUT_OF_RANGE:
		puts("Ractangle colour out of range!");
		break;
	case ERROR_FILLED_OUT_OF_RANGE:
		puts("Filled out of range!");
		break;
	case ERROR_CIRCLE_COLOUR_OUT_OF_RANGE:
		puts("Circle colour out of range!");
		break;
	case ERROR_CIRCLE_OUT_OF_RANGE:
		puts("Circle out of range!");
		break;
	case ERROR_FIGURE_COLOUR_OUT_OF_RANGE:
		puts("Figure colour out of range!");
		break;
	case ERROR_FIGURE_LENGTH_OUT_OF_RANGE:
		puts("Figure length out of range!");
	case ERROR_COLOUR_NOT_FOUND:
		puts("The colour you have entered, doesn't exist!");
		break;
	default:
		puts("Unknown Error!");
	}
}

void error_on_screen(uint8_t error)
{
	char buffer[MAX_NUMBER_OF_SCRIPT_CHARACTER];
	drawRect(268,226,50,12,VGA_COL_WHITE,0,1,VGA_COL_BLACK); // draws a white filled rectangle with black borders in the bottom right corner
	drawText(275,227,VGA_COL_BLACK,"Error:","arial",0,0); // draws the text "Error:" inside the rectangle
	drawText(307,227,VGA_COL_BLACK,itoa(error,buffer,10),"arial",0,0); // draws the number of error inside the rectangle
}
