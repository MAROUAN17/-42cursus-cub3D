/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersection_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:26 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_bonus.h"

float	calculate_ystep(float ray_angle)
{
	float	ystep;

	ystep = tan(ray_angle) * TILE_PX;
	return (ystep);
}

float	find_closest_vertical_xintersec(t_player *player)
{
	float	xintersept;

	xintersept = floor(player->player_x / TILE_PX) * TILE_PX;
	return (xintersept);
}

float	find_closest_vertical_yintersec(t_player *player,
			float xintersept, float ray_angle)
{
	float	yintersept;

	yintersept = player->player_y + (xintersept - player->player_x)
		* tan(ray_angle);
	return (yintersept);
}

t_point	calculating_vertical_intersections(t_player *player,
			t_ray *ray)
{
	t_point	wall;
	float	xstep;
	float	ystep;
	int		i;

	i = 0;
	ray->v_xintersept = find_closest_vertical_xintersec(player);
	if (ray->p_is_facing_right)
		ray->v_xintersept += TILE_PX;
	ray->v_yintersept = find_closest_vertical_yintersec(player,
			ray->v_xintersept, ray->angle);
	xstep = TILE_PX;
	if (ray->p_is_facing_left)
		xstep *= -1;
	ystep = calculate_ystep(ray->angle);
	if ((ray->p_is_facing_up && ystep > 0)
		|| (ray->p_is_facing_down && ystep < 0))
		ystep *= -1;
	v_initialize_inters_doors(player, ray);
	wall = finding_wall_vertical(player, ray, xstep, ystep);
	return (wall);
}
