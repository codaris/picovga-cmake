# PicoVGA Example Programs

## Ants
 Card game (sound). Two anthills compete for supremacy. The goal is to build a higher castle. Controls: J left, L right, space select card, D discard, H help, Q quit. Can be played against another player or against the computer.

<a href="../pages/img/ants.jpg"><img src="../pages/img/ants_m.jpg" border="0" width="250" height="188"></a> <a href="../pages/img/ants2.jpg"><img src="../pages/img/ants2_m.jpg" border="0" width="250" height="188"></a>

## Balloons

Demonstration of sprite use, flying balloons (43 sprites in total).

<a href="../pages/img/balloons.jpg"><img src="../pages/img/balloons_m.jpg" border="0" width="250" height="188"></a>

## Draw 
Demonstration of drawing graphic elements. For the demonstration, alternate between slow rendering and drawing at maximum speed.

<a href="../pages/img/draw.jpg"><img src="../pages/img/draw_m.jpg" border="0" width="250" height="188"></a>

## Earth 

Rotating globe. Software spherical image transformation.

<a href="../pages/img/earth.jpg"><img src="../pages/img/earth_m.jpg" border="0" width="250" height="188"></a>

## Eggs 
Logic game (sound). Based on the game Reversi. The goal is to get as many of your own stones as possible. One player changes stones in the direction of hen-chicken-egg, the other player in the opposite direction. Controls: L right, I up, J left, K down, H help, Q end, P 2 players, D demo, space bar to place stone, Enter ok. Can be played against another player and against the computer.

<a href="../pages/img/eggs.jpg"><img src="../pages/img/eggs_m.jpg" border="0" width="250" height="188"></a> <a href="../pages/img/eggs2.jpg"><img src="../pages/img/eggs2_m.jpg" border="0" width="250" height="188"></a>

## Fifteen 
Logic game (sound). The objective is to sort the stones in order from 1 to 15. Controls: L right, I up, J left, K down, Q new game.

<a href="../pages/img/fifteen.jpg"><font
        face="Arial"><img src="../pages/img/fifteen_m.jpg" border="0"
        width="250" height="188"></a>

## Flag 
Fluttering flag

<a href="../pages/img/flag.jpg"><font
        face="Arial"><img src="../pages/img/flag_m.jpg" border="0"
        width="250" height="188"></a>

## Ghost Racing 
Car racing (sound). After passing the first lap (checkpoints are required), a rival "ghost" appears, which copies your previous path. You are competing with yourself. There are a total of 2 ghost opponents in the game (the second one should appear after the second lap). The game is unfinished - I couldn't calculate the correct transformation of the opponents' image into the camera and it is now only very approximate. It's more of a half-finished game for inspiration and to demonstrate 3D terrain projection (tile areas). Controls: I gear up, K gear down, J left, L right. 5 gears can be shifted. Originally, reverse was possible, but it was rather hindering.

<a href="../pages/img/ghostracing.jpg"><img src="../pages/img/ghostracing_m.jpg" border="0" width="250" height="188"></a>

## Gingerbread House 
A fairy tale book about a gingerbread house. The program serves as a demonstration of working with images with RLE compression. Control: J previous page, L next page.

<a href="../pages/img/gingerhouse.jpg"><img src="../pages/img/gingerhouse_m.jpg" border="0" width="250" height="188"></a> <a href="../pages/img/gingerhouse2.jpg"><img src="../pages/img/gingerhouse2_m.jpg" border="0" width="250" height="188"></a>

## Hello World
The simplest example of using the PicoVGA library.

<a href="../pages/img/hello.jpg"><img src="../pages/img/hello_m.jpg" border="0" width="250" height="188"></a>

## Hypno 
A hypnotic rotating pattern. Example of matrix image transformation.

<a href="../pages/img/hypno.jpg"><img src="../pages/img/hypno_m.jpg" border="0" width="250" height="188"></a>

