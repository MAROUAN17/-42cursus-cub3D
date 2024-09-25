/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_wall_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:01:55 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/25 14:42:27 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

t_point	finding_wall_horizontal(t_player *player, t_ray *ray, float xstep, float ystep)
{
	t_point wall;
	float xcheck = 0;
	float ycheck = 0;

	while (ray->h_xintersept >= 0 && ray->h_yintersept >= 0
		&& ray->h_xintersept <= player->map_width
		&& ray->h_yintersept <= player->map_height)
	{
		xcheck = ray->h_xintersept;
		if (ray->p_isFacingUp)
			ycheck = ray->h_yintersept - 1;
		else
			ycheck = ray->h_yintersept;
		if ((int)(ycheck) < player->map_height
			&& (int)(ycheck) >= 0
			&& (int)(xcheck) < player->map_width
			&& (int)(xcheck) >= 0
			&& player->map[(int)(ycheck / TILE_PX)][(int)(xcheck / TILE_PX)] == '1')
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

t_point	finding_wall_vertical(t_player *player, t_ray *ray, float xstep, float ystep)
{
	t_point wall;
	float xcheck = 0;
	float ycheck = 0;

	while (ray->v_xintersept >= 0 && ray->v_yintersept >= 0
		&& ray->v_yintersept <= player->map_height
		&& ray->v_xintersept <= player->map_width)
	{
		if (ray->p_isFacingLeft)
			xcheck = ray->v_xintersept - 1;
		else
			xcheck = ray->v_xintersept;
		ycheck = ray->v_yintersept;
		if ((int)(ycheck) < player->map_height
			&& (int)(ycheck) >= 0
			&& (int)(xcheck) < player->map_width
			&& (int)(xcheck) >= 0
			&& player->map[(int)(ycheck / TILE_PX)][(int)(xcheck / TILE_PX)] == '1')
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
