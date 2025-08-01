# so_long

## So Long And Thanks for All the Fish!

A small 2D game project for 42 School, written in C, using the MiniLibX graphics library. The goal is to collect all collectibles and escape the map, practicing window management, event handling, textures, and basic gameplay logic.

---

## Table of Contents
- [Foreword](#foreword)
- [Objectives](#objectives)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Map Format](#map-format)
- [Bonus Features](#bonus-features)
- [Project Structure](#project-structure)
- [License](#license)

---

## Foreword
This project is an introduction to 2D game development using C and the MiniLibX library. You will work with textures, sprites, and basic gameplay elements. The assets can be customized, but must respect copyright.

## Objectives
- Practice window management, event handling, and graphics in C
- Use the MiniLibX library
- Implement a simple 2D game with collectibles and an exit
- Ensure code follows the 42 Norm and is memory-safe

## Features
- 2D top-down or profile view
- Player moves with W, A, S, D (or arrow keys/ZQSD)
- Collect all collectibles to unlock the exit
- Walls block movement
- Movement count displayed in the shell (bonus: on screen)
- Clean exit on ESC or window close
- Map validation (rectangular, surrounded by walls, valid path, etc.)

## Requirements
- C compiler (cc)
- MiniLibX (provided or install from source)
- Make
- macOS or Linux

## Installation
1. Clone the repository:
   ```sh
   git clone <your-repo-url>
   cd so_long
   ```
2. Build the project:
   ```sh
   make
   ```
   For bonus features:
   ```sh
   make bonus
   ```

## Usage
Run the game with a valid map file:
```sh
./so_long maps/map.ber
```

## Map Format
- Map files must have a `.ber` extension
- Allowed characters:
  - `0`: Empty space
  - `1`: Wall
  - `C`: Collectible
  - `E`: Exit
  - `P`: Player start
- Map must be rectangular, surrounded by walls, with exactly one exit, one player, and at least one collectible.
- Example:
  ```
  11111
  1P0C1
  100E1
  11111
  ```

## Bonus Features
- Enemies: player loses if touching a patrol
- Sprite animation
- Movement count displayed on screen

## Project Structure
```
includes/        # Header files
libft/           # Custom libft library
maps/            # Example map files
mlx_linux/       # MiniLibX (if needed)
srcs/            # Main source files
srcs_bonus/      # Bonus source files
textures/        # XPM texture files
Makefile         # Build rules
```

## License
This project is for educational purposes at 42 School.

---

**So Long, and thanks for all the fish!**
