# FlappyBird
Flappy Bird Clone, made in C++ and QT.

This is my attempt at the very popular Flappy Bird Game, made with QT and C++. The bird traverses through a random arrangement of pipes, increasing the score as it goes until it collides with one of them or falls off the screen. Mouse clicks provide the "boost" for the bird to briefly gain altitude.

The flapping motion of the bird is simulated by switching through three images of it, where the wings are in various states, top, middle and bottom and by using a timer with sufficient intervals we can make it appear to flap. On top of this I've added two animations, one to simulate gravity to pull the bird downward and another to rotate its orientation as it falls. Both are implemented using a Quad easing curve so that their effects are applied smoothly. The brief uplift provided to the bird through the mouse click is also an animation that raises its orientation upward and propels it up the Y axis.

The Pipe(s) are actually a single pipe image where I have taken one and placed it in the lower half of the window and the other in the upper half of the window and then grouped them as a single object with a gap in between them that I thought was sufficient for the gameplay. They spawn at regular intervals and traverse the screen. Once off screen they automatically destroy themselves and thereby avoid any memory leaks. Their height position is chosen through a random number generator so that the game is different with every run.

Collision occurs when the bird makes contact with the pipe group. Otherwise if the bird finds itself past the pipes then the score (upper left) is incremented. Finally to provide a parallax effect I added a Gif animation in the background to simulate a moving sky. This was an image which I found and brought into Photoshop so that I could transition the front and end frames to produce a gif with a relatively slowly moving background.

https://user-images.githubusercontent.com/111576658/201320975-99ae403c-8140-4255-9d2b-8cc6f6758e74.mp4

