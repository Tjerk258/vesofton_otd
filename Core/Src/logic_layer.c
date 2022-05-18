#include "logic_layer.h"

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
				drawRect((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint16_t)atoi((char*)commando_filled[3]),
						(uint16_t)atoi((char*)commando_filled[4]),
						(uint16_t)atoi((char*)commando_filled[5]),
						(uint16_t)atoi((char*)commando_filled[6]));
				break;
			/*case 2:
				drawLines(100,10,200,10,0x1F,5);
				/*drawText((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint16_t)atoi((char*)commando_filled[3]),
						(char*)commando_filled[4],
						(char*)commando_filled[5],
						(uint16_t)atoi((char*)commando_filled[6]),
						(char*)commando_filled[7]);*/
				break;
			case 3:
				/*drawBitmap((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint16_t)atoi((char*)commando_filled[3]));*/
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
				//lijn
				break;
			default:
				printf("place holder");
			}
			break;
		}
	}


}
