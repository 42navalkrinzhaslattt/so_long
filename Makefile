NAME	= so_long

SRC = so_long.c

SRC_DIR = srcs/

OBJ	= $(addprefix $(SRC_DIR), $(SRC:.c=.o))

INC_DIR = includes

LIBFT	= libft/libft.a

CC			= cc

CFLAGS		= -Wall -Werror -Wextra

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -I/usr/include -Imlx_linux -O3 -c  $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -Llibft -lft -o $(NAME) -fsanitize=address

$(LIBFT):
	make -C libft all

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re:	fclean all

.PHONY: all clean fclean re