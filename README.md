# Musical Paddle

<a href="https://youtu.be/CesO73p4aDg"><img src="https://i.imgur.com/yYl3cS0.png" align="left" height="200px" alt="Musical Paddle" title="YouTube video of the musical paddle in action"></a>This program was built to turn my Kappa Kappa Psi (honorary band service fraternity) paddle into a music and lights show that would play our school's fight song, "Buckeye Battle Cry," using an Adafruit Trinket 5V (ATtiny85 @ 8MHz). The `MusicalPaddle.ino` file also contains code to play "Hang on Sloopy," but it was not used in the final project.

By Colin A. Williams (2018)

This project would not have been possible without the TrinketTone code by Bruce E. Hall, W8BH. 
*http://w8bh.net/avr/TrinketTone.pdf*

## Hardware used
- 1 Adafruit Trinket 5V
- 2 5mm Standard blue LEDs
- 1 5mm Standard white LED
- 1 Toggle switch push button
- 2 330Ω resistors between board and blue LEDs
- 1 1KΩ resistor between the board and the white LED
- 1 Passive buzzer
- 1 9V battery
- 1 9V battery snap connector
- Hook-up wire
- Solder

## Move pitches folder to your Sketchbook's libraries folder
In order for the `pitches.h` file to work, the `pitches` folder must me moved inside of your Sketchbook's `libraries` folder before compiling.

## Why didn't you use the built-in Arduino tone() method?
The normal Arduino `tone()` method does not work with the Adafruit Trinket, so [some TrinketTone code by Bruce E. Hall, W8BH](http://w8bh.net/avr/TrinketTone.pdf) that gives the same result with an Adafruit Trinket was used instead.
