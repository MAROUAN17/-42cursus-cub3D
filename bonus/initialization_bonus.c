/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:46:04 by maglagal          #+#    #+#             */
/*   Updated: 2024/09/25 16:54:39 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_b.h"

void initialize_player_struct(t_player *player, char *map_path, int *map_width, int *map_height)
{
    player->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!player->mlx)
	{
		free_2d_arr(player->map);
		perror(strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
    player->nbr_collected = 0;
	player->p_fov_angle = degrees2rad(60);
	player->player_x = -1;
	player->player_y = -1;
	player->map = store_2d_array(player, map_path, map_height, map_width);
	if (!player->map)
		return ;
	player->map_img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
    player->moveSpeed = 6.0;
	player->rotationSpeed = degrees2rad(2.5);
    player->map_height = *map_height * TILE_PX;
	player->map_width = *map_width * TILE_PX;
}

void initialize_rays_struct(t_player *player, t_ray *rays)
{
    int     i;

    i = 0;
	while (i < WIDTH)
	{
		rays[i].map_img = player->map_img;
		rays[i].h_xintersept = 0;
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
}

void initialize_sprites_struct(t_player *player, t_sprite *sprite, mlx_texture_t **textures)
{
    int j;

    j = 0;
	while (j < NUM_SPRITE)
	{
		sprite[j].pSpriteWidth = 0;
		sprite[j].pSpriteHeight = 0;
		sprite[j].spriteXstart = 0;
		sprite[j].spriteXend = 0;
		sprite[j].collected = 0;
		sprite[j].x = 0;
		sprite[j].y = 0;
		sprite[j].texture = textures[0];
		sprite[j].visible = 0;
		sprite[j].an_textures = textures;
		j++;
	}
    player->sprite = sprite;
}
