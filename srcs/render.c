/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:05:44 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/07 18:05:44 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (type == 'p' && game->player.orient == 'U')
		mlx_put_image_to_window(game->mlx,
			game->win, game->txt.u, 32 * x, 32 * y);
	if (type == 'p' && game->player.orient == 'L')
		mlx_put_image_to_window(game->mlx,
			game->win, game->txt.l, 32 * x, 32 * y);
	if (type == 'p' && game->player.orient == 'R')
		mlx_put_image_to_window(game->mlx,
			game->win, game->txt.r, 32 * x, 32 * y);
	if (type == 'p' && game->player.orient == 'D')
		mlx_put_image_to_window(game->mlx,
			game->win, game->txt.d, 32 * x, 32 * y);
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
