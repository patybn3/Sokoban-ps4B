# PS2a: Sokoban

## Contact
Name: Patricia Antlitz
Section: 202
Time to Complete: Please take into consideration I didnt have a running machine for 3 days


## Description
The program is a simple implementation of the Sokoban game using the SFML library on C++. Sokoban is a puzzle game where the player, represented by a character, must push boxes onto a storage locations. The player can move in four cardinal directions, and the goal is to place all boxes on the designated storage locations. The players can move in four cardinal directions, and the goal is to place all boxes on the designated storage locations to win the game. The game features different textures for walls, empty spaces, boxes, and the player, creating a visual representation of the game board.

### Features
- Grid Representation = The game board is represented by a two-dimensional matrix grid, where each character corresponds to a specific element (image).
- Player movement = The player can move to the right, left, up and down and the image of the player follows the direction.
- Box pushing: The player can push boxes on all directions and from all directions with the exception to when there is a wall on the way.
- Storage areas: certain locations on the grid act as storage areas
- Victory: The game is won is all boxes are pushed onto a storage space

### Memory
The project uses a two-dimensional grid to store the game board, and the level data is represented by characters within this grid. The grid is implemented as a vector of vectors, providing a flexible data structure for managing the level layout. In this implementation, smart pointers are not used; instead, standard data structures, such vectors, are employed to manipulate and manage the game data.

### Lambdas
I decided to not use lambda function.

### Issues
Player movement:
Initially the player movement was not updating the grid correctly, leading to unexpected behavior when pushing boxes. The updatePOsition() and movePlayer() methods were modified to correctly handle box pushing, ensuring that the grid reflects the updated positions of the player and boxes according to the Sokoban game rules.

Storage Image:
The storage image was being replaced by a background image when a box was moved out of it. 

Winning conditions:
- Premature winning messages were being displayed for a while
- points were not correctly calculated


### Extra Credit
Points calculation:
Points are set to 50 as the max amount of points a player can get per level. There is a timer on the right bottom part of the screen counting the seconds. The points decrease by one point per second the player takes to finish the game. If points is less or equal to 0, points is set to be equal to 1. So the min amount of points is 1, and the max is 50 per level. I changed the background color of the screen to match the background.

I created a file names level7.lvl

The reset method resets the board, the timer, and the points

I like this program, I plan to continue implementing. I plan to allow the user to select the level from a menu, undo, go back, jump a level, continue to the next level and accumulate the points.

## Acknowledgements
class' materials and videos
