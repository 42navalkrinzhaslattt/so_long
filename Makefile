NAME	= so_long

SRC		= so_long.c input_check.c utils.c hooks.c render.c

BONUS_SRC		= so_long_bonus.c input_check_bonus.c utils_bonus.c hooks_bonus.c render_bonus.c

SRC_DIR	= srcs/

BONUS_SRC_DIR	= srcs_bonus/

OBJ	= $(addprefix $(SRC_DIR), $(SRC:.c=.o))

BONUS_OBJ	= $(addprefix $(BONUS_SRC_DIR), $(BONUS_SRC:.c=.o))

INC_DIR = includes

LIBFT	= libft/libft.a

CC		= cc

CFLAGS	= -Wall -Werror -Wextra

MLX		= mlx_linux/libmlx_Linux.a

%.o: %.c
	$(CC) $(CFLAGS) -I ./includes -I/usr/include -Imlx_linux -O3 -c  $< -o $@

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -Llibft -lft -fsanitize=address -g -o $(NAME)

bonus: $(MLX) $(LIBFT) $(BONUS_OBJ)
	$(CC) $(BONUS_OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -Llibft -lft -fsanitize=address -g -o $(NAME)

$(LIBFT):
	make -C libft all

$(MLX):
	git clone https://github.com/42Paris/minilibx-linux.git mlx_linux
	cd mlx_linux && ./configure

clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -rf mlx_linux

re:	fclean all

.PHONY: all clean fclean re