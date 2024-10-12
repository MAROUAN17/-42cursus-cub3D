/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:40:53 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_bonus.h"

float	get_distance(t_player *player, float x, float y)
{
	float	result;

	result = sqrt(pow(player->player_x - x, 2) + pow(player->player_y - y, 2));
	return (result);
}

void	handle_multi_d_intersects(t_player *player, int i, int j)
{
	float	h_x;
	float	h_y;
	float	v_x;
	float	v_y;

	h_x = player->rays[i].d_h_xintersept[j];
	h_y = player->rays[i].d_h_yintersept[j];
	v_x = player->rays[i].d_v_xintersept[j];
	v_y = player->rays[i].d_v_yintersept[j];
	if (player->rays[i].vertical_wall && v_x != -1 && h_x != -1)
	{
		player->rays[i].vertical_wall = 0;
		if (get_distance(player, h_x, h_y) < player->rays[i].distance_to_wall)
			draw_door(player, h_x, h_y, i);
		player->rays[i].vertical_wall = 1;
	}
	else if (h_x != -1 && v_x != -1)
	{
		player->rays[i].vertical_wall = 1;
		if (get_distance(player, v_x, v_y) < player->rays[i].distance_to_wall)
			draw_door(player, v_x, v_y, i);
		player->rays[i].vertical_wall = 0;
	}
	draw_door(player, player->rays[i].d_x, player->rays[i].d_y, i);
}

int	check_visible_door(t_player *player, float x, float y, int j)
{
	visible_sprite_d(player, player->door_sprite, j);
	return (player->door_sprite[j].visible
		&& x >= player->door_sprite[j].x
		&& x <= player->door_sprite[j].x + TILE_PX
		&& y >= player->door_sprite[j].y
		&& y <= player->door_sprite[j].y + TILE_PX);
}

void	check_open_door(t_player *player, int i, int j)
{
	if (player->door_sprite[j].open_door == 0)
		player->rays[i].distance_to_wall
			= player->rays[i].distance_to_door;
}

void	draw_door(t_player *player, float x, float y, int i)
{
	int	text_offsetx;
	int	j;
	int	ystart;

	j = 0;
	player->rays[i].distance_to_door = get_distance(player, x, y);
	player->rays[i].wall_height = calculate_door_height(player, i);
	ystart = (HEIGHT / 2) - ((int)player->rays[i].wall_height / 2);
	if (ystart < 0)
		ystart = 0;
	while (j < player->doors_count)
	{
		if (check_visible_door(player, x, y, j))
		{
			player->rays[i].texture = player->door_sprite[j].texture;
			if (player->rays[i].vertical_wall)
				text_offsetx = (int)y % player->door_sprite[j].texture->width;
			else
				text_offsetx = (int)x % player->door_sprite[j].texture->width;
			check_open_door(player, i, j);
			draw_rectangle_3d(player, i, ystart, text_offsetx);
		}
		j++;
	}
}
