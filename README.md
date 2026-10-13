# so_long

A small top-down 2D game in C on MiniLibX (X11): collect every coin, then reach the exit. Maps are loaded from `.ber` files and validated with a flood fill. The bonus build adds zombies that chase the player.

**Stack:** C · MiniLibX · X11 · Make    **Context:** 42 Berlin curriculum

---

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Build](#build)
- [Usage](#usage)
- [Map Format](#map-format)
- [How It Works](#how-it-works)
- [Bonus: Zombies](#bonus-zombies)
- [Project Structure](#project-structure)

---

## Overview
The game reads a map file, checks that it is playable, opens a window sized to the map (32x32 px per tile) and draws it from XPM textures. The player moves one tile per key press; walls block movement, coins are picked up by walking over them, and the exit only ends the game once every coin has been collected. Rendering is incremental: after the first full draw, each move redraws only the tiles that changed.

## Features
- Movement with `W` `A` `S` `D`; the player sprite turns to face the direction of the last key
- Move counter printed to the shell and drawn at the bottom of the window
- Exit unlocks when all coins are collected
- `ESC` or closing the window quits and frees all images, the window and the display
- Map validation: `.ber` extension, rectangular, closed by walls, exactly one player and one exit, at least one coin, every coin and the exit reachable
- Any invalid input prints `Error` / `Invalid map` and exits with a failure status

## Requirements
- Linux with X11 (the Makefile links `-lXext -lX11 -lm -lz`), including the X11 and zlib development headers
- `cc`, Make and `git`
- MiniLibX: not vendored; the Makefile clones [42Paris/minilibx-linux](https://github.com/42Paris/minilibx-linux) into `mlx_linux/` on the first build

## Build
```sh
make          # clones and configures MiniLibX if needed, builds libft, then ./so_long
make bonus    # same, with the zombie version, also built as ./so_long
make clean    # remove object files (and libft objects)
make fclean   # also remove ./so_long, libft.a and the mlx_linux/ clone
make re       # fclean + all
```

Sources are compiled with `-Wall -Wextra -Werror -O3`; the binary is linked with `-fsanitize=address -g`.

## Usage
Run from the repository root (textures are loaded from `textures/` by relative path):
```sh
./so_long maps/map.ber
```

## Map Format
- Map files must have a `.ber` extension and at least three rows
- Allowed characters:
  - `0`: Empty space
  - `1`: Wall
  - `C`: Collectible
  - `E`: Exit
  - `P`: Player start
  - `Z`: Zombie (bonus build only)
- Map must be rectangular, surrounded by walls, with exactly one exit, one player, and at least one collectible.
- Example:
  ```
  11111
  1P0C1
  100E1
  11111
  ```

## How It Works
- **Loading:** the file is read once to measure it, then read again into a single buffer and split on newlines into a `char **` grid.
- **Validation:** after the shape, border and character-count checks, a recursive flood fill starts at `P`. It marks every reached tile by switching it to lowercase (`0`->`o`, `C`->`c`, `E`->`e`, `P`->`p`) and counts the coins it reaches. The map is accepted only if the exit was reached and the reached coin count equals the total. The lowercase markers are then reused as the in-game state of the grid.
- **Input:** `mlx_key_hook` dispatches X11 key codes to `mv_up` / `mv_down` / `mv_left` / `mv_right`; the window close event (17) is hooked to the same cleanup function as `ESC`.
- **Drawing:** each move draws the floor under the old position, the item that was there, and the player sprite for the current direction at the new position. Only the move counter text is redrawn at the bottom.

## Bonus: Zombies
Built with `make bonus`. Zombies are placed on the map with `Z`.
- After every player move, each zombie takes one step: toward the player if the player is on an adjacent tile, otherwise onto the first free floor tile it finds (up, down, left, right).
- Walking into a zombie, or a zombie stepping onto the player, ends the game.
- Zombies alternate between `z` and `Z` in the grid each turn so a single scan never moves the same zombie twice.

## Project Structure
```
includes/        # so_long.h, so_long_bonus.h
libft/           # my libft (with ft_printf and get_next_line), built as libft.a
maps/            # example map
srcs/            # mandatory game: main, input_check, hooks, render, utils
srcs_bonus/      # bonus game with zombies
textures/        # 32x32 XPM sprites (walls, floor, coin, exit, player in 4 directions, zombie)
Makefile         # build rules; fetches MiniLibX into mlx_linux/
```

---

42 Berlin project by Nam Lap Vu ([42navalkrinzhaslattt](https://github.com/42navalkrinzhaslattt)).
