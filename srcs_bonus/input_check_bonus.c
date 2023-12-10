/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:42:59 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/10 16:42:59 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	get_characters(char **map, int *characters, t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if (map[i][j] == 'P')
			{
				game->player.y = i;
				game->player.x = j;
				(*characters)++;
			}
			else if (map[i][j] == 'E')
				(*(characters + 1))++;
			else if (map[i][j] == 'C')
				(*(characters + 2))++;
			else if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'Z')
				return (0);
		}
	}
	return (1);
}

void	flood_fill(int y, int x, t_game *game, int *exit_flag)
{
	if (game->map[y][x] == '1' || game->map[y][x] == 'e'
		|| game->map[y][x] == 'c' || game->map[y][x] == 'o'
		|| game->map[y][x] == 'p' || game->map[y][x] == 'z')
		return ;
	if (game->map[y][x] == 'E')
	{
		game->map[y][x] = 'e';
		*exit_flag = 1;
	}
	if (game->map[y][x] == 'C')
	{
		game->coins++;
		game->map[y][x] = 'c';
	}
	if (game->map[y][x] == '0')
		game->map[y][x] = 'o';
	if (game->map[y][x] == 'P' || game->map[y][x] == 'Z')
		game->map[y][x] += 32;
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
	flood_fill(game->player.y, game->player.x, game, &exit_flag);
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
		if ((int)ft_strlen(map[i]) != game->map_width || map[i][0] != '1'
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
		|| characters[0] != 1 || characters[1] != 1 || characters[2] < 1)
		return (0);
	return (characters[2] == flood_fill_check(game));
}

int	input_check(char *filename, t_game *game)
{
	int		len;
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
	return (1);
}
