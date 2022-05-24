#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "API.h"

#define NUMBER_OF_COMMANDS 7
#define POINT_OF_FIGURE 5
#define MAX_NUMBER_OF_SCRIPT_CHARACTER 20
#define MAX_SCRIPT_COMMANDOS 15
#define ASCII_OF_COMMA 44
#define COLOUR_CHAR_MAX		50
#define COLOUR_LIST			17


//#define DEBUG_COMMANDO
//#define DEBUG_NUMBEROFCOMMANDO

//Prototypes
int logic_layer(char commando[]);
