/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:09 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/27 11:55:51 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

void draw_rectangle(mlx_image_t *img, float x, float y, int color, float p)
{
	float i = 0;
	float j = 0;
	while (i < p)
	{
		j = 0;
		while (j < p)
		{
			mlx_put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void save_sprite_coordinates(t_player *player, int index, int x, int y)
{
	player->sprite[index].x = x * TILE_PX;
	player->sprite[index].y = y * TILE_PX;
	draw_rectangle(player->map_img, (x * TILE_PX) * MINIMAP_FACTOR, (y * TILE_PX) * MINIMAP_FACTOR, 0xFFFFFFFF, TILE_PX * MINIMAP_FACTOR);
}

void	check_save_player_coordinates(t_player *player, int x, int y)
{
	if (player->player_x == -1 && player->player_y == -1 && (player->map[y][x] == 'N' || player->map[y][x] == 'S' || player->map[y][x] == 'W' || player->map[y][x] == 'E'))
	{	
		player->player_x = x * TILE_PX;
		player->player_y = y * TILE_PX;
	}
}

void render_minimap(t_player *player)
{
	int     x = 0;
	int     y = 0;
	int		index = 0;
	int		d_index = 0;

	while (player->map[y])
	{
		x = 0;
		while (player->map[y][x])
		{
			if (player->map[y][x] == '1')
				draw_rectangle(player->map_img, (x * TILE_PX) * MINIMAP_FACTOR, (y * TILE_PX) * MINIMAP_FACTOR, 0x000000FF, TILE_PX * MINIMAP_FACTOR);
			else if (player->map[y][x] == 'I')
			{	
				save_sprite_coordinates(player, index, x, y);
				index++;
			}
			else if (player->map[y][x] == 'D')
			{
				// printf("insside\n");
				player->door_sprite[d_index].x = x * TILE_PX;
				player->door_sprite[d_index].y = y * TILE_PX;
				// printf("x -> %f\n", player->door_sprite[d_index].x);
				// printf("y -> %f\n", player->door_sprite[d_index].y);
				draw_rectangle(player->map_img, (x * TILE_PX) * MINIMAP_FACTOR, (y * TILE_PX) * MINIMAP_FACTOR, 0xFFFFFFFF, TILE_PX * MINIMAP_FACTOR);
				d_index++;
			}
			else
			{
				check_save_player_coordinates(player, x, y);
				draw_rectangle(player->map_img, (x * TILE_PX) * MINIMAP_FACTOR, (y * TILE_PX) * MINIMAP_FACTOR, 0xFFFFFFFF, TILE_PX * MINIMAP_FACTOR);
			}
			x++;
		}
		y++;
	}
}
