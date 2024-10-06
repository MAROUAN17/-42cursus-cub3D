/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:20:56 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/06 14:39:27 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

void	save_door_cord(t_player *player, int x, int y, int *d_index)
{
	int	color;

	player->door_sprite[*d_index].x = x * TILE_PX;
	player->door_sprite[*d_index].y = y * TILE_PX;
	color = get_rgba(149, 69, 53, 255);
	if (((player->player_x / TILE_PX) - 10 <= x
			&& (player->player_x / TILE_PX) + 10 >= x)
		&& ((player->player_y / TILE_PX) - 10 <= y
			&& (player->player_y / TILE_PX) + 10 >= y))
	{
		player->color = color;
		draw_rectangle(player, (x * TILE_PX + player->map_x_offset)
			* player->minimap_factor, (y * TILE_PX + player->map_y_offset)
			* player->minimap_factor, TILE_PX * player->minimap_factor);
	}
	(*d_index)++;
}

float	define_wall1(t_ray *ray, t_point *wall1, float distance1)
{
	ray->x = wall1->x;
	ray->y = wall1->y;
	ray->horizontal_wall = 1;
	ray->vertical_wall = 0;
	return (distance1);
}

float	define_wall2(t_ray *ray, t_point *wall2, float distance2)
{
	ray->x = wall2->x;
	ray->y = wall2->y;
	ray->horizontal_wall = 0;
	ray->vertical_wall = 1;
	return (distance2);
}

float	calculate_correct_distance(t_player *player, t_ray *ray,
			t_point *wall1, t_point *wall2)
{
	float	distance1;
	float	distance2;

	distance1 = sqrt(pow(wall1->x - player->player_x, 2)
			+ pow(wall1->y - player->player_y, 2));
	distance2 = sqrt(pow(wall2->x - player->player_x, 2)
			+ pow(wall2->y - player->player_y, 2));
	if (wall1->x == -1)
		return (define_wall2(ray, wall2, distance2));
	else if (wall2->x == -1)
		return (define_wall1(ray, wall1, distance1));
	else
	{
		if (distance1 < distance2)
			return (define_wall1(ray, wall1, distance1));
		else
			return (define_wall2(ray, wall2, distance2));
	}
}

float	get_smallest_door_distance(t_player *player, t_ray *ray, int j)
{
	t_point	p1;
	t_point	p2;
	float	distance;
	float	tmp_x;
	float	tmp_y;

	p1.x = ray->d_h_xintersept[j];
	p1.y = ray->d_h_yintersept[j];
	p2.x = ray->d_v_xintersept[j];
	p2.y = ray->d_v_yintersept[j];
	tmp_x = ray->x;
	tmp_y = ray->y;
	distance = calculate_correct_distance(player, ray, &p1, &p2);
	ray->d_x = ray->x;
	ray->d_y = ray->y;
	ray->x = tmp_x;
	ray->y = tmp_y;
	return (distance);
}
