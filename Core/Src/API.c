/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : API.c
  * @brief          : Library for Graphics.
  ******************************************************************************
  */

#include "API.h"

/**
 *@brief Draw bitmap function, this function draws the bitmap smiley, angry and the four arrows on the screen.
 *			The user can choose between smiley=0, angry=1, left=2, up=3, right=4, right=5.
 *
 *@param nr is the bitmap number to draw.
 *@param x_1up and y_1up is the position of the bitmap
 * */
void draw_bitmap(int nr, int x_1up, int y_1up)
{
	int i, j;
	const uint8_t *bitmap = bitmaps[nr];
	for (i= 0; i < bitmap[0]; i++)
	{
		for(j=0; j < (uint16_t)(bitmap[BITMAP_WIDTH_HIGH] | (bitmap[BITMAP_WIDTH_LOW] <<8)); j++)	//The first byte of the bitmap is the Y-axis and the other 2 bytes are SUM of the X-axis.
		{
			UB_VGA_SetPixel(j+x_1up, i+y_1up, bitmap[j+i*(uint16_t)(bitmap[BITMAP_WIDTH_HIGH] | (bitmap[BITMAP_WIDTH_LOW] <<8))+ BEGGINING_OF_BITMAP]); //+3 bytes to set the beginning of the bitmap.
		}
	}
}
/**@brief Draw text function, this function prints the text on the screen.
 * 			The user can choose between Arial= 0 en Consolas=1.
 *@param x, y is the position of the starting point of the first letter.
 *@param kleur is the fonts colour.
 *@param tekst[] is an array with text.
 *@param fontname can be chosen from fonts of Arial and Consolas.
 *@param fontgrootte is the size of the font. The size can be chosen from 8 or 32. 0 = 8 and 1 = 32.
 *@param frontstyle is the style of fonts, this can be chosen of Italic, Bold.
 * */
void draw_text(int x, int y, char kleur, char tekst[], char fontname[], char fontgrootte, char fontstyle)
{
	int i, j, k, l;
	int x_old = 0;
	const char *letter;		//Pointer to the array of letter
	char width;				//The width of every letter can be different.

	const char **fonts[] = {Arial_8_addr, Arial_32_addr, Arial_Italic_8_addr, Arial_Italic_32_addr, Arial_Bold_8_addr, Arial_Bold_32_addr,
			Consolas_8_addr, Consolas_32_addr, Consolas_Italic_8_addr, Consolas_Italic_32_addr, Consolas_Bold_8_addr, Consolas_Bold_32_addr};

	char font_name[3][20] = {"Arial", "Consolas"};	//Names of fonts in array.
	const char **font;
	const char *width_array;
	for(i = 0; i<2; i++)
	{
		if(!strcmp(font_name[i], fontname))			//If (font_name == font_name) output is 0.
		{
			font = fonts[i*FONT_TYPES+fontgrootte+fontstyle*FONT_SIZE];
			width_array = *font;
			break;
		}
	}
	for(i = 0; i < strlen(tekst); i++)
	{
		letter = font[tekst[i]-31];				//The first character spacebar.
		width = width_array[tekst[i]-32];
		for(j=0; j < 1 +fontgrootte*3; j++)		//cijfer define maken.
		{
			for (k=0; k < width; k++)
			{
				for(l=0; l < BYTE_SIZE; l++)
				{
					if ((letter[j*width+k] >> l) & 0x01)	//Compare the LSB with 0x01 (AND) if so, then print then print pixel (font) on the screen.
					{
						UB_VGA_SetPixel(x+x_old + k, y+j*BYTE_SIZE+l, kleur);
					}
				}
			}
		}
		x_old += k + 2;	// draw 2 pixels between the letters.
	}
}
