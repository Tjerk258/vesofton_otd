@mainpage VGA Graphics library
@tableofcontents

With this software you can easily print different types of graphics on a vga screen over UART.   

This software can generate a VGA signal of 240 x 320 pixels.

@section Flowchart
The beautiful flowchart.  

![Flowchart](images/Flowcharts_softon.jpg)

@section subscript Script usages
see @ref Script

@section subadding Adding fonts and bitmaps
see @ref Adding

@section Debugging
In different header files are some debug defines that are commanded out. By adding those debug defines in the code can be enabled or disabled.

@section Error Error handeling
If an error ocours the error will be printed over the uart and the error code will be printed over VGA on the screen.