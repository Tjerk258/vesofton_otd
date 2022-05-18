#include "API.h"

void myLijntekenaar(uint16_t x_begin, uint16_t y_begin, uint16_t x_eind, uint16_t y_eind,uint8_t kleur)
{
	uint8_t i=0;
	float derivative = 0.0; // Float since the formula creates decimal numbers that are needed to calculate line_var
	int16_t x_offset=0, y_offset=0;
	uint16_t start_point = 0, end_point = 0;
	uint16_t line_var = 0; // The variable which is used to calculated increments of either x or y coordinates

	x_offset = x_begin - x_eind;// Offset is used to determine if the line is straight
	y_offset = y_begin - y_eind; // Offset is also used to calculated the derivative.

#ifdef DEBUG_OFFSET
	printf("Here value of x offset \t %d \n", x_offset);
	printf("Here value of y offset \t %d \n", y_offset);
#endif

	UB_VGA_SetPixel(x_begin, y_begin, kleur); // The arithmetic of the function something does not write the start point or end point.
	UB_VGA_SetPixel(x_eind, y_eind, kleur); // ""

	if (x_offset == 0 || y_offset == 0) // If the line is a line either one of the offset is zero.
	{
		if (x_offset == 0) // If the line is horizontal the offset from the x axis is zero.
		{
			if (y_offset > 0) // The orientation of the line determines where the code needs to start.
			{
				start_point = y_eind;
				end_point = y_begin;
			}
			else
			{
				start_point = y_begin;
				end_point = y_eind;
			}
			for (i = start_point; i < end_point + 1; i++)
			{
				UB_VGA_SetPixel(x_begin, (start_point)+(i-start_point), kleur);
			}

		}
		if (y_offset == 0) // If the line is vertical the offset from the y axis is zero
		{
			if (x_offset > 0)
			{
				start_point = x_eind;
				end_point = x_begin;
			}
			else
			{
				start_point = x_begin;
				end_point = x_eind;
			}
			for (i = start_point; i < end_point + 1; i++)
			{
				UB_VGA_SetPixel((start_point)+(i - start_point), y_begin, kleur);
			}
		}
	}
	else
	{
		derivative = (float)y_offset / (float)x_offset; // Calculate the derivative.
#ifdef DEBUG_DERIVATIVE
		printf("Here value of the derivative \t %.5f \n", derivative);
#endif
		if (fabs(derivative) >= 1) // Determines whether x or y value changes with the derivative.
		{							// Also the line_var calculation changes
			if (derivative > 0) // The polarity of the derivative will change the polarity parameter in line_var.
			{
				if (x_offset < 0) // The orientation of the line decides which parameter of the function is the start and end point of the loop.
				{
					start_point = y_begin;
					end_point = y_eind;
				}
				else
				{
					start_point = y_eind;
					end_point = y_begin;
				}
				for (i= start_point; i< end_point;i++)
				{
					line_var = round((1/derivative)*(i-y_begin))+ x_begin;
#ifdef DEBUG_LINE_VAR
					printf("lijn variable : \t %d\n", line_var);
#endif
					UB_VGA_SetPixel(line_var, y_begin + (i-y_begin), kleur);
				}
			}
			else
			{
				if (x_offset < 0)
				{
					start_point = y_eind;
					end_point = y_begin;
				}
				else
				{
					start_point = y_begin;
					end_point = y_eind;
				}
				for (i = start_point; i < end_point; i++)
				{
					line_var = x_begin - round((1/fabs(derivative)) * (i - y_begin));
#ifdef DEBUG_LINE_VAR
					printf("lijn variable : \t %d\n", line_var);
#endif
					UB_VGA_SetPixel(line_var, y_begin + (i-y_begin), kleur);
				}
			}
		}
		else
		{
			if (derivative > 0)
			{
				if (x_offset < 0)
				{
					start_point = x_begin;
					end_point = x_eind;
				}
				else
				{
					start_point = x_eind;
					end_point = x_begin;
				}
				for (i = start_point; i < end_point; i++)
				{
					line_var = round(derivative * (i - x_begin)) + y_begin;
#ifdef DEBUG_LINE_VAR
					printf("lijn variable : \t %d\n", line_var);
#endif
					UB_VGA_SetPixel(x_begin+(i-x_begin), line_var, kleur);
				}
			}
			else
			{
				if (x_offset < 0)
				{
					start_point = x_begin;
					end_point = x_eind;
				}
				else
				{
					start_point = x_eind;
					end_point = x_begin;
				}
				for (i = start_point; i < end_point; i++)
				{
					line_var = y_begin + round(fabs(derivative)*(i-x_eind));
#ifdef DEBUG_LINE_VAR
					printf("lijn variable : \t %d\n", line_var);
#endif
					UB_VGA_SetPixel(x_eind-(i-x_begin), line_var, kleur);
				}
			}
		}
	}
}

