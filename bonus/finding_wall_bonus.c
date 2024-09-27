/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_wall_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:01:55 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/27 14:08:13 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

t_point h_wall_check_position(t_player *player, t_ray *ray)
{
	t_point wall;
	float xcheck;
	float ycheck;

	ycheck = 0;
	xcheck = ray->h_xintersept;
	if (ray->p_isFacingUp)
		ycheck = ray->h_yintersept - 1;
	else
		ycheck = ray->h_yintersept;
	if ((int)(ycheck) < player->map_height
		&& (int)(ycheck) >= 0
		&& (int)(xcheck) < player->map_width
		&& (int)(xcheck) >= 0)
	{
		if (player->map[(int)(ycheck / TILE_PX)][(int)(xcheck / TILE_PX)] == '1')
		{
			wall.x = ray->h_xintersept;
			wall.y = ray->h_yintersept;
			return (wall);
		}
		else if (player->map[(int)((ycheck) / TILE_PX)][(int)(xcheck / TILE_PX)] == 'D')
		{
			ray->d_h_xintersept = ray->h_xintersept;
			ray->d_h_yintersept = ray->h_yintersept;
		}
	}
	wall.x = -1;
	wall.y = -1;
	return (wall);
}

t_point	finding_wall_horizontal(t_player *player, t_ray *ray, float xstep, float ystep)
{
	t_point wall;

	while (ray->h_xintersept >= 0 && ray->h_yintersept >= 0
		&& ray->h_xintersept < player->map_width
		&& ray->h_yintersept < player->map_height)
	{
		wall = h_wall_check_position(player, ray);
		if (wall.x != -1 && wall.y != -1)
			return (wall);
		ray->h_xintersept += xstep;
		ray->h_yintersept += ystep;
	}
	wall.x = ray->h_xintersept;
	wall.y = ray->h_yintersept;
	
	return (wall);
}

t_point v_wall_check_position(t_player *player, t_ray *ray)
{
	t_point wall;
	float xcheck;
	float ycheck;

	if (ray->p_isFacingLeft)
		xcheck = ray->v_xintersept - 1;
	else
		xcheck = ray->v_xintersept;
	ycheck = ray->v_yintersept;
	if ((int)(ycheck) < player->map_height
		&& (int)(ycheck) >= 0
		&& (int)(xcheck) < player->map_width
		&& (int)(xcheck) >= 0)
	{
		if (player->map[(int)(ycheck / TILE_PX)][(int)(xcheck / TILE_PX)] == '1')
		{
			wall.x = ray->v_xintersept;
			wall.y = ray->v_yintersept;
			return (wall);
		}
		else if (player->map[(int)((ycheck) / TILE_PX)][(int)(xcheck / TILE_PX)] == 'D')
		{
			ray->d_v_xintersept = ray->v_xintersept;
			ray->d_v_yintersept = ray->v_yintersept;
		}
	}
	wall.x = -1;
	wall.y = -1;
	return (wall);
}

t_point	finding_wall_vertical(t_player *player, t_ray *ray, float xstep, float ystep)
{
	t_point wall;

	while (ray->v_xintersept >= 0 && ray->v_yintersept >= 0
		&& ray->v_yintersept < player->map_height
		&& ray->v_xintersept < player->map_width)
	{
		wall = v_wall_check_position(player, ray);
		if (wall.x != -1 && wall.y != -1)
			return (wall);
		ray->v_xintersept += xstep;
		ray->v_yintersept += ystep;
	}
	wall.x = ray->v_xintersept;
	wall.y = ray->v_yintersept;
	return (wall);
}
