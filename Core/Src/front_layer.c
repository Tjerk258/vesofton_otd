
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

/**
 * @brief Function to check if the UART buffer is filled.
 *
 * @details Checks if UART buffer is filled and if it's filled the logic layer is called for further processing.
 *
 *@author Tjerk ten Dam
 */
void FL_Parser()
{
	if(input.command_execute_flag == TRUE)
	{
#if DEBUG_PARSER
		printf("Parser result = %s", (char*)input.line_rx_buffer);
#endif
		//call logic layer fucntion
		logic_layer(input.line_rx_buffer);
		input.command_execute_flag = FALSE;
	}
}

void softonErrorHandler(uint8_t error)
{
	switch(error)
	{
	case ERROR_BITMAP_NOT_FOUND:
		puts("The number of bitmap you have chosen doesn't exist!");
		break;
	case ERROR_FIGURE_OUT_OFF_RANGE:
		puts("Chosen fonts doesn't exist!");
		break;
	case ERROR_FONT_NOT_FOUND:
		puts("Font not found");
		break;
	case ERROR_FONT_OUT_OF_RANGE:
		puts("blabla");
		break;
	case ERROR_FONTSIZE_OUT_OF_RANGE:
		puts("blabla");
		break;
	case ERROR_FONTSTYLE_OUT_OF_RANGE:
		puts("blabla");
		break;
	case ERROR_BITMAP_OUT_OF_RANGE:
		puts("blabla");
		break;
	default:
		puts("Unknown Error!");
	}
}
