lb-arduino-simon
================

http://littlebits.cc/projects/simon-clone

Combining the Arduino module and a few basic littleBits modules, I made a simple clone of the classic 1980s electronic game of Simon.

http://en.wikipedia.org/wiki/Simon_(game)

Simon was an electronic game of memory consisting of four buttons and four lights. The lights would illuminate in a pattern and the player would have to match the pattern by pressing the light's corresponding button in the correct order. The patterns would begin short and easy to remember and get longer and harder to remember with each successive round. Higher skill levels would show their patterns more quickly.

My version of Simon is simplified. It has three lights, three matching buttons and an Arduino module to control the game's logic. Upon power on, all lights will turn on to let you know the game is beginning. After all the lights flash, the game will show you the start of the pattern by illuminating a single LED momentarily. Now you have to press the matching button. If you pressed the correct button, the corresponding LED would illuminate and then you'd advance to the next round. The game will now show you a longer pattern. Throughout the game if you don't correctly follow the pattern and press the wrong button, the game will let you know by illuminating all three LEDs. It will then give you another chance by showing you the pattern again. After five rounds, the game is over and you are greeted with flashing, alternating LED lights.

Currently, the game is only 5 rounds though this can be changed easily in the Arduino sketch. The speed of the game can also be adjusted, but currently it is less easy to do so. If you have spare synth kit modules, you can add oscillators to the output of the RGB LEDs along with mix modules and a synth speaker to add sound to your game (see the third image or the accompanying video)!
