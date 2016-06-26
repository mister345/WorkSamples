This is a clone of the classic space shooter game 'Invaders,'
written from scratch in C# for the WPF platform. A real-time 
shooter game, the player scores points by destroying incoming 
alien invaders, and loses if the invaders collide with the player 
or reach the bottom of the screen.

This Application follows the model view viewmodel design pattern,
in which the game logic occurs in the model layer (written in C#), 
the display and binding logic happens in the view layer (written in
xaml), and the viewmodel is the pipeline that provides communication
between the two aforementioned layers. This allows for better
portability of the business logic, and better compartmentalization of
code overall.

Gregory Weiner
February 2013
