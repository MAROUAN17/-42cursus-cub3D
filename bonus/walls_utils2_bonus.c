/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:13:09 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/04 11:11:29 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

float calculate_correct_wall_distance(t_player *player, int i)
{
	float correct_wall_distance;

	if (player->rays[i].distance_to_wall < 0)
		player->rays[i].distance_to_wall = 0;
	correct_wall_distance = fabs(player->rays[i].distance_to_wall * cos(player->rays[i].angle - player->playerAngle));
	if (!correct_wall_distance)
		correct_wall_distance = 0.001;
	return (correct_wall_distance);
}

float calculate_correct_door_distance(t_player *player, int i)
{
	float correct_door_distance;

	if (player->rays[i].distance_to_door < 0)
		player->rays[i].distance_to_door = 0;
	correct_door_distance = fabs(player->rays[i].distance_to_door * cos(player->rays[i].angle - player->playerAngle));
	if (!correct_door_distance)
		correct_door_distance = 0.001;
	return (correct_door_distance);
}

float	calculate_door_height(t_player *player, int i)
{
	float correct_wall_distance;
	float pWallHeight;
	float d_projection;

	d_projection = (WIDTH / 2) / tan(degrees2rad(FOV_ANGLE / 2));
	correct_wall_distance = calculate_correct_door_distance(player, i);
	pWallHeight = (TILE_PX * d_projection) / correct_wall_distance;
	return (pWallHeight);
}

float	calculate_wall_height(t_player *player, int i)
{
	float correct_wall_distance;
	float pWallHeight;
	float d_projection;

	d_projection = (WIDTH / 2) / tan(degrees2rad(FOV_ANGLE / 2));
	correct_wall_distance = calculate_correct_wall_distance(player, i);
	pWallHeight = (TILE_PX * d_projection) / correct_wall_distance;
	return (pWallHeight);
}

int	check_door_coin_collision(t_player *player, int i)
{
	int z = 0;

	z = 0;
	while (z < player->total_sprites)
	{
		if (player->sprite[z].visible &&
			player->sprite[z].distance < player->rays[i].distance_to_door)
			return (1);
		z++;
	}
	return (0);
}
