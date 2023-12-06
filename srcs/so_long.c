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
#include "../includes/so_long.h"

int	main(int ac, char **av)
{
	t_mlx_data	mlx_data;
	t_game		game;

	if (ac != 2 || !input_check(av[1], &game))
		return (exit_error());
}