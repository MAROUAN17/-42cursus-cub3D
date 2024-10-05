/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_distance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:09:09 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/05 16:47:36 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

float	calculate_smallest_distance(t_player *player, t_ray *ray,
	t_point *wall1, t_point *wall2)
{
	float	distance1;
	float	distance2;

	distance1 = sqrt(pow(wall1->x - player->player_x, 2)
			+ pow(wall1->y - player->player_y, 2));
	distance2 = sqrt(pow(wall2->x - player->player_x, 2)
			+ pow(wall2->y - player->player_y, 2));
	if (distance2 < distance1)
	{
		ray->x = wall2->x;
		ray->y = wall2->y;
		ray->horizontal_wall = 0;
		ray->vertical_wall = 1;
		return (distance2);
	}
	else
	{
		ray->x = wall1->x;
		ray->y = wall1->y;
		ray->horizontal_wall = 1;
		ray->vertical_wall = 0;
		return (distance1);
	}
}

float	calculate_wall_height(t_player *player, int i)
{
	float	correct_wall_distance;
	float	wall_height;
	float	d_projection;

	d_projection = (WIDTH / 2) / tan(degrees2rad(FOV_ANGLE / 2));
	correct_wall_distance = calculate_correct_wall_distance(player, i);
	wall_height = (TILE_PX * d_projection) / correct_wall_distance;
	return (wall_height);
}
