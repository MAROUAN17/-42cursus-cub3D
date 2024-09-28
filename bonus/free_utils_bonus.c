/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:51:39 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/28 15:36:09 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

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

void	free_allocated_memory(t_player *player, mlx_texture_t **textures, mlx_texture_t **d_textures)
{
	free(player->rays);
	free(player->door_sprite);
	free(player->sprite);
	mlx_delete_texture(player->east_texture);
	mlx_delete_texture(player->west_texture);
	mlx_delete_texture(player->north_texture);
	mlx_delete_texture(player->south_texture);
	mlx_delete_texture(textures[0]);
	mlx_delete_texture(textures[1]);
	mlx_delete_texture(textures[2]);
	mlx_delete_texture(textures[3]);
	mlx_delete_texture(textures[4]);
	mlx_delete_texture(d_textures[0]);
	mlx_delete_texture(d_textures[1]);
	mlx_delete_texture(d_textures[2]);
	mlx_delete_texture(d_textures[3]);
}
