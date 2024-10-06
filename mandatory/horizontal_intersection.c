/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 09:43:56 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/06 09:45:20 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

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

	xintersept = (yintersept - player->player_y) / tan(ray_angle)
		+ player->player_x;
	return (xintersept);
}

t_point	calculating_horizontal_intersections(t_player *player, t_ray *ray)
{
	t_point	wall;

	ray->h_yintersept = find_closest_horizontal_yintersec(player);
	if (ray->p_is_facing_down)
		ray->h_yintersept += TILE_PX;
	ray->h_xintersept = find_closest_horizontal_xintersec(player,
			ray->h_yintersept, ray->angle);
	ray->ystep = TILE_PX;
	if (ray->p_is_facing_up)
		ray->ystep *= -1;
	ray->xstep = calculate_xstep(ray->angle);
	if ((ray->p_is_facing_left && ray->xstep > 0)
		|| (ray->p_is_facing_right && ray->xstep < 0))
		ray->xstep *= -1;
	wall = finding_wall_horizontal(player, ray, ray->xstep, ray->ystep);
	return (wall);
}