void drawLines(uint16_t x_begin, uint16_t y_begin, uint16_t x_eind, uint16_t y_eind, uint8_t kleur, uint8_t lijn_dikte)
{
	uint8_t i = 0; uint8_t lijnwaarde = 0; float derivative = 0.0;
	lijnwaarde = lijn_dikte / 2; // Since the function wants to put original x and y coordinates as the middle line.
	derivative = (float)(y_begin - y_eind) / (float)(x_begin - x_eind); // Needed to know whether the line multiplication is in x or y axis.
#ifdef DEBUG_LIJN_DIKTE
		printf("waarde lijn dikte is %d\n", lijn_dikte);
		printf("waarde lijnwaarde is %d\n", lijnwaarde);
#endif
	if(lijn_dikte==1) myLijntekenaar(x_begin, y_begin, x_eind, y_eind,kleur);// If line width is just one, the function does not need to loop the line function.
	else
	{
		for (i = 0; i < lijn_dikte; i++)
		{ // The derivative defines whether the line multiplication is in x or y axis.
			if (fabs(derivative) > 1) myLijntekenaar(x_begin + (-lijnwaarde + i), y_begin, x_eind + (-lijnwaarde + i), y_eind,kleur);
			else myLijntekenaar(x_begin, y_begin + (-lijnwaarde + i), x_eind, y_eind + (-lijnwaarde + i),kleur);
		}
	}
}

void drawRect(uint16_t x_pos, uint16_t y_pos, uint16_t length, uint16_t width, uint8_t kleur, uint8_t filled)
{
	uint8_t i = 0;
	if (filled == 0) // If the rectangle does not need to be filled
	{
#ifdef DEBUG_RECT_BOUNDS
		printf("x-begin: \t %d \n x-eind: \t %d ", x_pos, x_pos + length-1);
		printf("y-begin: \t %d \n y-eind: \t %d ", y_pos,y_pos+(width-1));
#endif
		for (i = 0; i <= 1; i ++)
		{
			myLijntekenaar(x_pos, y_pos+(width-1)*i, x_pos + length-1, y_pos+(width-1)*i, kleur); // Draws a horizontal line.
			myLijntekenaar(x_pos + (length -1) * i, y_pos, x_pos + (length-1 ) * i,y_pos+width-1, kleur); //Draws a Vertical line.
		}
	}
	else
	{
		for (i = y_pos; i < width +y_pos; i++) // Loops around the y axis
			myLijntekenaar(x_pos, i, x_pos + length-1, i, kleur); // Draws around the x axis
	}
}

void drawCircle(uint16_t x_pos, uint16_t y_pos, uint8_t radius, uint8_t kleur)
{
	float i=0; // Float because it hold division of PI which are decimal numbers.
	uint16_t plaats_x = 0, plaats_y = 0;
	for (i = 0; i < (2 * M_PI); i += (M_PI/RADIUS_INCREMENT_CIRCLE))
	{   // Needs an addition because the original formula makes a circle start at point (0,0)
		plaats_x = (VGA_DISPLAY_X/2) + round(radius * cos(i)); // X = r*cosine(θ)
		plaats_y = (VGA_DISPLAY_Y/2) + round(radius * sin(i));  // Y = r*sine(θ)
#ifdef DEBUG_CIRCLE_PLAATS
		if(i=M_PI) printf("plaats x is \t %d \n plaats y is \t %d",plaats_x, plaats_y);
#endif
		UB_VGA_SetPixel(plaats_x, plaats_y, kleur);
	}
}

void drawFigure(uint8_t kleur, uint8_t nr_pointsgiven,...)
{
	uint8_t i = 0;
	int figure_ram_x[nr_pointsgiven]; // Array where the loop can easily find the x coordinates
	int figure_ram_y[nr_pointsgiven]; // Array where the loop can easily find the y coordinates
	va_list argumenten;

	memset(figure_ram_x, 0, nr_pointsgiven+1); // Filled array with 0
	memset(figure_ram_y, 0, nr_pointsgiven+1);

	va_start (argumenten, nr_pointsgiven); // All arguments after nr_pointsgiven are saved in va_list argumenten.
	for (i = 0; i < nr_pointsgiven*2; i++)
	{
		if (i % 2 != 0) figure_ram_y[(i / 2)] = va_arg(argumenten, int); // Every odd number of coordinate arguments are saved in the y array
		else figure_ram_x[(i / 2)] = va_arg(argumenten, int); // The even number of arguments of coordinate are saved to x array
	}
	va_end(argumenten); // To clean up va_list argumenten.
#ifdef DEBUG_FIGURE_COR
	for (i = 0; i < nr_pointsgiven; i++)
	{
		printf("X \t %d", figure_ram_x[i]);
		puts("");
	}
	for (i = 0; i < nr_pointsgiven; i++)
	{
		printf(" Y \t %d", figure_ram_y[i]);
		puts("");
	}
#endif
	for (i = 0; i < nr_pointsgiven-1; i++)
		myLijntekenaar(figure_ram_x[i], figure_ram_y[i], figure_ram_x[i+1], figure_ram_y[i+1], kleur); // Draws a line with coordinates from the array's
}
