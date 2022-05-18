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
void FL_UART_Check()
{
	if(input.command_execute_flag == TRUE)
	{
		printf("%s",input.line_rx_buffer);
		printf("okay");
		//call logic layer fucntion
//		logic_layer(input.line_rx_buffer);
		input.command_execute_flag = FALSE;
	}
}


void error(int errorCode)
{
	switch(errorCode)
	{
	case 1:
		printf("error 1");
		break;
	default:
		printf("Unknown error occurred");
	}
}

void help()
{
	printf("Standaard commando’s:/n\
			lijn, x, y, x’, y’, kleur, dikte/n\
			rechthoek, x_lup, y_lup, breedte, hoogte, kleur, gevuld (1,0) [als 1: rand (1px) met kleur]/n\
			tekst, x, y, kleur, tekst, fontnaam (arial, consolas), fontgrootte (1,2), fontstijl (normaal, vet, cursief)/n\
			bitmap, nr, x-lup, y-lup  [tenminste: pijl (in 4 richtingen), smiley (boos, blij)]/n\
			clearscherm, kleur/n\
			/n\
			Bonus-commando’s (voor bonuspunten):/n\
			wacht, msecs/n\
			herhaal, aantal (laatst uitgevoerde commando’s), hoevaak (herhalen)/n\
			cirkel, x, y, radius, kleur/n\
			figuur, x1,y1, x2,y2, x3,y3, x4,y4, x5,y5, kleur/n");
}


