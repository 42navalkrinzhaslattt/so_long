#ifndef	SO_LONG_H
# define SO_LONG_H
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
#include "../libft/includes/libft.h"
# define BUFF_SIZE 100000

typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx_data;

typedef struct s_game
{
	char	**map;
	int		map_height;
	int		map_width;
	int		start_x;
	int		start_y;
	int		coins;

}	t_game;

//input_check.c
char	*parse_map(char *file);
int		get_characters(char **map, int *characters, t_game *game);
int		flood_fill_check(t_game *game);
int		map_check(char **map, t_game *game);
int		input_check(char *filename, t_game *game);
//so_long.c
int		main(int ac, char **av);
//utils.c
int		exit_error();
int		free_map(char **map);
#endif