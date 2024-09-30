/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:00 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/30 15:39:13 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

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

float	find_closest_horizontal_xintersec(t_player *player, float yintersept, float ray_angle)
{
	float	xintersept;

	xintersept = player->player_x + (yintersept - player->player_y) / tan(ray_angle);
	return (xintersept);
}

t_point calculating_horizontal_intersections(t_player *player, t_ray *ray)
{
    t_point wall;
    float  ystep;
    float  xstep;

    ray->h_yintersept = find_closest_horizontal_yintersec(player);
    if (ray->p_isFacingDown)
        ray->h_yintersept += TILE_PX;
    ray->h_xintersept = find_closest_horizontal_xintersec(player, ray->h_yintersept, ray->angle);
    ystep = TILE_PX;
    if (ray->p_isFacingUp)
        ystep *= -1;
    xstep = calculate_xstep(ray->angle);
    if ((ray->p_isFacingLeft && xstep > 0) || (ray->p_isFacingRight && xstep < 0))
        xstep *= -1;
	int i = 0;
	ray->d_x = -1;
	ray->d_y = -1;
	while (i < player->doors_count)
	{
		ray->d_h_xintersept[i] = -1;
		ray->d_h_yintersept[i] = -1;
		i++;
	}
	wall = finding_wall_horizontal(player, ray, xstep, ystep);
	return (wall);
}
