@page Script Script turtorial
@tableofcontents
In this explanation all the scripts will be explained what they can do.  


@section Line
With this script command a line can be printed on the screen.  
The syntax for this scirpt is:  

    lijn, x1, y1, x2, y2, kleur, dikte, middelijn

- **x1:** This is the x of the first coöridnate.  
- **y1:** This is the y of the first coöridnate.  
- **x2:** This is the x of the second coöridnate.  
- **y2:** This is the y of the second coöridnate.  
- **kleur:** This is the color of the line to be draw. see @ref color for the differnt colors to be used.  
- **dikte:** This is the width of the line in pixels.  
- **middelijn:** ***???????????????????????????????????***. 



@section Rectangle
With this script command a rectangle can be printed on the screen.  
The syntax for this scirpt is:  

    rechthoek, x_lup, y_lup, breedte, hoogte, kleur, gevuld, rand, randkleur

- **x_up:** This is the x coördinate of the left upper cornor.  
- **y_up:** This is the x coördinate of the left upper cornor.  
- **breedte:** This is the width of the rectangle in pixels.  
- **hoogte:** This is the height of the rectangle in pixels.  
- **kleur:** This is the color of the line to be draw. see @ref color for the differnt colors to be used.  
- **gevuld:** This is for filling the rectangle.  
    - 0 for not filled.
    - 1 for filled.
- **rand:** ***?????????????????????????????????????????????***. 
- **randkleur:** ***????????????????????????????????????????***.



@section Text
With this script command a piece of text can be printed on the screen.  
The syntax for this scirpt is:  

    tekst, x, y, kleur, tekst, fontnaam, fontgrootte, fontstijl, ??

- **x:** This is the x coördinate of the left upper cornor.  
- **y:** This is the x coördinate of the left upper cornor.    
- **kleur:** This is the color of the line to be draw. see @ref color for the differnt colors to be used.  
- **tekst:** This is the text that will be printed on the screen. If a comma needs te be printed a backslash can be put before it to prevent it to be seen als script delimitter. If tekst ends with a backslash be sure to put a space between the backslash and de comma delimitter to prevent it to be printed on the screen. 
- **fontnaam:** This is the name of the font to be used. Standard available are:  
    - arial.  
    - consolas.  
- **fontgrootte:** This is the size of the fonts. Standard available are:  
    - 1 for 8px.  
    - 2 for 32px.  
- **fontstijl:** This is for filling the rectangle. Standard available are:  
    - "normaal" for normal.
    - "vet" for bold.
    - "cursief" for Italic.

@section Bitmap
With this script command a bitmap can be printed on the screen.  
The syntax for this scirpt is:  

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
- **x-1up:** This is the x coördinate of the left upper cornor.  
- **y-1up:** This is the x coördinate of the left upper cornor.  .  

@section Clearscreen
With this script command the screen can be cleared.   
The syntax for this scirpt is:  

    clearscherm, kleur

- **kleur:** This is the color of the line to be draw. see @ref color for the differnt colors to be used.  

@section Wait
With the script a specific time to wait can be inplemented  
The syntax for this scirpt is:  

    wacht, msecs

- **msecs:** This is the time to wait in miliseconds.  

@section Repeat
With the script a specific number of scirpts can be repeated.  
The syntax for this scirpt is:  

    herhaal, aantal, hoevaak, richting

- **aantal:** This is the number of scripts to be repeated.  
- **hoevaak:** This is how may times the scripts have to be repeated.  
- **richting:** This is in wich order the scripts should be repeated.
    - 0 for normal order.
    - 1 for turned order.

@section Circle
With the script a specific time to wait can be inplemented  
The syntax for this scirpt is:  

    cirkel, x, y, radius, kleur, lradius

- **x:** This is the x coördinate of the middlepoint.   
- **y:** This is the y coördinate of the middlepoint.   
- **radius:** This is the radius of the circle.  
- **kleur:** This is the color of the line to be draw. see @ref color for the differnt colors to be used.  
- **lradius:** ***?????????????????????????????????????????????????????????????***.

@section Figure
With the script a specific figure can be printed on the screen.  
The syntax for this scirpt is:  

    figuur, x1,y1, x2,y2, x3,y3, x4,y4, x5,y5, kleur, dikte

- **x1:** This is the x of the first coöridnate.  
- **y1:** This is the y of the first coöridnate.  
- **y2:** This is the y of the second coöridnate.  
- **x2:** This is the x of the second coöridnate.  
- **x3:** This is the x of the third coöridnate.  
- **y3:** This is the y of the third coöridnate.  
- **x4:** This is the x of the fourth coöridnate.  
- **y4:** This is the y of the fourth coöridnate.  
- **x5:** This is the x of the fifth coöridnate.  
- **y5:** This is the y of the fifth coöridnate.  
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
| Pink          | **roos??**    |
| Violet        | paars         |
