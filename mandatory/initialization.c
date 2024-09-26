/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:04:05 by maglagal          #+#    #+#             */
/*   Updated: 2024/09/26 13:09:22 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header.h"

void initialize_player_struct(t_player *player, char *map_path, int *map_width, int *map_height)
{
    player->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!player->mlx)
	{
		free_2d_arr(player->map);
		perror(strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	player->p_fov_angle = degrees2rad(60);
	player->player_x = -1;
	player->player_y = -1;
	player->map = store_2d_array(player, map_path, map_height, map_width);
	if (!player->map)
		return ;
	player->map_img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
    player->moveSpeed = (float)(((float)TILE_PX / HEIGHT) * 100);
	player->rotationSpeed = degrees2rad(2.5);
    player->map_height = *map_height * TILE_PX;
	player->map_width = *map_width * TILE_PX;
    save_player_coordinates(player);
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
