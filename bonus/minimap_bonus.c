/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:09 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/28 14:47:38 by maglagal         ###   ########.fr       */
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

int	calculate_number_sprites(t_player *player)
{
	int x;
	int y;
	int num;

	x = 0;
	y = 0;
	num = 0;
	while(player->map[y])
	{
		x = 0;
		while (player->map[y][x])
		{
			if (player->map[y][x] == 'N' || player->map[y][x] == 'S'
				|| player->map[y][x] == 'E' || player->map[y][x] == 'W')
			{
				player->player_x = x * TILE_PX;
				player->player_y = y * TILE_PX;
			}
			if (player->map[y][x] == 'I')
				num++;
			x++;
		}
		y++;
	}
	return (num);
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
	int	x;
	int	y;
	int	index;
	int	d_index;

	x = 0;
	y = 0;
	index = 0;
	d_index = 0;
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
				player->door_sprite[d_index].x = x * TILE_PX;
				player->door_sprite[d_index].y = y * TILE_PX;
				draw_rectangle(player->map_img, (x * TILE_PX) * MINIMAP_FACTOR, (y * TILE_PX) * MINIMAP_FACTOR, 0xFFFFFFFF, TILE_PX * MINIMAP_FACTOR);
				d_index++;
			}
			else
				draw_rectangle(player->map_img, (x * TILE_PX) * MINIMAP_FACTOR, (y * TILE_PX) * MINIMAP_FACTOR, 0xFFFFFFFF, TILE_PX * MINIMAP_FACTOR);
				// check_save_player_coordinates(player, x, y);
			x++;
		}
		y++;
	}
}
