#include "bitmap.h"
#include "API.h"

//Draw bitmap function
void draw_bitmap(int nr, int x_1up, int y_1up)
{
	char i, j;
	const uint8_t *bitmap = bitmaps[nr];
	for (i= 0; i < bitmap[0]; i++)
	{
		for(j=0; j < bitmap[1]; j++)
		{
			UB_VGA_SetPixel(j+x_1up,i+y_1up,bitmap[j+i*bitmap[0]+2]);

		}
	}
}
