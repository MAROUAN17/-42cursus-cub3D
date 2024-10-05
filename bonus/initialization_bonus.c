/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:46:04 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/05 16:57:16 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_b.h"

int	initialize_all(t_player *player, char *map_path, mlx_texture_t **c_textures,
		mlx_texture_t **d_textures)
{
	int		map_width;
	int		map_height;

	map_width = 0;
	map_height = 0;
	initialize_player_struct(player, map_path, &map_width, &map_height);
	if (!initialize_rays_struct(player))
	{
		free_2d_arr(player->map);
		perror(strerror(mlx_errno));
		mlx_terminate(player->mlx);
		return (1);
	}
	initialize_animation_textures(c_textures, d_textures);
	initialize_sprites_struct(player, c_textures);
	if (!initialize_door_sprites(player, d_textures))
		return (1);
	return (0);
}

void initialize_animation_textures(mlx_texture_t **c_textures, mlx_texture_t **d_textures)
{
	d_textures[0] = resize_texture(mlx_load_png("./textures/MetalDoor1.png"), TILE_PX, TILE_PX);
	d_textures[1] = resize_texture(mlx_load_png("./textures/MetalDoor2.png"), TILE_PX, TILE_PX);
	d_textures[2] = resize_texture(mlx_load_png("./textures/MetalDoor3.png"), TILE_PX, TILE_PX);
	d_textures[3] = resize_texture(mlx_load_png("./textures/MetalDoor4.png"), TILE_PX, TILE_PX);
	c_textures[0] = mlx_load_png("./textures/MonedaD1.png");
	c_textures[1] = mlx_load_png("./textures/MonedaD2.png");
	c_textures[2] = mlx_load_png("./textures/MonedaD3.png");
	c_textures[3] = mlx_load_png("./textures/MonedaD4.png");
	c_textures[4] = mlx_load_png("./textures/MonedaD5.png");
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

void initialize_player_struct(t_player *player, char *map_path, int *map_width, int *map_height)
{
	player->map = store_2d_array(player, map_path, map_height, map_width);
	if (!player->map)
		exit(1);
	player->mlx = mlx_init(WIDTH, HEIGHT, "cub3D_bonus", false);
	if (!player->mlx)
	{
		free_2d_arr(player->map);
		perror(strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
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
	initialize_map_img(player);
	player->move_speed = (float)(((float)TILE_PX / HEIGHT) * 4000);
	player->rotation_speed = degrees2rad(2.5);
	player->map_height = *map_height * TILE_PX;
	player->map_width = *map_width * TILE_PX;
}

int	alloc_d_rays(t_player *player,t_ray *rays, int i)
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
}

int initialize_rays_struct(t_player *player)
{
	int     i;

	i = 0;
	player->rays = malloc(sizeof(t_ray) * WIDTH);
	if (!player->rays)
		return (0);
	while (i < WIDTH)
	{
		player->rays[i].map_img = player->map_img;
		player->rays[i].h_xintersept = 0;
		if (alloc_d_rays(player, player->rays, i) == 0)
			return (free_old_rays(player->rays, i), 0);
		player->rays[i].h_yintersept = 0;
		player->rays[i].v_xintersept = 0;
		player->rays[i].v_yintersept = 0;
		player->rays[i].p_is_facing_down = 0;
		player->rays[i].p_is_facing_up = 0;
		player->rays[i].p_is_facing_right = 0;
		player->rays[i].p_is_facing_left = 0;
		player->rays[i].horizontal_wall = 0;
		player->rays[i].vertical_wall = 0;
		i++;
	}
	return (1);
}

void initialize_sprites_struct(t_player *player, mlx_texture_t **textures)
{
	int	j;

	j = 0;
	player->total_sprites = calculate_number_sprites(player);
	player->sprite = malloc(sizeof(t_sprite) * player->total_sprites);
	while (j < player->total_sprites)
	{
		player->sprite[j].pSpriteWidth = 0;
		player->sprite[j].pSpriteHeight = 0;
		player->sprite[j].spriteXstart = 0;
		player->sprite[j].spriteXend = 0;
		player->sprite[j].collected = 0;
		player->sprite[j].x = -1;
		player->sprite[j].y = -1;
		player->sprite[j].texture = textures[0];
		player->sprite[j].visible = 0;
		player->sprite[j].an_textures = textures;
		j++;
	}
}

int initialize_door_sprites(t_player *player, mlx_texture_t **textures)
{
    int j;
	t_sprite *sprite;

    j = 0;
	sprite = malloc(sizeof(t_sprite) * player->doors_count);
	if (!sprite)
		return (0);
	while (j < player->doors_count)
	{
		sprite[j].collected = 0;
		sprite[j].open_door = 0;
		sprite[j].start_a = 0;
		sprite[j].x = 0;
		sprite[j].y = 0;
		sprite[j].texture = textures[0];
		sprite[j].visible = 0;
		sprite[j].an_textures = textures;
		j++;
	}
    player->door_sprite = sprite;
	return (1);
}
