/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:39:59 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/05 16:54:47 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

float	degrees2rad(float degrees)
{
	return (degrees * (M_PI / 180.0));
}

void	draw_wall(t_player *player)
{
	int		text_offset_x;
	int		i;
	int		ystart;

	i = 0;
	ystart = 0;
	while (i < WIDTH)
	{
		player->rays[i].wall_height = calculate_wall_height(player, i);
		ystart = (HEIGHT / 2) - ((int)player->rays[i].wall_height / 2);
		if (ystart < 0)
			ystart = 0;
		draw_ceiling(player->map_img, i, ystart, player->ceiling_color, 1);
		text_offset_x = calculate_offsetx_walls(player, i);
		draw_walls(player, i, ystart, text_offset_x);
		if (ystart + player->rays[i].wall_height < HEIGHT)
			draw_floor(player->map_img, i,
				ystart + player->rays[i].wall_height, player->floor_color, 1);
		i++;
	}
}

void	update_ray_facing(t_ray *ray)
{
	ray->p_is_facing_down = 0;
	ray->p_is_facing_up = 0;
	ray->p_is_facing_right = 0;
	ray->p_is_facing_left = 0;
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->p_is_facing_down = 1;
	ray->p_is_facing_up = !ray->p_is_facing_down;
	if (ray->angle < M_PI / 2 || ray->angle > (1.5 * M_PI))
		ray->p_is_facing_right = 1;
	ray->p_is_facing_left = !ray->p_is_facing_right;
}

float	normalize_ray_angle(float ray_angle)
{
	ray_angle = remainder(ray_angle, 2 * M_PI);
	if (ray_angle < 0)
		ray_angle = (2 * M_PI) + ray_angle;
	if (fabs(tan(ray_angle)) < 0.000001)
		ray_angle += 0.0001;
	return (ray_angle);
}
