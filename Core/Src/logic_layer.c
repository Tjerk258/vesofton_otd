#include "logic_layer.h"
#include "stm32_ub_vga_screen.h"
#include "error.h"


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
	char styles_array[NUMBER_OF_FONT_STYLES][MAX_NUMBER_OF_SCRIPT_CHARACTER] = {"normaal","vet","cursief"};
	uint8_t i;
	for(i = 0; i< NUMBER_OF_FONT_STYLES;i++)
	{
		if(!strcmp(styles_array[i],command))
		{
			return i;
		}
	}
	softonErrorHandler(ERROR_FONTSTYLE_NOT_FOUND);
	return 0;
}

/**
 *@brief	This function translates color tekst to 8 bit color variable.
 *
 *@param command This is the color string.
 *@retval Returns 8bit color value.
 *@authors Osman Pekcan,Tjerk ten Dam
 */
uint8_t kleur_decoder(char command[])
{
	char styles_array[NUMBER_OF_COLORS][MAX_NUMBER_OF_SCRIPT_CHARACTER] = {"zwart","blauw","groen","rood","wit","lichtcyaan","magenta","geel","grijs","bruin"};
		uint8_t i;
		for(i = 0; i< NUMBER_OF_COLORS;i++)
		{
			if(!strcmp(styles_array[i],command))
			{
				switch(i)
				{
				case 0:
					return VGA_COL_BLACK;
				case 1:
					return VGA_COL_BLUE;
				case 2:
					return VGA_COL_GREEN;
				case 3:
					return VGA_COL_RED;
				case 4:
					return VGA_COL_WHITE;
				case 5:
					return VGA_COL_CYAN;
				case 6:
					return VGA_COL_MAGENTA;
				case 7:
					return VGA_COL_YELLOW;
				case 8:
					return VGA_COL_GRIJS;
				case 9:
					return VGA_COL_BROWN;
				}
			}
		}
	softonErrorHandler(ERROR_COLOR_NOT_FOUND);
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
void logic_layer(char commando[])
{
	char commando_list[NUMBER_OF_COMMANDS][MAX_NUMBER_OF_SCRIPT_CHARACTER] = {"lijn", "rechthoek", "tekst", "bitmap", "clearscherm", "cirkel", "figuur" }; // The script commando that the project needs to do.
	char commando_filled[MAX_SCRIPT_COMMANDOS][MAX_NUMBER_OF_SCRIPT_CHARACTER]; // Here is the script split into multiple array.
	uint8_t i=0, j=0, k=0;

#ifdef DEBUG_COMMANDO
	puts(commando);
#endif

	for(i=0, j=0;commando[i]!='\0' && commando[i] != 0x0D ;i++, k++)
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
						(uint16_t)kleur_decoder((char*)commando_filled[5]),
						(uint16_t)atoi((char*)commando_filled[6]));
				break;
			case 1:
				drawRect((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint16_t)atoi((char*)commando_filled[3]),
						(uint16_t)atoi((char*)commando_filled[4]),
						(uint16_t)kleur_decoder((char*)commando_filled[5]),
						(uint16_t)atoi((char*)commando_filled[6]));
				break;
			case 2:
//				drawLines(100,10,200,10,0x1F,5);
				drawText((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						kleur_decoder((char*)commando_filled[3]),
						(char*)commando_filled[4],
						(char*)commando_filled[5],
						(uint16_t)atoi((char*)commando_filled[6])-1,
						font_style((char*)commando_filled[7]));
				break;
			case 3:
				drawBitmap((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint16_t)atoi((char*)commando_filled[3]));
				break;
			case 4:
				UB_VGA_FillScreen(kleur_decoder((char*)commando_filled[1]));
				break;
			case 5:
				drawCircle((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint8_t)atoi((char*)commando_filled[3]),
						(uint8_t)kleur_decoder((char*)commando_filled[4]));
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
						(uint16_t)kleur_decoder((char*)commando_filled[10]));
				break;
			case 7:
				//lijn
				break;
			default:
				printf("place holder");
			}
			break;
		}
	}
}

