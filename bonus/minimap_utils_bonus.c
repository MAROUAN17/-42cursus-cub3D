/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:40:24 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/03 11:21:53 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

void	draw_map_background(t_player *player)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	player->map_x_offset = 11 * TILE_PX - (int)player->player_x;
	player->map_y_offset = 11 * TILE_PX - (int)player->player_y;
	while (y <= 22)
	{
		x = 0;
		while (x <= 22)
		{
			draw_rectangle(player->map_img, (x * TILE_PX) * MINIMAP_FACTOR,
				(y * TILE_PX) * MINIMAP_FACTOR, 0x000000FF, TILE_PX * MINIMAP_FACTOR);
			x++;
		}
		y++;
	}
}

void	draw_map_elements(t_player *player, int x, int y)
{
	float x_out;
	float y_out;

	y_out = y * TILE_PX + player->map_y_offset;
	x_out = x * TILE_PX + player->map_x_offset;
	if (((player->player_x / TILE_PX) - 10 <= x && (player->player_x / TILE_PX) + 10 >= x)
		&& ((player->player_y / TILE_PX) - 10 <= y && (player->player_y / TILE_PX) + 10 >= y))
	{
		if (player->map[y][x] == '1')
			draw_rectangle(player->map_img, x_out * MINIMAP_FACTOR,
				y_out * MINIMAP_FACTOR, 0x000000FF, TILE_PX * MINIMAP_FACTOR);
		else
			draw_rectangle(player->map_img, x_out * MINIMAP_FACTOR,
				y_out * MINIMAP_FACTOR, 0xFFFFFFFF, TILE_PX * MINIMAP_FACTOR);
	}
}
