/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:09 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_bonus.h"

void	check_save_player_coordinates(t_player *player, int x, int y)
{
	if (player->player_x == -1 && player->player_y == -1
		&& (player->map[y][x] == 'N' || player->map[y][x] == 'S'
			|| player->map[y][x] == 'W' || player->map[y][x] == 'E'))
	{
		player->player_x = x * TILE_PX + (TILE_PX / 2);
		player->player_y = y * TILE_PX + (TILE_PX / 2);
	}
}

int	calculate_number_sprites(t_player *player)
{
	int	x;
	int	y;
	int	num;

	y = 0;
	num = 0;
	while (player->map[y])
	{
		x = 0;
		while (player->map[y][x])
		{
			check_save_player_coordinates(player, x, y);
			if (player->map[y][x] == 'I')
				num++;
			x++;
		}
		y++;
	}
	player->map_x_offset = (player->map_width / 2) - (int)
		player->player_x - 5 * TILE_PX;
	player->map_y_offset = (player->map_height / 2) - (int)
		player->player_y - 5 * TILE_PX;
	return (num);
}

void	save_sprite_coordinates(t_player *player, int *index, int x, int y)
{
	if (player->map[y][x] == 'I'
		&& player->sprite[*index].x == -1
		&& player->sprite[*index].y == -1)
	{
		player->sprite[*index].x = x * TILE_PX + (TILE_PX / 2);
		player->sprite[*index].y = y * TILE_PX + (TILE_PX / 2);
		player->color = 0x00FF0000;
		if (((player->player_x / TILE_PX) - 10 <= x
				&& (player->player_x / TILE_PX) + 10 >= x)
			&& ((player->player_y / TILE_PX) - 10 <= y
				&& (player->player_y / TILE_PX) + 10 >= y))
		{
			if (player->sprite[*index].collected == 0)
				draw_rectangle(player, (player->sprite[*index].x
						+ player->map_x_offset) * player->minimap_factor,
					(player->sprite[*index].y + player->map_y_offset)
					* player->minimap_factor,
					(TILE_PX / 2) * player->minimap_factor);
		}
		(*index)++;
	}
}

void	draw_player_minimap(t_player *player)
{
	player->color = 0xFF0000FF;
	draw_rectangle(player, (player->player_x + player->map_x_offset)
		* player->minimap_factor, (player->player_y + player->map_y_offset)
		* player->minimap_factor, 40 * player->minimap_factor);
}

void	render_minimap(t_player *player)
{
	int	x;
	int	y;
	int	index;
	int	d_index;

	x = 0;
	y = 0;
	index = 0;
	d_index = 0;
	draw_map_background(player);
	while (player->map[y])
	{
		x = 0;
		while (player->map[y][x])
		{
			draw_map_elements(player, x, y);
			save_sprite_coordinates(player, &index, x, y);
			if (player->map[y][x] == 'D')
				save_door_cord(player, x, y, &d_index);
			x++;
		}
		y++;
	}
	draw_coin_minimap(player);
	draw_player_minimap(player);
}
