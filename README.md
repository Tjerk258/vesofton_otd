# VGA Driver and graphics library

With this software you can easily print different types of graphics on a vga screen over UART. 

## Usages

In this paragraph all the functions of the code will be discussed

### Comandos

The following script commandos can be send to the microcontroller to be executed.

>lijn, x, y, x’, y’, color, width
>rechthoek, x_lup, y_lup, width, heigth, color, filled
>tekst, x, y, color, text, fontname (arial, consolas), fontsize (1,2), fontstyle (normal, bold, cursive)
>bitmap, nr, x-lup, y-lup
>clearscherm, color
>wacht, msecs
>herhaal, aantal (laatst uitgevoerde commando’s), hoevaak (herhalen)
>cirkel, x, y, radius, kleur
>figuur, x1,y1, x2,y2, x3,y3, x4,y4, x5,y5, kleur

### Supported colors
-zwart  
-blauw  
-lichtblauw  
-groen  
-lichtgroen  
-cyaan  
-lichtcyaan  
-rood  
-lichtrood  
-magenta  
-lichtmagenta  
-bruin  
-geel  
-grijs  
-wit

### Bitmap numbers
0. Smiley
1. Angry simley
2. Arrow left
3. Arrow right
4. Arrow up
5. Arrow down
6. Smiley 2
7. Angry smiley 2

### max screen size
320*240

### error handeling
If a error ocurs the error code and what the error is will be printed over UART back to the user interface.

### Supported text types
There are a couple of fonts included in this code wich wil be discussed.
#### Fonts
>Arial
>Consolas

#### Font size
For font size there are two optionsto choose from
1. Normal
2. Big

#### Font Type
>Normal
>Italic
>Bold