/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:55:12 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/08 14:43:44 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_b.h"

void	handle_animation_door(t_player *player, int i)
{
	if (player->door_sprite[i].start_a
		&& player->door_sprite[i].open_door == 0)
	{
		player->door_sprite[i].texture
			= player->door_sprite[i].an_textures[player->door_index / 5];
		if (player->door_index == 15)
		{
			player->door_sprite[i].open_door = 1;
			player->door_sprite[i].start_a = 0;
		}
	}
	else if (player->door_sprite[i].start_a
		&& player->door_sprite[i].open_door)
	{
		player->door_sprite[i].texture
			= player->door_sprite[i].an_textures[3 - (player->door_index / 5)];
		if (player->door_index == 15)
		{
			player->door_sprite[i].start_a = 0;
			player->door_sprite[i].open_door = 0;
		}
	}
}

void	handle_door(t_player *player)
{
	int	i;

	i = 0;
	while (i < player->doors_count)
	{
		handle_animation_door(player, i);
		i++;
	}
}

void	handle_door_intersect(t_player *player, int i)
{
	int		j;
	float	n_distance_to_wall;

	j = player->doors_count - 1;
	while (j >= 0)
	{
		if ((player->rays[i].d_h_xintersept[j] != -1
				&& player->rays[i].d_h_yintersept[j] != -1)
			|| (player->rays[i].d_v_xintersept[j] != -1
				&& player->rays[i].d_v_yintersept[j] != -1))
			n_distance_to_wall = get_smallest_door_distance(player,
					&player->rays[i], j);
		if (((player->rays[i].d_h_xintersept[j] != -1
					&& player->rays[i].d_h_yintersept[j] != -1)
				|| (player->rays[i].d_v_xintersept[j] != -1
					&& player->rays[i].d_v_yintersept[j] != -1))
			&& n_distance_to_wall < player->rays[i].distance_to_wall)
			handle_multi_d_intersects(player, i, j);
		j--;
	}
}

void	h_initialize_inters_doors(t_player *player, t_ray *ray)
{
	int	i;

	i = 0;
	while (i < player->doors_count)
	{
		ray->d_h_xintersept[i] = -1;
		ray->d_h_yintersept[i] = -1;
		i++;
	}
}

void	v_initialize_inters_doors(t_player *player, t_ray *ray)
{
	int	i;

	i = 0;
	while (i < player->doors_count)
	{
		ray->d_v_xintersept[i] = -1;
		ray->d_v_yintersept[i] = -1;
		i++;
	}
}
