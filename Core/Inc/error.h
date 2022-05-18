/*
 * error.h
 *
 *  Created on: 12 mei 2022
 *      Author: Djalil
 */
#include <stdint.h>
#include <stdio.h>

#define ERROR_BITMAP_NOT_FOUND			1
#define ERROR_FIGURE_OUT_OFF_RANGE		2
#define ERROR_FONT_NOT_FOUND			3
#define ERROR_FONT_OUT_OF_RANGE			4
#define ERROR_FONTSIZE_OUT_OF_RANGE 	5
#define ERROR_FONTSTYLE_OUT_OF_RANGE 	6
#define ERROR_BITMAP_OUT_OF_RANGE		7

//prototypes
void softonErrorHandler(uint8_t error);
