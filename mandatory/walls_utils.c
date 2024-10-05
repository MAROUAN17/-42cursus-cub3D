/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:25:52 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/05 11:22:22 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int is_wall(t_player *player, int x, int y)
{
	int p_x;
	int p_y;

	p_x = x / TILE_PX;
	p_y = y / TILE_PX;
	if (p_y < 0 || p_x < 0 || p_y >= player->map_height || p_x >= player->map_width)
		return (0);
	return (player->map[p_y][p_x] == '1');
}

mlx_texture_t *get_texture(t_player *player, int is_vert, double x, double y)
{
	if (is_vert)
	{
		if (is_wall(player, x - 1, y))
			return (player->east_texture);
		else
			return  (player->west_texture);
	}
	else
	{
		if (is_wall(player, x, y - 1))
			return (player->south_texture);
		else
			return (player->north_texture);
	}
}

void draw_walls(t_player *player, int x, float y, int textOffsetX)
{
	int j = 0;
	int Dbottom = 0;
	int textOffsetY = 0;
	int index = 0;
	int color = 0;
	j = 0;
	while (j < (int)player->rays[x].wall_height && y + j < HEIGHT)
	{
		Dbottom = (y + j) + (((int)player->rays[x].wall_height / 2) - (HEIGHT / 2));
		textOffsetY = Dbottom * ((float)player->rays[x].texture->height / (int)player->rays[x].wall_height);
		index = ((textOffsetY * player->rays[x].texture->width) + textOffsetX) * 4;
		color = get_rgba(player->rays[x].texture->pixels[index],
			player->rays[x].texture->pixels[index + 1],
			player->rays[x].texture->pixels[index + 2],
			player->rays[x].texture->pixels[index + 3]);
		if (color != 0)
			mlx_put_pixel(player->map_img, x, y + j, color);
		j++;
	}
}

void draw_ceiling(mlx_image_t *img, int x, int y, int color, int w)
{
    int i = 0;
	int j = 0;

	while (i < w && i < WIDTH)
	{
		j = 0;
		while (j < y && j < HEIGHT)
		{
			mlx_put_pixel(img, x + i, j, color);
			j++;
		}
		i++;
	}
}

void draw_floor(mlx_image_t *img, int x, int y, int color, int w)
{
    int i;
	int j;

	i = 0;
	while (i < w && i < WIDTH)
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
