/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:00 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_bonus.h"

float	calculate_xstep(float ray_angle)
{
	float	xstep;

	xstep = TILE_PX / tan(ray_angle);
	return (xstep);
}

float	find_closest_horizontal_yintersec(t_player *player)
{
	float	yintersept;

	yintersept = floor(player->player_y / TILE_PX) * TILE_PX;
	return (yintersept);
}

float	find_closest_horizontal_xintersec(t_player *player,
			float yintersept, float ray_angle)
{
	float	xintersept;

	xintersept = player->player_x + (yintersept - player->player_y)
		/ tan(ray_angle);
	return (xintersept);
}

t_point	calculating_horizontal_intersections(t_player *player, t_ray *ray)
{
	t_point	wall;
	float	ystep;
	float	xstep;

	ray->h_yintersept = find_closest_horizontal_yintersec(player);
	if (ray->p_is_facing_down)
		ray->h_yintersept += TILE_PX;
	ray->h_xintersept = find_closest_horizontal_xintersec(player,
			ray->h_yintersept, ray->angle);
	ystep = TILE_PX;
	if (ray->p_is_facing_up)
		ystep *= -1;
	xstep = calculate_xstep(ray->angle);
	if ((ray->p_is_facing_left && xstep > 0)
		|| (ray->p_is_facing_right && xstep < 0))
		xstep *= -1;
	ray->d_x = -1;
	ray->d_y = -1;
	h_initialize_inters_doors(player, ray);
	wall = finding_wall_horizontal(player, ray, xstep, ystep);
	return (wall);
}