## Level Meter 
Music spectrum indicator simulation (sound). The program uses a gradient graph level display mode. The input for the display is an array of values. There is no need to generate the indicator image programmatically and so a very fast response to change can be achieved. Random samples are used in the demo.

<a href="../pages/img/levelmeter.jpg"><img src="../pages/img/levelmeter_m.jpg" border="0" width="250" height="188"></a>

## Life 
Cell life simulator (cellular automaton). Cells change at each step according to the number of neighboring cells: for 1 or less a cell dies on isolation, for 4 or more a cell dies on overpopulation, for 3 a new cell is created, for 2 there is no change. In the game, you can switch between 10 screens (slots) and transfer the image between them using the clipboard. In each slot there is a predefined definition of popular combinations. Controls: L right, I up, J left, K down, C copy to clipboard, V insert from clipboard, D clear area, space bar change cell, Enter start/stop generation, 0-9 select slot.

<a href="../pages/img/life.jpg"><img src="../pages/img/life_m.jpg" border="0" width="250" height="188"></a>
## Lines
Relaxation line pattern generator.

<a href="../pages/img/lines.jpg"><img src="../pages/img/lines_m.jpg" border="0" width="250" height="188"></a>

## Mandelbrot 
Fractal pattern generator of Mandelbrot set. Integer mathematics is used to generate the pattern, which makes the redrawing fast. However, it must be taken into account that as the scale of the display increases, increasing accuracy in the number of digits is required. The used integer and float mathematics are sufficient up to a magnification scale of 10^5, double mathematics up to a scale of 10^10. When zooming in further, only colored lines are displayed instead of the pattern. Controls: E up, S left, D right, X down, Q scale up, A scale down, L low resolution selection 132x100, M medium resolution selection 264x200, H high resolution selection 528x400, I switch to integer math (fastest, range up to 10^-5), F switching to float math (slowest, range up to 10^-5), B switching to double math (slowest, range up to 10^-10), O decreasing the number of iteration steps, P increasing the number of iteration steps, U increasing the system clock, T decreasing the system clock, space redraw screen.

<a href="../pages/img/mandelbrot.jpg"><img src="../pages/img/mandelbrot_m.jpg" border="0" width="250" height="188"></a> <a href="../pages/img/mandelbrot2.jpg"><img src="../pages/img/mandelbrot2_m.jpg" border="0" width="250" height="188"></a>

## Matrix Rain 
"Matrix code rain" simulation. It uses text-based video mode.

<a href="../pages/img/matrixrain.jpg"><img src="../pages/img/matrixrain_m.jpg" border="0" width="250" height="188"></a>

## Maze 
The goal is to find a way out of the maze. The mazes are generated randomly programmatically. Controls: J left, I up, L right, K down, H help (showing the door).

<a href="../pages/img/maze.jpg"><img src="../pages/img/maze_m.jpg" border="0" width="250" height="188"></a>

## Monoscope 
Video modes test. The keys 0 to 9 and A to U can be used to switch the display resolution, from 256x192 to 1280x960, for both VGA monitor and PAL/NTSC TV.For the TV, interlaced video is used for higher resolutions (such as broadcast TV), and progressive mode is used for lower resolutions (such as the outputs from 8-bit computers). Can be used to test the display on different devices. The individual test patterns are stored in the program as prepared images with RLE compression. It would be possible to modify the program to use only 1 image, which would be recomputed as needed, but would have to be compressed into RAM with RLE compression when generated, as it would not fit in RAM at full size.

<a href="../pages/img/monoscope.jpg"><img src="../pages/img/monoscope_m.jpg" border="0" width="250" height="188"></a> <a href="../pages/img/monoscope2.jpg"><img src="../pages/img/monoscope2_m.jpg" border="0" width="250" height="188"></a>

