/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:43:05 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/10 16:43:05 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	put_item(int x, int y, t_game *game, char type)
{
	if (type == 'o')
		mlx_put_image_to_window(game->mlx,
			game->win, game->txt.f, 32 * x, 32 * y);
	if (type == 'c')
		mlx_put_image_to_window(game->mlx,
			game->win, game->txt.c, 32 * x, 32 * y);
	if (type == 'e')
		mlx_put_image_to_window(game->mlx,
			game->win, game->txt.e, 32 * x, 32 * y);
	if (type == 'u' || (type == 'p' && game->player.orient == 'U'))
		mlx_put_image_to_window(game->mlx,
			game->win, game->txt.u, 32 * x, 32 * y);
	if (type == 'l' || (type == 'p' && game->player.orient == 'L'))
		mlx_put_image_to_window(game->mlx,
			game->win, game->txt.l, 32 * x, 32 * y);
	if (type == 'r' || (type == 'p' && game->player.orient == 'R'))
		mlx_put_image_to_window(game->mlx,
			game->win, game->txt.r, 32 * x, 32 * y);
	if (type == 'd' || (type == 'p' && game->player.orient == 'D'))
		mlx_put_image_to_window(game->mlx,
			game->win, game->txt.d, 32 * x, 32 * y);
	if (type == 'z')
		mlx_put_image_to_window(game->mlx,
			game->win, game->txt.z, 32 * x, 32 * y);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx,
					game->win, game->txt.w, 32 * x, 32 * y);
			else
			{
				put_item(x, y, game, 'o');
				if (game->map[y][x] != '0' && game->map[y][x] != 'o')
					put_item(x, y, game, game->map[y][x]);
			}
		}
	}
	mlx_string_put(game->mlx, game->win, 0,
		31 * game->map_height, 0X00FFFFFF, "Number of moves:0");
}

void	check_zombie(t_game *game, int keycode, int x, int y)
{
	if ((keycode == 119 && (game->map[y - 1][x] == 'z'
			|| game->map[y - 1][x] == 'Z'))
		|| (keycode == 97 && (game->map[y][x - 1] == 'z'
		|| game->map[y][x - 1] == 'Z'))
		|| (keycode == 115 && (game->map[y + 1][x] == 'z'
		|| game->map[y + 1][x] == 'Z'))
		|| (keycode == 100 && (game->map[y][x + 1] == 'z'
		|| game->map[y][x + 1] == 'Z')))
	{
		put_item(game->player.x, game->player.y, game, 'o');
		if (keycode == 119)
			put_item(game->player.x, game->player.y - 1, game, 'u');
		if (keycode == 97)
			put_item(game->player.x, game->player.y + 1, game, 'd');
		if (keycode == 115)
			put_item(game->player.x - 1, game->player.y, game, 'l');
		if (keycode == 100)
			put_item(game->player.x + 1, game->player.y, game, 'r');
		end_game(game);
	}
}

void	mv_zombie(int x, int y, t_game *game)
{
	int	x_new;
	int	y_new;

	x_new = x;
	y_new = y;
	if (game->map[y - 1][x] == 'p' || game->map[y + 1][x] == 'p')
		y_new = y - (game->map[y - 1][x] == 'p') + (game->map[y + 1][x] == 'p');
	else if (game->map[y][x - 1] == 'p' || game->map[y][x + 1] == 'p')
		x_new = x - (game->map[y][x - 1] == 'p') + (game->map[y][x + 1] == 'p');
	else if (game->map[y - 1][x] == 'o')
		y_new = y - 1;
	else if (game->map[y + 1][x] == 'o')
		y_new = y + 1;
	else if (game->map[y][x - 1] == 'o')
		x_new = x - 1;
	else if (game->map[y][x + 1] == 'o')
		x_new = x + 1;
	put_item(x_new, y_new, game, 'z');
	if (game->map[y_new][x_new] == 'p')
		end_game(game);
	if (game->map[y][x] == 'z')
		game->map[y_new][x_new] = 'Z';
	else
		game->map[y_new][x_new] = 'z';
}

void	render_zombies(t_game *game)
{
	int			x;
	int			y;
	static int	flag;

	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			if ((game->map[y][x] == 'z' && flag % 2 == 0)
				|| (game->map[y][x] == 'Z' && flag % 2 == 1))
			{
				put_item(x, y, game, 'o');
				mv_zombie(x, y, game);
				game->map[y][x] = 'o';
			}
		}
	}
	flag++;
}
