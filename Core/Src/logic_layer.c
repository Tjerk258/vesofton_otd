#include "logic_layer.h"
#include "error.h"

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
			if(!strcmp(r3g3b2_Colour[i], command))
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
	char commando_list[NUMBER_OF_COMMANDS][MAX_NUMBER_OF_SCRIPT_CHARACTER] = {"lijn", "rechthoek", "tekst", "bitmap", "clearscherm", "cirkel", "figuur" }; // The script commando that the project needs to do.
	char commando_filled[MAX_SCRIPT_COMMANDOS][MAX_NUMBER_OF_SCRIPT_CHARACTER]; // Here is the script split into multiple array.
	uint8_t i=0, j=0, k=0;
#ifdef DEBUG_COMMANDO
	puts(commando);
#endif

	for(i=0, j=0;commando[i]!='\0';i++, k++)
	{
		if(commando[i]==ASCII_OF_COMMA)
		{
			commando_filled[j][k]='\0'; // Add end string for strcmp.
			j++; // Go to the new array in the double array.
			i++; // To skip the comma in the commando array.
			k=0; // Start at the begin
		}
		commando_filled[j][k]=commando[i];
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
						(uint16_t)atoi((char*)commando_filled[5]),
						(uint16_t)atoi((char*)commando_filled[6]));
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
						(uint8_t)atoi((char*)commando_filled[5]),
						(uint16_t)atoi((char*)commando_filled[6]));
				break;
			/*case 2:
				drawLines(100,10,200,10,0x1F,5);
				drawText((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint16_t)atoi((char*)commando_filled[3]),
						(char*)commando_filled[4],
						(char*)commando_filled[5],
						(uint16_t)atoi((char*)commando_filled[6]),
						(char*)commando_filled[7]);*/
				break;
			case 3:
				drawBitmap((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint16_t)atoi((char*)commando_filled[3]));
				break;
			case 4:
				/*clearScreen((uint16_t)atoi((char*)commando_filled[1]));*/
				break;
			case 5:
				drawCircle((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint8_t)atoi((char*)commando_filled[3]),
						(uint8_t)atoi((char*)commando_filled[4]));
				break;
			case 6:
				drawFigure((uint16_t)atoi((char*)commando_filled[11]),
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

				break;
			default:
				printf("place holder");
			}
			break;
		}
	}
	return 0;
}
