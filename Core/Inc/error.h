/**
  ******************************************************************************
  * @file           : error.h
  * @brief          : Defines for all error codes
  * @author			: Djalil
  ******************************************************************************
  */
#include <stdint.h>
#include <stdio.h>

#define ERROR_BITMAP_NOT_FOUND				1
#define ERROR_BITMAP_OUT_OF_RANGE			2
#define ERROR_BITMAP_POSITION_OUT_OF_RANGE	3
#define ERROR_FONT_COLOUR_OUT_OF_RANGE		4
#define ERROR_FONT_NOT_FOUND				5
#define ERROR_FONT_OUT_OF_RANGE				6
#define ERROR_FONTSIZE_OUT_OF_RANGE 		7
#define ERROR_FONTSTYLE_OUT_OF_RANGE 		8
#define ERROR_LINE_OUT_OF_RANGE				9
#define ERROR_LINE_LENGTH_OUT_OF_RANGE		10
#define ERROR_LINE_COLOUR_OUT_OF_RANGE		11
#define ERROR_LINE_WIDTH_OUT_OF_RANGE		12
#define ERROR_RECT_OUT_OF_RANGE				13
#define	ERROR_RECT_COLOUR_OUT_OF_RANGE		14
#define ERROR_FILLED_OUT_OF_RANGE			15
#define ERROR_CIRCLE_COLOUR_OUT_OF_RANGE 	16
#define ERROR_CIRCLE_OUT_OF_RANGE			17
#define ERROR_FIGURE_COLOUR_OUT_OF_RANGE 	18
#define ERROR_FIGURE_LENGTH_OUT_OF_RANGE 	19
#define ERROR_COLOUR_NOT_FOUND				20
#define ERROR_CIRCLE_WRONG_RADIUS			21
#define ERROR_CIRCLE_OUT_OF_ANGLE			22
#define ERROR_PARALLELOGRAM_OUT_OF_RANGE	23
#define ERROR_PARALLELOGRAM_OUT_OF_ANGLE	24

//prototypes
void softonErrorHandler(uint8_t error);
