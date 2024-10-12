/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_wall_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:01:55 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_bonus.h"

t_point	h_wall_check_position(t_player *player, t_ray *ray, int *index)
{
	t_point	wall;
	float	xcheck;
	float	ycheck;

	count_xcheck_ycheck(ray, &xcheck, &ycheck);
	if ((int)(ycheck) < player->map_height
		&& (int)(ycheck) >= 0
		&& (int)(xcheck) < player->map_width
		&& (int)(xcheck) >= 0)
	{
		if (player->map[(int)(ycheck / TILE_PX)]
			[(int)(xcheck / TILE_PX)] == '1')
			return (h_set_interse_wall(ray, index));
		else if (player->map[(int)((ycheck) / TILE_PX)]
			[(int)(xcheck / TILE_PX)] == 'D')
			h_set_interse_door(ray, index);
	}
	wall.x = -1;
	wall.y = -1;
	return (wall);
}

t_point	finding_wall_horizontal(t_player *player, t_ray *ray,
			float xstep, float ystep)
{
	t_point		wall;
	static int	h_index;

	while (ray->h_xintersept >= 0 && ray->h_yintersept >= 0
		&& ray->h_xintersept < player->map_width
		&& ray->h_yintersept < player->map_height)
	{
		wall = h_wall_check_position(player, ray, &h_index);
		if (wall.x != -1 && wall.y != -1)
			return (wall);
		ray->h_xintersept += xstep;
		ray->h_yintersept += ystep;
	}
	wall.x = ray->h_xintersept;
	wall.y = ray->h_yintersept;
	h_index = 0;
	return (wall);
}

t_point	v_wall_check_position(t_player *player, t_ray *ray, int *index)
{
	t_point	wall;
	float	xcheck;
	float	ycheck;

	if (ray->p_is_facing_left)
		xcheck = ray->v_xintersept - 1;
	else
		xcheck = ray->v_xintersept;
	ycheck = ray->v_yintersept;
	if ((int)(ycheck) < player->map_height
		&& (int)(ycheck) >= 0
		&& (int)(xcheck) < player->map_width
		&& (int)(xcheck) >= 0)
	{
		if (player->map[(int)(ycheck / TILE_PX)]
			[(int)(xcheck / TILE_PX)] == '1')
			return (v_set_interse_wall(ray, index));
		else if (player->map[(int)((ycheck) / TILE_PX)]
			[(int)(xcheck / TILE_PX)] == 'D')
			v_set_interse_door(ray, index);
	}
	wall.x = -1;
	wall.y = -1;
	return (wall);
}

t_point	finding_wall_vertical(t_player *player, t_ray *ray,
			float xstep, float ystep)
{
	t_point		wall;
	static int	v_index;

	while (ray->v_xintersept >= 0 && ray->v_yintersept >= 0
		&& ray->v_yintersept < player->map_height
		&& ray->v_xintersept < player->map_width)
	{
		wall = v_wall_check_position(player, ray, &v_index);
		if (wall.x != -1 && wall.y != -1)
			return (wall);
		ray->v_xintersept += xstep;
		ray->v_yintersept += ystep;
	}
	v_index = 0;
	wall.x = ray->v_xintersept;
	wall.y = ray->v_yintersept;
	return (wall);
}
