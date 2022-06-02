#include "logic_layer.h"
#include "stm32_ub_vga_screen.h"
#include "error.h"
#include "tim.h"
#include <string.h>

wait_vars wait;

/**
 *@brief	This function translates font_style tekst to variable.
 *
 *@param command This is the font_style string.
 *
 *@retval Variable for tekst function
 *@retval 0 = normal tekst
 *@retval 1 = bold tekst
 *@retval 2 = Italic tekst
 *
 *@authors Osman Pekcan,Tjerk ten Dam
 */
uint8_t font_style(char command[])
{
	char styles_array[NUMBER_OF_FONT_STYLES][MAX_NUMBER_OF_SCRIPT_CHARACTER] = {"normaal","cursief","vet"};
	uint8_t i;
	for(i = 0; i< NUMBER_OF_FONT_STYLES;i++)
	{
		if(!strcmp(styles_array[i],command))
		{
			return i;
		}
	}
	return 8;
}

/**
 *@brief	This function is the 8 bit color designation
 *			8bit color (R3G3B2)
 * 			Red   (3bit) -> Bit7-Bit5
 *			Green (3bit) -> Bit4-Bit2
 * 			Blue  (2bit) -> Bit1-Bit0
 *
 *@param commando[] this is the
 *@authors Djalil
 */
uint8_t r3g3b2_Colour(char command[])
{
	char colourList[COLOUR_LIST][COLOUR_CHAR_MAX]= { "zwart", "blauw", "lichtblauw", "groen", "lichtgroen", "rood", "lichtrood", "wit",
													 "cyaan", "lichtcyaan", "magenta", "lichtmagenta", "bruin", "geel", "grijs", "roos", "paars" };
		uint8_t i= 0;
		uint8_t colourNumber = (sizeof(colourList) / sizeof(colourList[0])); //Define maken voor positie nul?
		for (i=0; i < colourNumber; i++)
		{
			if(!strcmp(colourList[i], command))
			{
				switch(i)
				{
				case 0:
					return VGA_COL_BLACK;
				case 1:
					return VGA_COL_BLUE;
				case 2:
					return VGA_COL_LIGHT_BLUE;
				case 3:
					return VGA_COL_GREEN;
				case 4:
					return VGA_COL_LIGHT_GREEN;
				case 5:
					return VGA_COL_RED;
				case 6:
					return VGA_COL_LIGHT_RED;
				case 7:
					return VGA_COL_WHITE;
				case 8:
					return VGA_COL_CYAN;
				case 9:
					return VGA_COL_LIGHT_CYAN;
				case 10:
					return VGA_COL_MAGENTA;
				case 11:
					return VGA_COL_LIGHT_MAGENTA;
				case 12:
					return VGA_COL_BROWN;
				case 13:
					return VGA_COL_YELLOW;
				case 14:
					return VGA_COL_GRAY;
				case 15:
					return VGA_COL_PINK;
				case 16:
					return VGA_COL_VIOLET;
				default:
					softonErrorHandler(ERROR_COLOUR_NOT_FOUND);
					return 20;
				}
			}
		}
		return 0;
}

/**
 *@brief	This function is for initilising buffer of scripts.
 *
 *@authors Tjerk ten Dam
 */
void buffer_init()
{
	wait.head = 0;
	wait.waitFlag = 0;
	wait.counter = -1;
	wait.executed = 0;
}

/**
 *@brief	Tim callback when period is elapsed
 *
 *@details	This callback functions gets called when the timer period is elapsed for the wait function and when elapsed the wait flag gets reset.
 *
 *@param *htim	handle of the timer
 *
 *@authors Tjerk ten Dam
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance==TIM5)
  {
	  wait.waitFlag = 0;
	  HAL_TIM_Base_Stop_IT(&htim5);
  }
}


/**
 *@brief	This function writes a array to the cirulair script buffer
 *
 *@param buf	array to be write to the script buffer
 *
 *@authors Tjerk ten Dam
 */
