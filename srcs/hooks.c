/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:39:21 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/09 14:52:06 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mv_right(t_game *game)
{
	game->player.orient = 'R';
	if (game->map[game->player.y][game->player.x + 1] == '1')
		return (put_item(game->player.x, game->player.y, game, 'p'));
	if (game->map[game->player.y][game->player.x] != 'e')
		game->map[game->player.y][game->player.x] = 'o';
	put_item(game->player.x, game->player.y, game, 'o');
	put_item(game->player.x, game->player.y, game,
		game->map[game->player.y][game->player.x]);
	game->player.x++;
	if (game->map[game->player.y][game->player.x] == 'c'
		|| game->map[game->player.y][game->player.x] == 'o')
	{
		if (game->map[game->player.y][game->player.x] == 'c')
			game->player.score++;
		put_item(game->player.x, game->player.y, game, 'o');
	}
	put_item(game->player.x, game->player.y, game, 'p');
	if (game->map[game->player.y][game->player.x] == 'e'
		&& game->player.score == game->coins)
	{
		game->end_flag = 1;
		return ;
	}
	if (game->map[game->player.y][game->player.x] != 'e')
		game->map[game->player.y][game->player.x] = 'p';
}

void	mv_down(t_game *game)
{
	game->player.orient = 'D';
	if (game->map[game->player.y + 1][game->player.x] == '1')
		return (put_item(game->player.x, game->player.y, game, 'p'));
	if (game->map[game->player.y][game->player.x] != 'e')
		game->map[game->player.y][game->player.x] = 'o';
	put_item(game->player.x, game->player.y, game, 'o');
	put_item(game->player.x, game->player.y, game,
		game->map[game->player.y][game->player.x]);
	game->player.y++;
	if (game->map[game->player.y][game->player.x] == 'c'
		|| game->map[game->player.y][game->player.x] == 'o')
	{
		if (game->map[game->player.y][game->player.x] == 'c')
			game->player.score++;
		put_item(game->player.x, game->player.y, game, 'o');
	}
	put_item(game->player.x, game->player.y, game, 'p');
	if (game->map[game->player.y][game->player.x] == 'e'
		&& game->player.score == game->coins)
	{
		game->end_flag = 1;
		return ;
	}
	if (game->map[game->player.y][game->player.x] != 'e')
		game->map[game->player.y][game->player.x] = 'p';
}

void	mv_left(t_game *game)
{
	game->player.orient = 'L';
	if (game->map[game->player.y][game->player.x - 1] == '1')
		return (put_item(game->player.x, game->player.y, game, 'p'));
	if (game->map[game->player.y][game->player.x] != 'e')
		game->map[game->player.y][game->player.x] = 'o';
	put_item(game->player.x, game->player.y, game, 'o');
	put_item(game->player.x, game->player.y, game,
		game->map[game->player.y][game->player.x]);
	game->player.x--;
	if (game->map[game->player.y][game->player.x] == 'c'
		|| game->map[game->player.y][game->player.x] == 'o')
	{
		if (game->map[game->player.y][game->player.x] == 'c')
			game->player.score++;
		put_item(game->player.x, game->player.y, game, 'o');
	}
	put_item(game->player.x, game->player.y, game, 'p');
	if (game->map[game->player.y][game->player.x] == 'e'
		&& game->player.score == game->coins)
	{
		game->end_flag = 1;
		return ;
	}
	if (game->map[game->player.y][game->player.x] != 'e')
		game->map[game->player.y][game->player.x] = 'p';
}

void	mv_up(t_game *game)
{
	game->player.orient = 'U';
	if (game->map[game->player.y - 1][game->player.x] == '1')
		return (put_item(game->player.x, game->player.y, game, 'p'));
	if (game->map[game->player.y][game->player.x] != 'e')
		game->map[game->player.y][game->player.x] = 'o';
	put_item(game->player.x, game->player.y, game, 'o');
	put_item(game->player.x, game->player.y, game,
		game->map[game->player.y][game->player.x]);
	game->player.y--;
	if (game->map[game->player.y][game->player.x] == 'c'
		|| game->map[game->player.y][game->player.x] == 'o')
	{
		if (game->map[game->player.y][game->player.x] == 'c')
			game->player.score++;
		put_item(game->player.x, game->player.y, game, 'o');
	}
	put_item(game->player.x, game->player.y, game, 'p');
	if (game->map[game->player.y][game->player.x] == 'e'
		&& game->player.score == game->coins)
	{
		game->end_flag = 1;
		return ;
	}
	if (game->map[game->player.y][game->player.x] != 'e')
		game->map[game->player.y][game->player.x] = 'p';
}

int	key_hooks(int keycode, t_game *game)
{
	int			x_start;
	int			y_start;
	static int	moves;

	x_start = game->player.x;
	y_start = game->player.y;
	if (keycode == 119)
		mv_up(game);
	if (keycode == 97)
		mv_left(game);
	if (keycode == 115)
		mv_down(game);
	if (keycode == 100)
		mv_right(game);
	if (game->player.x != x_start || game->player.y != y_start)
		print_moves(&moves, game);
	if (keycode == 65307 || game->end_flag == 1)
		return (end_game(game));
	return (0);
}
