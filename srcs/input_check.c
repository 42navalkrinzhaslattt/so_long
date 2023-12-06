/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:16:35 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/05 19:16:35 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../includes/so_long.h"

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

int get_characters(char **map, int *characters, t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map_width)
	{
		j = -1;
		while (++j < game->map_height)
		{
			if (map[i][j] == 'P')
			{
				game->start_y = i;
				game->start_x = j;
				(*characters)++;
			}
			else if (map[i][j] == 'E')
				(*(characters + 1))++;
			else if (map[i][j] == 'C')
				(*(characters + 2))++;
			else if (map[i][j] != '1' && map[i][j] != '0')
				return (0);
		}
	}
	return (1);
}

void	flood_fill(int y, int x, t_game *game, int *exit_flag)
{
	if (game->map[y][x] == '1')
		return ;
	if (game->map[y][x] == 'E')
		*exit_flag = 1;
	if (game->map[y][x] == 'C')
	{
		game->coins++;
		game->map[y][x] = 'c';
	}
	flood_fill(y + 1, x, game, exit_flag);
	flood_fill(y - 1, x, game, exit_flag);
	flood_fill(y, x + 1, game, exit_flag);
	flood_fill(y, x - 1, game, exit_flag);
}

int	flood_fill_check(t_game *game)
{
	int	exit_flag;

	exit_flag = 0;
	game->coins = 0;
	flood_fill(game->start_y, game->start_x, game, &exit_flag);
	if (exit_flag != 1)
		return (-1);
	return (game->coins);
}

int	map_check(char **map, t_game *game)
{
	int			i;
	int			j;
	static int	characters[3];

	game->map_width = ft_strlen(map[0]);
	i = -1;
	while (map[++i])
	{
		if (ft_strlen(map[i]) != game->map_width || map[i][0] != '1'
			|| map[i][game->map_width - 1] != '1')
			return (0);
		if (i == 0 || !map[i + 1])
		{
			j = -1;
			while (map[i][++j])
				if (map[i][j] != '1')
					return (0);
		}
	}
	game->map_height = i;
	if (!get_characters(map, &characters[0], game)
		|| characters[0] != 1 || characters[1] != 1)
		return (0);
	return (characters[2] == flood_fill_check(game));
}

int	input_check(char *filename, t_game *game)
{
	int		len;
	int		i;
	char	*buf;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(&filename[len - 4], ".ber", 4))
		return (0);
	buf = parse_map(filename);
	game->map = ft_split(buf, '\n');
	if (buf)
		free(buf);
	if (!game->map || !game->map[0] || !game->map[1]
		|| !game->map[2] || !map_check(game->map, game))
		return (0);
}
