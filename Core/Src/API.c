/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : API.c
  * @brief          : Library for Graphics.
  ******************************************************************************
  */

#include "API.h"

/**
 *@brief Draw bitmap function, this function draws the bitmap; smiley, angry and the four arrows on the screen.
 *
 *@details  Bitmap has 6 icons; smiley, angry and the four arrows.
 *			smiley_map=0, angry_map=1, Arrow left=2, Arrow up=
 *			The user can choose between smiley=0, angry=1, left=2, up=3, right=4, right=5.
 *			Add more bitmapguide:
 *			Step 1: Add bitmap array into bitmap.h
 *			Step 2: At the buttom of bitmap.h change the array and add the name of bitmap.
 *
 *
 *@param nr is the bitmap number to draw.
 *@param x_1up and y_1up is the position of the bitmap
 *@author Djalil & Tjerk
 * */
void drawBitmap(int nr, int x_1up, int y_1up)
{
	if (nr > strlen((const char*)bitmaps))
	{
		softonErrorHandler(ERROR_BITMAP_NOT_FOUND);
	}
	//if (x_1up )
	int i, j = 0;
	const uint8_t *bitmap = bitmaps[nr];
	for (i= 0; i < bitmap[0]; i++)		//Bitmap first byte is the Y boundary.
	{
		for(j=0; j < (uint16_t)(bitmap[BITMAP_WIDTH_HIGH] | (bitmap[BITMAP_WIDTH_LOW] <<8)); j++)	//The first byte of the bitmap is the Y-axis and the other 2 bytes are SUM of the X-axis.
		{
			UB_VGA_SetPixel(j+x_1up, i+y_1up, bitmap[j+i*(uint16_t)(bitmap[BITMAP_WIDTH_HIGH] | (bitmap[BITMAP_WIDTH_LOW] <<8))+ BEGGINING_OF_BITMAP]); //+3 bytes to set the beginning of the bitmap.
		}
	}
}
/**@brief Draw text function, this function prints the text on the screen.
 *
 * @details This function prints/draws the text on the screen.
 * 			The user can choose between Arial= 0 en Consolas=1.
 * 			Each fonts have 3 styles: Standard, Italic and Bold
 * 			Each fonts have 2 sizes:  8, 32
 * 			Fontstyle Standard=0, Italic=1 and Bold=2.
 * 			Fontsize 8=0, 32=1.
 * 			Add more fonts:
 * 			Step 1: Import the header file into fonts folder.
 * 			Step 2: Add all the fonts into **fonts[].
 * 			Step 3: Add fontnames into font_name[][].
 * 			Step 4: Change the Define FONT_NUMBER
 *
 *@param x, y Is the position of the starting point of the first letter.
 *@param colour Is the fonts colour.
 *@param tekst[] Is an array with text.
 *@param fontname Can be chosen from fonts of Arial and Consolas.
 *@param fontsize is the size of the font. The size can be chosen from 8 or 32. 0 = 8 and 1 = 32.
 *@param frontstyle is the style of fonts, this can be chosen of Italic, Bold.
 *@author Djalil & Tjerk
 * */
void drawText(int x, int y, char colour, char tekst[], char fontname[], char fontsize, char fontstyle)
{
	int i, j, k, l = 0;
    int x_old = 0;
	const char *letter;		//Pointer to the array of letter
	char width;				//The width of every letter can be different.

	const char **fonts[] = {Arial_8_addr, Arial_32_addr, Arial_Italic_8_addr, Arial_Italic_32_addr, Arial_Bold_8_addr, Arial_Bold_32_addr,
			Consolas_8_addr, Consolas_32_addr, Consolas_Italic_8_addr, Consolas_Italic_32_addr, Consolas_Bold_8_addr, Consolas_Bold_32_addr};

	char font_name[FONT_NUMBER][FONT_NAME_SIZE] = {"Arial", "Consolas"};	//Names of fonts in array.
	const char **font;
	const char *width_array;
	for(i = 0; i<FONT_NUMBER; i++)
	{
		if(!strcmp(font_name[i], fontname))			//If (font_name==font_name) output is 0.
		{
			font = fonts[i*FONT_TYPES+fontsize+fontstyle*FONT_SIZE];
			width_array = *font;

#ifdef DEBUG_FONT_NAME
		printf("The font name is: ");
		puts(font_name[i]);
		printf("The font width is: ");
		puts(width_array);
#endif
			break;
		}
	}
	for(i = 0; i < strlen(tekst); i++)
	{
		letter = font[tekst[i]-LETTER_BITS];				//Letter bits (= 31)
		width = width_array[tekst[i]-LETTER_WIDTH_BITS];	//letter width (= 32)
		for(j=0; j < 1 +fontsize*FONT_SIZE_POSITION; j++)	//Fonts size is 4th position in array (FONT_SIZE_POSITION = 3).
		{
			for (k=0; k < width; k++)
			{
				for(l=0; l < BYTE_SIZE; l++)
				{
					if ((letter[j*width+k] >> l) & 0x01)	//Compare the LSB with 0x01 (AND) if so, print pixel (font) on the screen.
					{
						UB_VGA_SetPixel(x+x_old + k, y+j*BYTE_SIZE+l, colour);
					}
				}
			}
		}
		x_old += k + SPACE_BETWEEN_LETTER;	//Space between the letters (SPACE_BETWEEN_LETTER =2).
	}
}
