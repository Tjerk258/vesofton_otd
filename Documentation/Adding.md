@page Adding Adding fonts and bitmap to code
@tableofcontents
On this page we will discuss how different fonts and bitmaps can be added to the code.  


@section Bitmap
To add a bitmap to the code follow the following steps.  
1. Add bitmap array into bitmap.h
2. change the first byte to the height of the picture
3. change the second and third byte to the width of the picture whereby the second byte is the higher byte and the third byte is the lower byte.
4. At the buttom of bitmap.h change the array and add the name of bitmap.  
5. You have succesfully added a bitmap to the code.

@section Fonts
To add a font to the code follow the following steps.  
Credit of the script for font generation is going to https://github.com/jdmorise.

1. create a font with the python script included in the repository.
    1. run the python script in folder Font generator\TTF2BMH-master\src\ttf2bmh.py with the following arguments

            python3 .\ttf2bmh.py --ascii --font <font> --variable_width -s <Hight in pixels> --square

    and generate the font to your likings in normal, Bold and italic in 8px height and 32px height.
2. add the files to /Core/Inc/fonts.
3. In API.h increase the value of FONT_NUMBER with 1.
4. In API.c include al the font files
5. In API.c in the function drawText() add to the variable **fonts[] the differnt fonts in the same order as the previous fonts.
6. In API.c in the function drawText() add to the variable font_name the font name you added to be called by the script.
7. You now have succesfully added a font to the code.
    