/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:51:39 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/07 11:19:23 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

void	*free_memory(char **map, int r)
{
	while (r != 0)
		free(map[--r]);
	free(map);
	return (NULL);
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	print_err(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		write(2, &line[i], 1);
		i++;
	}
}

void	destroy_textures(t_player *player)
{
	if (player->east_texture)
		mlx_delete_texture(player->east_texture);
	if (player->west_texture)
		mlx_delete_texture(player->west_texture);
	if (player->north_texture)
		mlx_delete_texture(player->north_texture);
	if (player->south_texture)
		mlx_delete_texture(player->south_texture);
}
