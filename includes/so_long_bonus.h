/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:49:20 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/10 15:49:20 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# include <mlx.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"
# define BUFF_SIZE 100000

typedef struct s_textures
{
	void	*w;
	void	*c;
	void	*e;
	void	*d;
	void	*u;
	void	*r;
	void	*l;
	void	*f;
	void	*z;
}	t_textures;

typedef struct s_player
{
	int		x;
	int		y;
	char	orient;
	int		score;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_height;
	int			map_width;
	int			coins;
	int			end_flag;
	t_player	player;
	t_textures	txt;
}	t_game;

//input_check.c
int		get_characters(char **map, int *characters, t_game *game);
void	flood_fill(int y, int x, t_game *game, int *exit_flag);
int		flood_fill_check(t_game *game);
int		map_check(char **map, t_game *game);
int		input_check(char *filename, t_game *game);
//so_long.c
int		main(int ac, char **av);
int		init_textures(t_game *game);
void	init_pointers(t_game *game);
//utils.c
int		exit_error(t_game *game);
int		free_map(char **map);
int		end_game(t_game *game);
void	print_moves(int *moves, t_game *game);
char	*parse_map(char *file);
//hooks.c
void	mv_right(t_game *game);
void	mv_down(t_game *game);
void	mv_left(t_game *game);
void	mv_up(t_game *game);
int		key_hooks(int keycode, t_game *game);
//render.c
void	render_map(t_game *game);
void	put_item(int x, int y, t_game *game, char type);
void	check_zombie(t_game *game, int keycode, int x, int y);
void	mv_zombie(int x, int y, t_game *game);
void	render_zombies(t_game *game);

#endif