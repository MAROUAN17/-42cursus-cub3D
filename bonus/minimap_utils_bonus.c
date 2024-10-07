/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:40:24 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/07 16:25:58 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

void	draw_rectangle(t_player *player, float x, float y, float p)
{
	float	i;
	float	j;

	i = 0;
	j = 0;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	while (i < p && y + i < HEIGHT)
	{
		j = 0;
		while (j < p && x + j < WIDTH)
		{
			mlx_put_pixel(player->map_img, x + j, y + i, player->color);
			j++;
		}
		i++;
	}
}

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
			player->color = 0x000000FF;
			draw_rectangle(player, (x * TILE_PX) * player->minimap_factor,
				(y * TILE_PX) * player->minimap_factor,
				TILE_PX * player->minimap_factor);
			x++;
		}
		y++;
	}
}

void	draw_map_elements(t_player *player, int x, int y)
{
	float	x_out;
	float	y_out;

	y_out = y * TILE_PX + player->map_y_offset;
	x_out = x * TILE_PX + player->map_x_offset;
	if (((player->player_x / TILE_PX) - 10 <= x
			&& (player->player_x / TILE_PX) + 10 >= x)
		&& ((player->player_y / TILE_PX) - 10 <= y
			&& (player->player_y / TILE_PX) + 10 >= y))
	{
		if (player->map[y][x] == '1')
		{
			player->color = 0x000000FF;
			draw_rectangle(player, x_out * player->minimap_factor,
				y_out * player->minimap_factor,
				TILE_PX * player->minimap_factor);
		}
		else
		{
			player->color = 0xFFFFFFFF;
			draw_rectangle(player, x_out * player->minimap_factor,
				y_out * player->minimap_factor,
				TILE_PX * player->minimap_factor);
		}
	}
}

void	draw_coin_minimap(t_player *player)
{
	int	i;

	i = 0;
	while (i < player->total_sprites)
	{
		if (player->sprite[i].collected == 0)
			render_sprites_minimap(player, i);
		i++;
	}
}