## Oscilloscope 
Demonstration of oscilloscope signal display. The program uses graph and curve display mode. The signal waveform image does not need to be generated in software, only the array of values is passed to the display, and this allows a very fast response to changing values. In the demo the samples are generated programmatically. It also serves as a demonstration of stacking image segments in different modes. The basic oscilloscope image is an 8-bit bitmap (with dithering), consisting of 4 stripes. In place of the screen, 2 elements are used to display graphs. The screen is overlaid by a transparent overlay with a grid.

<a href="../pages/img/oscilloscope.jpg"><img src="../pages/img/oscilloscope_m.jpg" border="0" width="250" height="188"></a>

## Pac-Man 
Popular action game (sound). The game attempts to emulate the original 1980's version of the game by Namco. The logic of ghost behavior, score and level counting is followed. I would like to point out that the sounds and appearance are taken from the original game, they are covered by Namco's copyright, and therefore the game serves only as an inspirational sample. Controls: J left, I up, L right, K down, A pause.

<a href="../pages/img/pacman.jpg"><img src="../pages/img/pacman_m.jpg" border="0" width="250" height="188"></a> <a href="../pages/img/pacman2.jpg"><img src="../pages/img/pacman2_m.jpg" border="0" width="250" height="188"></a>

## Pi 
Calculating the number Pi to 4833 digits. After the calculation, the result is checked against the expected sample.

<a href="../pages/img/pi.jpg"><img src="../pages/img/pi_m.jpg" border="0" width="250" height="188"></a>

## Pixels 
Random generation of colored pixels.

<a href="../pages/img/pixels.jpg"><img src="../pages/img/pixels_m.jpg" border="0" width="250" height="188"></a>

## Raytracing 
3D pattern generation by ray tracing method. Due to the limited color depth of PicoVGA, raster dithering ("graininess" of the image) is used in the display.

<a href="../pages/img/raytracing.jpg"><img src="../pages/img/raytracing_m.jpg" border="0" width="250" height="188"></a>

## Sokoban
Logic game (sound). The goal is to move the crates to the marked fields. The game contains 3000 levels from different authors, along with their solutions. Controls: L right, I up, J left, K down, H help (level solution), R restart level, Q previous level, W next level, P print info.

<a href="../pages/img/sokoban.jpg"><img src="../pages/img/sokoban_m.jpg" border="0" width="250" height="188"></a> <a href="../pages/img/sokoban2.jpg"><img src="../pages/img/sokoban2_m.jpg" border="0" width="250" height="188"></a>

## Spheres 
Random spheres generation.

<a href="../pages/img/spheres.jpg"><img src="../pages/img/spheres_m.jpg" border="0" width="250" height="188"></a>

## Spots 
Random generation of spots.

<a href="../pages/img/spots.jpg"><img src="../pages/img/spots_m.jpg" border="0" width="250" height="188"></a>

## Tetris 
Popular game, stacking blocks (sound). Control: L right, I turn, J left, K lay, A pause.

<a href="../pages/img/tetris.jpg"><img src="../pages/img/tetris_m.jpg" border="0" width="250" height="188"></a>

## Train 
Logic game based on the principle of the Snake (sound). The goal is to collect all objects and pass through the gate. The game has 50 levels, along with their solutions. Controls.: L right, I up, J left, K down, H help (view solution of the level), Enter enter password, Esc back, BS delete character of password.

<a href="../pages/img/train.jpg"><img src="../pages/img/train_m.jpg" border="0" width="250" height="188"></a> <a href="../pages/img/train2.jpg"><img src="../pages/img/train2_m.jpg" border="0" width="250" height="188"></a>

## Twister 
Twisting of the textured block. It serves as an example of programmatic image deformation, using a hardware interpolator.

<a href="../pages/img/twister.jpg"><img src="../pages/img/twister_m.jpg" border="0" width="250" height="188"></a>

## Water Surface
Simulation of rippling water surface (sound).

<a href="../pages/img/watersurface.jpg"><img src="../pages/img/watersurface_m.jpg" border="0" width="250" height="188"></a>