#include "logic_layer.h"

void logic_layer(char commando[])
{
	char commando_list[NUMBER_OF_COMMANDS][20] = {"lijn", "rechthoek", "tekst", "bitmap", "clearscherm", "cirkel", "figuur" };
	char commando_filled[10][20];
	uint8_t i=0, j=0, k=0;


	for(i=0, j=0;commando[i]!='\0';i++, k++)
	{

		if(commando[i]==44)
		{
			commando_filled[j][k]='\0';
			j++;
			i++;
			k=0;
		}
		commando_filled[j][k]=commando[i];
	}

	for(i=0;i<NUMBER_OF_COMMANDS;i++)
	{
		if(strcmp(commando_list[i], commando_filled[0])==0)
		{
			drawLines(100,200,200,200,0x1F,5);
			switch(i)
			{
			case 0:
				drawLines(100,50,200,50,0x03,5);
				drawLines((uint16_t)atoi((char*)commando_filled[1]),
						(uint16_t)atoi((char*)commando_filled[2]),
						(uint16_t)atoi((char*)commando_filled[3]),
						(uint16_t)atoi((char*)commando_filled[4]),
						(uint16_t)atoi((char*)commando_filled[5]),
						(uint16_t)atoi((char*)commando_filled[6]));
				break;
			case 1:
				drawLines(100,150,200,150,0x03,5);
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
				/*drawFigure((uint16_t)atoi((char*)commando_filled[11]),
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
						(uint16_t)atoi((char*)commando_filled[10]));*/
				break;
			case 7:
				//lijn
				break;
			default:
				drawLines(200,150,200,200,0xFC,5);
				printf("place holder");
			}
			break;
		}
	}


}
