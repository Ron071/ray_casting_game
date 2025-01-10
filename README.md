Raycasting Maze Game.    in progress 

This project is a raycasting-based maze game developed in C++ using the SFML library. It features an efficient raycasting algorithm implemented with trigonometry, dynamic maze generation, and multithreading using pthreads to enhance performance and responsiveness.

Features

Raycasting:
Efficient implementation using trigonometric calculations.
Simulates a 3D perspective view for an immersive gaming experience.
Multithreading:
Raycasting calculations are divided into multiple threads using pthreads.
Each thread handles a portion of the rays, improving the rendering performance.
Dynamic Maze Generation:
The maze is dynamically generated using a custom algorithm, ensuring solvable paths.
Pathways in the maze are formed either by moving right or down from each cell.
Player Interaction:
Keyboard controls allow the player to navigate the maze.
Collision detection prevents the player from moving through walls
