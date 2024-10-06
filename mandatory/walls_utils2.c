/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:44:00 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/06 10:23:18 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header.h"

float	calculate_correct_wall_distance(t_player *player, int i)
{
	float	correct_wall_distance;

	if (player->rays[i].distance_to_wall < 0)
		player->rays[i].distance_to_wall = 0;
	correct_wall_distance = fabs(player->rays[i].distance_to_wall
			* cos(player->rays[i].angle - player->player_angle));
	if (!correct_wall_distance)
		correct_wall_distance = 0.001;
	return (correct_wall_distance);
}

int	calculate_offsetx_walls(t_player *player, int i)
{
	int	text_offset_x;

	if (player->rays[i].vertical_wall)
		text_offset_x = (int)player->rays[i].y % player->rays[i].texture->width;
	else
		text_offset_x = (int)player->rays[i].x % player->rays[i].texture->width;
	return (text_offset_x);
}

void	draw_floor(mlx_image_t *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 1 && i < WIDTH)
	{
		j = 0;
		while (y + j < HEIGHT)
		{
			mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
