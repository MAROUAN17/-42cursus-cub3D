/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 09:37:28 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/06 09:42:35 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

int	is_wall_hit(t_player *player, int xcheck, int ycheck)
{
	return ((ycheck) < player->map_height
		&& (ycheck) >= 0
		&& (xcheck) < player->map_width
		&& (xcheck) >= 0
		&& player->map[(ycheck / TILE_PX)][(xcheck / TILE_PX)] == '1');
}

t_point	finding_wall_horizontal(t_player *player, t_ray *ray,
	float xstep, float ystep)
{
	t_point	wall;
	int		xcheck;
	int		ycheck;

	while (ray->h_xintersept > 0 && ray->h_yintersept > 0
		&& ray->h_xintersept < player->map_width
		&& ray->h_yintersept < player->map_height)
	{
		xcheck = ray->h_xintersept;
		if (ray->p_is_facing_up)
			ycheck = ray->h_yintersept - 1;
		else
			ycheck = ray->h_yintersept;
		if (is_wall_hit(player, xcheck, ycheck))
		{
			wall.x = ray->h_xintersept;
			wall.y = ray->h_yintersept;
			return (wall);
		}
		ray->h_xintersept += xstep;
		ray->h_yintersept += ystep;
	}
	wall.x = ray->h_xintersept;
	wall.y = ray->h_yintersept;
	return (wall);
}

t_point	finding_wall_vertical(t_player *player, t_ray *ray,
	float xstep, float ystep)
{
	t_point	wall;
	float	xcheck;
	float	ycheck;

	while (ray->v_xintersept >= 0 && ray->v_yintersept >= 0
		&& ray->v_yintersept < player->map_height
		&& ray->v_xintersept < player->map_width)
	{
		if (ray->p_is_facing_left)
			xcheck = ray->v_xintersept - 1;
		else
			xcheck = ray->v_xintersept;
		ycheck = ray->v_yintersept;
		if (is_wall_hit(player, xcheck, ycheck))
		{
			wall.x = ray->v_xintersept;
			wall.y = ray->v_yintersept;
			return (wall);
		}
		ray->v_xintersept += xstep;
		ray->v_yintersept += ystep;
	}
	wall.x = ray->v_xintersept;
	wall.y = ray->v_yintersept;
	return (wall);
}
