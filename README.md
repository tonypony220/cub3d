# cub3d
Textured 2D raycaster with sprites, map validator, screenshots.
It uses miniLibX (OpenGL) to display and a tiny amount of linux functions (restrictions of school task)
 
Idea of project is to create a “realistic” 3D graphical
representation of the inside of a maze from a
first-person perspective using the Ray-Casting principles (like in Wolfenshtein 3d). 

All calculations are slow because only CPU cast each ray wtih simple DDA algorithm.
Image adopting for screen size, which you could set. 
There are map, which you could change, but it should be valid, otherwise you will got an error. Letters (NSWE) are shortcuts for directions. 
Also you colud adjust the color of floor(F) and ceil(C). And to change texture just upload it to project and set in config. 
And it's possible to make screenshot and get handmade BMP file! :)

If you do the same project and wonder why it moves so smooth - see the answer in code of events with keyboard. 
To make it display faster used simple buffering (like buffering slow write/read operation).

to run `./cub3D map.cub`
second argument is file with settings 
