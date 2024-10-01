/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:46:04 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/01 13:47:53 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_b.h"

void initialize_player_struct(t_player *player, char *map_path, int *map_width, int *map_height)
{
	player->map = store_2d_array(player, map_path, map_height, map_width);
	if (!player->map)
		exit(1);
    player->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!player->mlx)
	{
		free_2d_array(player->map);
		perror(strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
    player->nbr_collected = 0;
	player->p_fov_angle = degrees2rad(60);
	player->player_x = -1;
	player->player_y = -1;
	player->map_img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
	if (!player->map_img)
	{
		free_2d_array(player->map);
		perror(strerror(mlx_errno));
		mlx_terminate(player->mlx);
		exit(EXIT_FAILURE);
	}
    player->moveSpeed = (float)(((float)TILE_PX / HEIGHT) * 100);
	player->rotationSpeed = degrees2rad(2.5);
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

int initialize_rays_struct(t_player *player, t_ray *rays)
{
    int     i;

    i = 0;
	while (i < WIDTH)
	{
		rays[i].map_img = player->map_img;
		rays[i].h_xintersept = 0;
		if (alloc_d_rays(player, rays, i) == 0)
			return (free_old_rays(rays, i), 0);
		rays[i].h_yintersept = 0;
		rays[i].v_xintersept = 0;
		rays[i].v_yintersept = 0;
		rays[i].p_isFacingDown = 0;
		rays[i].p_isFacingUp = 0;
		rays[i].p_isFacingRight = 0;
		rays[i].p_isFacingLeft = 0;
		rays[i].horizontal_wall = 0;
		rays[i].vertical_wall = 0;
		i++;
	}
	player->rays = rays;
	return (1);
}

void initialize_sprites_struct(t_player *player, t_sprite *sprite, mlx_texture_t **textures)
{
    int	j;

	(void)sprite;
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
	// player->sprite = sprite;
}