void writeBuffer(char buf[])
{
	if(wait.head == BUFFER_SIZE-1)
		wait.head = 0;

	else
		wait.head++;

	strcpy(wait.buffer[wait.head], buf);
}

/**
 *@brief	This function translates a index for the script buffer
 *
 *@param index index for the script buffer
 *
 *@retval correct index for the circulair buffer
 *
 *@authors Tjerk ten Dam
 */
int indexBuffer(int index)
{
	if(index >= BUFFER_SIZE)
		return(index - BUFFER_SIZE);
	else if(index < 0)
		return(index + BUFFER_SIZE);
	else
		return index;
}


/**
 *@brief	This function looks at input array and calls function the input array calls for
 *
 *@details	First script commando's are split up and put into array: commando_filled.
 *			Then the function looks which script is called.
 *			If the function found the script that is called, the corresponding function is called.
 *
 *@param commando This is the script commando.
 *@authors Osman Pekcan,Tjerk ten Dam
 */
int logic_layer(char commando[])
{
	char commando_list[NUMBER_OF_COMMANDS][MAX_NUMBER_OF_SCRIPT_CHARACTER] = {"lijn", "rechthoek", "tekst", "bitmap", "clearscherm", "cirkel", "figuur", "herhaal", "wacht","cirkel2","parallelogram"}; // The script commando that the project needs to do.
	char commando_filled[MAX_SCRIPT_COMMANDOS][MAX_NUMBER_OF_SCRIPT_CHARACTER]; // Here is the script split into multiple array.
	uint8_t i=0, j=0, k=0;
#ifdef DEBUG_COMMANDO
	puts(commando);
#endif


	while(1)
	{
		if(!k)
			for(; commando[i] == ' '; i++);		//removing spaces add the beginnning of every script command

		if(commando[i]==ASCII_OF_BACKSLASH)
		{
			if(commando[i+1]==ASCII_OF_COMMA)
			{
				i++;
				commando_filled[j][k]=commando[i];
				i++;
				k++;
			}
		}
		else if(commando[i]==ASCII_OF_COMMA || commando[i]=='\0')
		{
			for(; commando_filled[j][k-1] == ' '; k--);		//removing spaces add the end of every script command
			commando_filled[j][k]='\0'; // Add end string for strcmp.
			j++; // Go to the new array in the double array.
			i++; // To skip the comma in the commando array.
			k=0; // Start at the begin
			if(commando[i]=='\0')
				break;
		}
		else
		{
			commando_filled[j][k]=commando[i];
			i++;
			k++;
		}
	}

	for(i=0;i<NUMBER_OF_COMMANDS;i++)
	{
		if(strcmp(commando_list[i], commando_filled[0])==0) // If the first script commando is one of the commando in the list.
		{
#ifdef DEBUG_NUMBEROFCOMMANDO
				printf("In commando list \t");puts(commando_list[i]);
				printf("In commando filled \t");puts(commando_filled[i]);
				printf("value of i is \t%d",i);
#endif
			switch(i) // find the number of commands
			{
			case 0:

				drawLines((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint16_t)atoi((char*)commando_filled[3]),
						(uint16_t)atoi((char*)commando_filled[4]),
						(uint16_t)r3g3b2_Colour((char*)commando_filled[5]),
						(uint8_t)atoi((char*)commando_filled[6]),
						(uint8_t)atoi((char*)commando_filled[7]));
				break;
			case 1:
				if (atoi((char*)commando_filled[5]) > 255)
				{
					softonErrorHandler(ERROR_RECT_COLOUR_OUT_OF_RANGE);
					return 13;
				}
				drawRect((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint16_t)atoi((char*)commando_filled[3]),
						(uint16_t)atoi((char*)commando_filled[4]),
						(uint16_t)r3g3b2_Colour((char*)commando_filled[5]),
						(uint8_t)atoi((char*)commando_filled[6]),
						(uint8_t)atoi((char*)commando_filled[7]),
						(uint16_t)r3g3b2_Colour((char*)commando_filled[8]));
				break;
			case 2:
				drawText((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						r3g3b2_Colour((char*)commando_filled[3]),
						(char*)commando_filled[4],
						(char*)commando_filled[5],
						(uint16_t)atoi((char*)commando_filled[6])-1,
						font_style((char*)commando_filled[7]),
						(uint8_t)atoi((char*)commando_filled[8]),
						(uint8_t)atoi((char*)commando_filled[9]));
				break;
			case 3:
				drawBitmap((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint16_t)atoi((char*)commando_filled[3]));
				break;
			case 4:
				UB_VGA_FillScreen(r3g3b2_Colour((char*)commando_filled[1]));
				break;
			case 5:
				drawCircle((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint8_t)atoi((char*)commando_filled[3]),
						(uint8_t)r3g3b2_Colour((char*)commando_filled[4]),
						(uint8_t)atoi((char*)commando_filled[5]));
				break;
			case 6:
				drawFigure((uint16_t)r3g3b2_Colour((char*)commando_filled[11]),
						(uint8_t)atoi((char*)commando_filled[12]),
						POINT_OF_FIGURE,
						(uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint16_t)atoi((char*)commando_filled[3]),
						(uint16_t)atoi((char*)commando_filled[4]),
						(uint16_t)atoi((char*)commando_filled[5]),
						(uint16_t)atoi((char*)commando_filled[6]),
						(uint16_t)atoi((char*)commando_filled[7]),
						(uint16_t)atoi((char*)commando_filled[8]),
						(uint16_t)atoi((char*)commando_filled[9]),
						(uint16_t)atoi((char*)commando_filled[10]));
				break;
			case 7:
			    if(wait.counter > 0)	// if it is repeating
			    {
			        wait.counter--;
			        wait.executed = wait.executed - atoi((char*)commando_filled[1]) - 1;
			    }
			    else if(wait.counter == 0) //if it is done repeating
			    {
			        wait.counter = -1;
			    }
			    else if(wait.counter == -1)	//if repeat has te be setup
			    {
			        if(atoi((char*)commando_filled[3]))		//if repeat is otherway around
			        {
			            char temp[MAX_NUMBER_OF_SCRIPT_CHARACTER];
			            for(int m = 0; m< (atoi((char*)commando_filled[1])) / 2 + 1; m++)
			            {
			                strcpy(temp, wait.buffer[indexBuffer(wait.executed - 1 - m)]);
			                strcpy(wait.buffer[indexBuffer(wait.executed - 1 - m)], wait.buffer[indexBuffer(wait.executed - atoi((char*)commando_filled[1]) - 1 + m)]);
			                strcpy(wait.buffer[indexBuffer(wait.executed - atoi((char*)commando_filled[1]) - 1 + m)], temp);
			            }
			        }
			        wait.counter = atoi((char*)commando_filled[2])-1;
			        wait.executed = wait.executed - atoi((char*)commando_filled[1]) - 1;
			    }
			    indexBuffer(wait.executed);

			    break;
			case 8:
			    wait.waitFlag = 1;
			    __HAL_TIM_SET_AUTORELOAD(&htim5,(atoi((char*)commando_filled[1]) * 2));	//set timer period
			    __HAL_TIM_CLEAR_IT(&htim5, TIM_IT_UPDATE);	//clear timer interupt
			    HAL_TIM_Base_Start_IT(&htim5);	//start tim
			    break;
			case 9:
				drawCircleplus((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint8_t)atoi((char*)commando_filled[3]),
						(uint8_t)atoi((char*)commando_filled[4]),
						(uint16_t)atoi((char*)commando_filled[5]),
						(uint16_t)atoi((char*)commando_filled[6]),
						(uint8_t)r3g3b2_Colour((char*)commando_filled[7]));
				break;
			case 10:
				drawParallelogram((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint16_t)atoi((char*)commando_filled[3]),
						(uint16_t)atoi((char*)commando_filled[4]),
						(uint8_t)atoi((char*)commando_filled[5]),
						(uint8_t)r3g3b2_Colour((char*)commando_filled[6]));
				break;
			default:
				printf("place holder");
			}
			break;
		}
	}
	return 0;
}

