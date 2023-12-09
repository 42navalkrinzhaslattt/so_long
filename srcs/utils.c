/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:12:49 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/05 19:12:49 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_error(t_game *game)
{
	ft_printf("Error\nInvalid map\n");
	free_map(game->map);
	if (game->txt.w && game->mlx)
		mlx_destroy_image(game->mlx, game->txt.w);
	if (game->txt.f && game->mlx)
		mlx_destroy_image(game->mlx, game->txt.f);
	if (game->txt.c && game->mlx)
		mlx_destroy_image(game->mlx, game->txt.c);
	if (game->txt.e && game->mlx)
		mlx_destroy_image(game->mlx, game->txt.e);
	if (game->txt.u && game->mlx)
		mlx_destroy_image(game->mlx, game->txt.u);
	if (game->txt.d && game->mlx)
		mlx_destroy_image(game->mlx, game->txt.d);
	if (game->txt.l && game->mlx)
		mlx_destroy_image(game->mlx, game->txt.l);
	if (game->txt.r && game->mlx)
		mlx_destroy_image(game->mlx, game->txt.r);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
	exit(EXIT_FAILURE);
}

int	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
		free(map[i++]);
	free(map);
	return (0);
}

int	end_game(t_game *game)
{
	free_map(game->map);
	mlx_destroy_image(game->mlx, game->txt.w);
	mlx_destroy_image(game->mlx, game->txt.f);
	mlx_destroy_image(game->mlx, game->txt.c);
	mlx_destroy_image(game->mlx, game->txt.e);
	mlx_destroy_image(game->mlx, game->txt.u);
	mlx_destroy_image(game->mlx, game->txt.d);
	mlx_destroy_image(game->mlx, game->txt.l);
	mlx_destroy_image(game->mlx, game->txt.r);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
	exit(0);
}

void	print_moves(int *moves, t_game *game)
{
	char		*mv_str;

	ft_printf("Number of moves: %i\n", ++(*moves));
	mv_str = ft_itoa(*moves);
	if (!mv_str)
	{
		game->end_flag = 1;
		return ;
	}
	mlx_put_image_to_window(game->mlx,
		game->win, game->txt.w, 32 * 3, 32 * (game->map_height - 1));
	mlx_string_put(game->mlx, game->win,
		96, 31 * game->map_height, 0x00FFFFFF, mv_str);
	free(mv_str);
}

char	*parse_map(char *file)
{
	char		*res;
	char		buf[BUFF_SIZE + 1];
	int			fd;
	ssize_t		nbytes;
	ssize_t		size;

	fd = open(file, O_RDONLY);
	size = 0;
	nbytes = read(fd, buf, BUFF_SIZE);
	while (nbytes > 0)
	{
		size += nbytes;
		nbytes = read(fd, buf, BUFF_SIZE);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	res = (char *)malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	read(fd, res, size);
	res[size] = 0;
	close(fd);
	return (res);
}
