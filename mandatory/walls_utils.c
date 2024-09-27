/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:25:52 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/26 13:18:12 by maglagal         ###   ########.fr       */
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

void draw_walls(t_player *player, int x, double y, int w, int p, int textOffsetX, mlx_texture_t *texture)
{
	int i;
	int j;
	int DTop;
	int textOffsetY;
	int index;
	int color;

	i = 0;
	while (i < w && i < WIDTH)
	{
		j = 0;
		while (j < p && y + j < HEIGHT)
		{
			DTop = (y + j) + ((p / 2) - (HEIGHT / 2));
			textOffsetY = DTop * ((double)texture->height / p);
			index = ((textOffsetY * texture->width) + textOffsetX) * 4;
			color = get_rgba(texture->pixels[index],
				texture->pixels[index + 1], texture->pixels[index + 2],
				texture->pixels[index + 3]);
			mlx_put_pixel(player->map_img, x + i, y + j, color);
			j++;
		}
		i++;
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
