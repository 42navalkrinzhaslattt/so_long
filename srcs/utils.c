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
#include "../includes/so_long.h"

int	exit_error()
{
	perror("Error\nInvalid map\n");
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
