#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "API.h"

#define NUMBER_OF_COMMANDS 11
#define POINT_OF_FIGURE 5
#define MAX_NUMBER_OF_SCRIPT_CHARACTER 150
#define MAX_SCRIPT_COMMANDOS 15
#define ASCII_OF_COMMA 44
#define ASCII_OF_BACKSLASH 92
#define COLOUR_CHAR_MAX		50
#define COLOUR_LIST			17


#define NUMBER_OF_FONT_STYLES 3
#define NUMBER_OF_COLORS 10
//#define DEBUG_COMMANDO
//#define DEBUG_NUMBEROFCOMMANDO

#define BUFFER_SIZE 200


typedef struct
{
	char buffer[BUFFER_SIZE][MAX_NUMBER_OF_SCRIPT_CHARACTER];
	int counter;
	int waitFlag;
	int head;
	int executed;
}wait_vars;

extern wait_vars wait;

//Prototypes
int logic_layer(char commando[]);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void buffer_init();
void writeBuffer(char buf[]);
int indexBuffer(int index);

