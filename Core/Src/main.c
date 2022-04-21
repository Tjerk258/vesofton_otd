//--------------------------------------------------------------
// File     : main.c
// Datum    : 30.03.2016
// Version  : 1.0
// Autor    : UB
// mods by	: J.F. van der Bent
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.x
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : VGA_core DMA LIB 320x240, 8bit color
//--------------------------------------------------------------

#include "main.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#define length 100
#define beginpunt 20


int main(void)
{
	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen
	UB_VGA_FillScreen(VGA_COL_YELLOW);

  while(1)
  {
	  uint8_t i;
	  for(i=beginpunt; i<=length; i++)
	  {
		  UB_VGA_SetPixel(160, i, VGA_COL_RED);	//Draw a vertical line in middle of the screen with a length of 80 pixels
	  }
  }
}
