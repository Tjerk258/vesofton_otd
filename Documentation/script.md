@page Script Script turtorial
@tableofcontents
In this explanation all the scripts will be explained what they can do.  


@section Line
With this script command a line can be printed on the screen.  
The syntax for this script is:  

    lijn, x1, y1, x2, y2, kleur, dikte, middelijn

- **x1:** This is the x of the first coordinate.  
- **y1:** This is the y of the first coordinate.  
- **x2:** This is the x of the second coordinate.  
- **y2:** This is the y of the second coordinate.  
- **kleur:** This is the color of the line to be draw. see @ref color for the differnt colors to be used.  
- **dikte:** This is the width of the line in pixels.  
- **middelijn:** If middelijn is equal to one,the function draws a black line with the original coordinates.  



@section Rectangle
With this script command a rectangle can be printed on the screen.  
The syntax for this script is:  

    rechthoek, x_lup, y_lup, breedte, hoogte, kleur, gevuld, rand, randkleur

- **x_up:** This is the x coordinate of the left upper cornor.  
- **y_up:** This is the x coordinate of the left upper cornor.  
- **breedte:** This is the width of the rectangle in pixels.  
- **hoogte:** This is the height of the rectangle in pixels.  
- **kleur:** This is the color of the line to be draw. see @ref color for the differnt colors to be used.  
- **gevuld:** This is for filling the rectangle.  
    - 0 for not filled.
    - 1 for filled.
- **rand:** this is if a border around the rectangle will be drone.
    - 0 for no border.
    - 1 for a border
- **randkleur:** this is the border color. see @ref color for the differnt colors to be used.  



@section Text
With this script command a piece of text can be printed on the screen.  
The syntax for this script is:  

    tekst, x, y, kleur, tekst, fontnaam, fontgrootte, fontstijl, space, linefeed

- **x:** This is the x coordinate of the left upper cornor.  
- **y:** This is the x coordinate of the left upper cornor.    
- **kleur:** This is the color of the line to be draw. see @ref color for the differnt colors to be used.  
- **tekst:** This is the text that will be printed on the screen. If a comma needs te be printed a backslash can be put before it to prevent it to be seen als script delimitter. If tekst ends with a backslash be sure to put a space between the backslash and de comma delimitter to prevent it to be printed on the screen. 
- **fontnaam:** This is the name of the font to be used. Available are:  
    - arial.  
    - consolas.  
- **fontgrootte:** This is the size of the fonts. Available are:  
    - 1 for 8px.  
    - 2 for 32px.  
- **fontstijl:** This is for filling the rectangle. Available are:  
    - "normaal" for normal.
    - "vet" for bold.
    - "cursief" for Italic.
- **space:** This is the space between the characters in pixels.
- **linefeed:** This is if you would like to go to the next line if the charchters go out of het screen.
    - 0 for not next line.
    - 1 for next line.    

@section Bitmap
With this script command a bitmap can be printed on the screen.  
The syntax for this script is:  

    bitmap, nr, x-lup, y-lup

- **nr:** This is the number of the bitmap to be used. Standard available are:  
| Number | Bitmap         |
|--------|----------------|
| 0      | Smiley         |
| 1      | Angry smiley   |
| 2      | Arrow left     |
| 3      | Arrow right    |
| 4      | Arrow up       |
| 5      | Arrow down     |
| 6      | Smiley 2       |
| 7      | Angry smiley 2 |
| 8      | Arrow right 2  |
- **x-1up:** This is the x coordinate of the left upper cornor.  
- **y-1up:** This is the x coordinate of the left upper cornor.  .  

@section Clearscreen
With this script command the screen can be cleared.   
The syntax for this script is:  

    clearscherm, kleur

- **kleur:** This is the color of the line to be draw. see @ref color for the differnt colors to be used.  

@section Wait
With the script a specific time to wait can be inplemented  
The syntax for this script is:  

    wacht, msecs

- **msecs:** Time to wait in miliseconds.  

@section Repeat
With the script a specific number of scripts can be repeated.  
The syntax for this script is:  

    herhaal, aantal, hoevaak, richting

- **aantal:** This is the number of scripts to be repeated.  
- **hoevaak:** This is how may times the scripts have to be repeated.  
- **richting:** This is in wich order the scripts should be repeated.
    - 0 for normal order.
    - 1 for turned order.


@section Circleplus
With the script a specific circle can be printed.  
The syntax for this script is: 

    cirkel2, x, y, laagradius, hoogradius, laagangle, hoogangle, kleur

- **x:** This is the x coordinate of the middlepoint.   
- **y:** This is the y coordinate of the middlepoint.   
- **laagradius:** This is the Lower boundary radius of the circle.  
- **hoogradius:** This is the higher boundary radius of the circle.
- **laagangle:** This is the Lower boundary anlge of the circle.  
- **hoogangle:** This is the higher boundary angle of the circle.
- **kleur:** This is the color of the line to be draw. see @ref color for the differnt colors to be used.    

@section Circle
With the script a specific circle can be printed.  
The syntax for this script is:  

    cirkel, x, y, radius, kleur, lradius

- **x:** This is the x coordinate of the middlepoint.   
- **y:** This is the y coordinate of the middlepoint.   
- **radius:** This is the radius of the circle.  
- **kleur:** This is the color of the line to be draw. see @ref color for the differnt colors to be used.  
- **lradius:**  This is the lower boundary radius of the circle.  

@section Figure
With the script a specific figure can be printed on the screen.  
The syntax for this script is:  

    figuur, x1,y1, x2,y2, x3,y3, x4,y4, x5,y5, kleur, dikte

- **x1:** the x of the first coordinate.  
- **y1:** the y of the first coordinate.  
- **y2:** the y of the second coordinate.  
- **x2:** the x of the second coordinate.  
- **x3:** the x of the third coordinate.  
- **y3:** the y of the third coordinate.  
- **x4:** the x of the fourth coordinate.  
- **y4:** the y of the fourth coordinate.  
- **x5:** the x of the fifth coordinate.  
- **y5:** the y of the fifth coordinate.  
- **kleur:** This is the color of the line to be draw. see @ref color for the differnt colors to be used.  
- **dikte:** This is the width of the line in pixels.  


@section color Colors
In this section al the availible colors are listed and witch string needs to be added to the script.  
| Color         | Script string |
|---------------|---------------|
| Black         | zwart         |
| Blue          | blauw         |
| Light blue    | lichtblauw    |
| Green         | groen         |
| Light green   | lichtgroen    |
| Red           | rood          |
| Light Red     | lichtrood     |
| White         | wit           |
| Cyan          | cyaan         |
| Light cyan    | lichtcyaan    |
| Magenta       | magenta       |
| Light magenta | lichtmagenta  |
| Brown         | bruin         |
| Yellow        | geel          |
| Gray          | grijs         |
| Pink          | roze    |
| Violet        | paars         |
