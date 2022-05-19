/*
 * error.h
 *
 *  Created on: 12 mei 2022
 *      Author: Djalil
 */
#include <stdint.h>
#include <stdio.h>

#define ERROR_BITMAP_NOT_FOUND				1
#define ERROR_BITMAP_OUT_OF_RANGE			2
#define ERROR_FONT_COLOR_OUT_OF_RANGE		3
#define ERROR_FONT_NOT_FOUND				4
#define ERROR_FONT_OUT_OF_RANGE				5
#define ERROR_FONTSIZE_OUT_OF_RANGE 		6
#define ERROR_FONTSTYLE_OUT_OF_RANGE 		7
#define ERROR_LINE_OUT_OF_RANGE				8
#define ERROR_LINE_LENGTH_OUT_OF_RANGE		9
#define ERROR_LINE_COLOR_OUT_OF_RANGE		10
#define ERROR_LINE_WIDTH_OUT_OF_RANGE		11
#define ERROR_RECT_OUT_OF_RANGE				12
#define	ERROR_RECT_COLOR_OUT_OF_RANGE		13
#define ERROR_FILLED_OUT_OF_RANGE			14
#define ERROR_CIRCLE_COLOR_OUT_OF_RANGE 	15
#define ERROR_CIRCLE_OUT_OF_RANGE			16
#define ERROR_FIGURE_COLOR_OUT_OF_RANGE 	17
#define ERROR_FIGURE_LENGTH_OUT_OF_RANGE 	18

//prototypes
void softonErrorHandler(uint8_t error);
