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
//#include "../includes/so_long.h"

int	exit_error(t_game *game)
{
	perror("Error\nInvalid map\n");
	end_game(game);
	return (-1);
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
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
	exit(0);
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
