#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>

//These files are needed for fonts and bitmap.
#include "bitmap.h"
#include "fonts/Arial_32.h"
#include "fonts/Arial_8.h"
#include "fonts/Arial_Italic_32.h"
#include "fonts/Arial_Italic_8.h"
#include "fonts/Arial_Bold_32.h"
#include "fonts/Arial_Bold_8.h"
#include "fonts/Consolas_32.h"
#include "fonts/Consolas_8.h"
#include "fonts/Consolas_Italic_32.h"
#include "fonts/Consolas_Italic_8.h"
#include "fonts/Consolas_Bold_32.h"
#include "fonts/Consolas_Bold_8.h"
#include "stm32_ub_vga_screen.h"

#define BEGGINING_OF_BITMAP 3
#define BITMAP_WIDTH_HIGH	2
#define BITMAP_WIDTH_LOW	1

void draw_bitmap(int nr, int x_1up, int y_1up);
void draw_text(int x, int y, char kleur, char tekst[], char fontname[], char fontgrootte, char fontstyle);
