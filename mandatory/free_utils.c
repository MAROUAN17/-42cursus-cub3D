/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:51:39 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/26 14:30:29 by maglagal         ###   ########.fr       */
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
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void print_err(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		write(2, &line[i], 1);
		i++;
	}
}

void	destroy_textures(t_player *player)
{
	if (player->ea_t)
		mlx_delete_texture(&player->ea_t->texture);
	else
		mlx_delete_texture(player->east_texture);
	if (player->we_t) 
		mlx_delete_texture(&player->we_t->texture);
	else
		mlx_delete_texture(player->west_texture);
	if (player->no_t)
		mlx_delete_texture(&player->no_t->texture);
	else
		mlx_delete_texture(player->north_texture);
	if (player->so_t)
		mlx_delete_texture(&player->so_t->texture);
	else
		mlx_delete_texture(player->south_texture);
}
