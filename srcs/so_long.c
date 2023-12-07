/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:09:43 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/05 19:09:43 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//#include "../includes/so_long.h"

int	init_textures(t_game *game)
{
	int	a;

	a = 32;
	game->txt.w = mlx_xpm_file_to_image(game->mlx, "textures/w.xpm", &a, &a);
	game->txt.f = mlx_xpm_file_to_image(game->mlx, "textures/f.xpm", &a, &a);
	game->txt.d = mlx_xpm_file_to_image(game->mlx, "textures/d.xpm", &a, &a);
	game->txt.l = mlx_xpm_file_to_image(game->mlx, "textures/l.xpm", &a, &a);
	game->txt.r = mlx_xpm_file_to_image(game->mlx, "textures/r.xpm", &a, &a);
	game->txt.u = mlx_xpm_file_to_image(game->mlx, "textures/u.xpm", &a, &a);
	game->txt.c = mlx_xpm_file_to_image(game->mlx, "textures/c.xpm", &a, &a);
	game->txt.e = mlx_xpm_file_to_image(game->mlx, "textures/e.xpm", &a, &a);
	if (!game->txt.w || !game->txt.f || !game->txt.d
		|| !game->txt.l || !game->txt.r || !game->txt.u
		|| !game->txt.c || !game->txt.e)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_game		game;

	if (ac != 2 || !input_check(av[1], &game))
		return (exit_error(&game));
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 32 * game.map_width,
			32 * game.map_height, "so_long");
	if (!init_textures(&game))
		return (exit_error(&game));
	game.player.orient = 'D';
	game.player.score = 0;
	game.player.moves = 0;
	game.end_flag = 0;
	render_map(&game);
	mlx_key_hook(game.win, key_hooks, &game);
	mlx_hook(game.win, 17, 1L << 2, end_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
