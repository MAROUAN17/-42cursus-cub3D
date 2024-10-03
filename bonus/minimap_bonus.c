/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:09 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/03 13:04:52 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

void draw_rectangle(mlx_image_t *img, float x, float y, int color, float p)
{
	float i = 0;
	float j = 0;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
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
				player->player_x = x * TILE_PX + (TILE_PX / 2);
				player->player_y = y * TILE_PX + (TILE_PX / 2);
			}
			if (player->map[y][x] == 'I')
				num++;
			x++;
		}
		y++;
	}
	player->map_x_offset = (player->map_width / 2) - (int)player->player_x - 5 * TILE_PX;
	player->map_y_offset = (player->map_height / 2) - (int)player->player_y - 5 * TILE_PX;
	// printf("player->player_x -> %f\n", player->player_x);
	// printf("player->player_y -> %f\n", player->player_y);
	// printf("player->map_width-> %d\n", player->map_width / 2);
	// printf("player->map_height -> %d\n", player->map_height / 2);
	// printf("map x 0ffset -> %d\n", player->map_x_offset);
	// printf("map y 0ffset -> %d\n", player->map_y_offset);
	return (num);
}

void save_sprite_coordinates(t_player *player, int *index, int x, int y)
{
	if (player->map[y][x] == 'I'
		&& player->sprite[*index].x == -1
		&& player->sprite[*index].x == -1)
	{
		player->sprite[*index].x = x * TILE_PX + (TILE_PX / 2);
		player->sprite[*index].y = y * TILE_PX + (TILE_PX / 2);
		draw_rectangle(player->map_img, (x * TILE_PX + player->map_x_offset) * MINIMAP_FACTOR, (y * TILE_PX + player->map_y_offset) * MINIMAP_FACTOR, 0xFFFFFFFF, TILE_PX * MINIMAP_FACTOR);
		(*index)++;
	}
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
	draw_rectangle(player->map_img, (player->player_x + player->map_x_offset) * MINIMAP_FACTOR, (player->player_y + player->map_y_offset) * MINIMAP_FACTOR,
		0xFF0000FF, 40 * MINIMAP_FACTOR);
}
