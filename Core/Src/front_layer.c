#include "error.h"

void softonErrorHandler(uint8_t error)
{
	switch(error)
	{
	case ERROR_BITMAP_NOT_FOUND:
		puts("The number of bitmap you have chosen doesn't exist!");
		break;
	case ERROR_FIGURE_OUT_OFF_RANGE:
		puts("blabla");
		break;
	default:
		puts("Unknown Error!");
	}
}
