/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:51:39 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_bonus.h"

void	*free_memory(char **map, int r)
{
	while (r != 0)
		free(map[--r]);
	free(map);
	return (NULL);
}

void	free_2d_arr(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_old_rays(t_ray *rays, int i)
{
	i--;
	while (i >= 0)
	{
		free(rays[i].d_h_xintersept);
		free(rays[i].d_h_yintersept);
		free(rays[i].d_v_xintersept);
		free(rays[i].d_v_yintersept);
		i--;
	}
	free(rays);
}

void	destroy_textures(mlx_texture_t **c_textures, mlx_texture_t **d_textures)
{
	mlx_delete_texture(c_textures[0]);
	mlx_delete_texture(c_textures[1]);
	mlx_delete_texture(c_textures[2]);
	mlx_delete_texture(c_textures[3]);
	mlx_delete_texture(c_textures[4]);
	mlx_delete_texture(d_textures[0]);
	mlx_delete_texture(d_textures[1]);
	mlx_delete_texture(d_textures[2]);
	mlx_delete_texture(d_textures[3]);
}

void	free_allocated_memory(t_player *player,
			mlx_texture_t **c_textures, mlx_texture_t **d_textures)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		free(player->rays[i].d_h_xintersept);
		free(player->rays[i].d_h_yintersept);
		free(player->rays[i].d_v_xintersept);
		free(player->rays[i].d_v_yintersept);
		i++;
	}
	if (player->door_sprite)
		free(player->door_sprite);
	free(player->sprite);
	free(player->rays);
	mlx_delete_texture(player->east_texture);
	mlx_delete_texture(player->west_texture);
	mlx_delete_texture(player->north_texture);
	mlx_delete_texture(player->south_texture);
	destroy_textures(c_textures, d_textures);
	free_2d_arr(player->map);
}
