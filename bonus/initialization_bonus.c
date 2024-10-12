/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:46:04 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_bonus.h"

int	initialize_all(t_player *player, char *map_path, mlx_texture_t **c_textures,
		mlx_texture_t **d_textures)
{
	int	map_width;
	int	map_height;

	map_width = 0;
	map_height = 0;
	if (initialize_player_struct(player, map_path, &map_width, &map_height))
		return (1);
	player->door_sprite = NULL;
	player->minimap_factor = ((float)(HEIGHT / 100) / TILE_PX);
	if (initialize_rays_struct(player))
		free_and_exit(player);
	if (initialize_animation_textures(c_textures, d_textures))
	{
		free_old_rays(player->rays, WIDTH);
		free_and_exit(player);
	}
	if (initialize_sprites_struct(player, c_textures))
	{
		return (destroy_t_coins(c_textures), destroy_t_door(d_textures),
			free_old_rays(player->rays, WIDTH), free_and_exit(player), 1);
	}
	if (initialize_door_sprites(player, d_textures))
		return (free_allocated_memory(player, c_textures, d_textures), 1);
	return (0);
}

int	initialize_animation_textures(mlx_texture_t **c_textures,
		mlx_texture_t **d_textures)
{
	if (init_door(d_textures))
		return (1);
	c_textures[0] = mlx_load_png("./textures/MonedaD1.png");
	if (!c_textures[0])
		return (destroy_t_door(d_textures), 1);
	c_textures[1] = mlx_load_png("./textures/MonedaD2.png");
	if (!c_textures[1])
		return (mlx_delete_texture(c_textures[0]),
			destroy_t_door(d_textures), 1);
	c_textures[2] = mlx_load_png("./textures/MonedaD3.png");
	if (!c_textures[2])
		return (mlx_delete_texture(c_textures[0]),
			mlx_delete_texture(c_textures[1]), destroy_t_door(d_textures), 1);
	c_textures[3] = mlx_load_png("./textures/MonedaD4.png");
	if (!c_textures[3])
		return (mlx_delete_texture(c_textures[0]),
			mlx_delete_texture(c_textures[1]),
			mlx_delete_texture(c_textures[2]), destroy_t_door(d_textures), 1);
	c_textures[4] = mlx_load_png("./textures/MonedaD5.png");
	if (!c_textures[4])
		return (mlx_delete_texture(c_textures[0]),
			mlx_delete_texture(c_textures[1]),
			mlx_delete_texture(c_textures[2]),
			mlx_delete_texture(c_textures[3]), destroy_t_door(d_textures), 1);
	return (0);
}

void	initialize_map_img(t_player *player)
{
	player->map_img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
	if (!player->map_img)
	{
		free_2d_arr(player->map);
		perror(strerror(mlx_errno));
		mlx_terminate(player->mlx);
		exit(EXIT_FAILURE);
	}
}

int	initialize_player_struct(t_player *player,
			char *map_path, int *map_width, int *map_height)
{
	player->map = store_2d_array(player, map_path, map_height, map_width);
	if (!player->map)
	{
		destroy_map_textures(player);
		exit(1);
	}
	player->mlx = mlx_init(WIDTH, HEIGHT, "cub3D_bonus", false);
	if (!player->mlx)
		free_and_exit(player);
	initialize_map_img(player);
	player->turn_left = 0;
	player->turn_right = 0;
	player->s_key = 0;
	player->a_key = 0;
	player->d_key = 0;
	player->w_key = 0;
	player->nbr_collected = 0;
	player->p_fov_angle = degrees2rad(60);
	player->player_x = -1;
	player->player_y = -1;
	player->move_speed = (float)(((float)TILE_PX / HEIGHT) * 4000);
	player->rotation_speed = degrees2rad(2.5);
	player->map_height = *map_height * TILE_PX;
	player->map_width = *map_width * TILE_PX;
	return (0);
}

int	alloc_d_rays(t_player *player, t_ray *rays, int i)
{
	rays[i].d_h_xintersept = malloc(sizeof(float) * (player->doors_count + 1));
	if (!rays[i].d_h_xintersept)
		return (0);
	rays[i].d_h_yintersept = malloc(sizeof(float) * (player->doors_count + 1));
	if (!rays[i].d_h_yintersept)
		return (free(rays[i].d_h_xintersept), 0);
	rays[i].d_v_xintersept = malloc(sizeof(float) * (player->doors_count + 1));
	if (!rays[i].d_v_xintersept)
		return (free(rays[i].d_h_xintersept),
			free(rays[i].d_h_yintersept), 0);
	rays[i].d_v_yintersept = malloc(sizeof(float) * (player->doors_count + 1));
	if (!rays[i].d_v_yintersept)
		return (free(rays[i].d_h_xintersept),
			free(rays[i].d_h_yintersept), free(rays[i].d_v_xintersept), 0);
	return (1);
}
