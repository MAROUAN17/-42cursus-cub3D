/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:31 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/29 11:53:44 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

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
	if (p_y < 0 || p_x < 0)
		return (0);
	return (player->map[p_y][p_x] == '1');
}

int is_door(t_player *player, int x, int y)
{
	int p_x;
	int p_y;

	p_x = x / TILE_PX;
	p_y = y / TILE_PX;
	if (p_y < 0 || p_x < 0)
		return (0);
	return (player->map[p_y][p_x] == 'D');
}

mlx_texture_t *get_texture(t_player *player, int is_vert, float x, float y)
{
	int wall;

	if (is_vert)
	{
		wall = is_wall(player, x - 1, y);
		if (wall == 1)
			return (player->east_texture);
		else
			return  (player->west_texture);
	}
	else
	{
		wall = is_wall(player, x, y - 1);
		if (wall == 1)
			return (player->south_texture);
		else
			return (player->north_texture);
	}
	return (NULL);
}

void draw_rectangle_3d(t_player *player, int x, float y, int w, int p, int textOffsetX, mlx_texture_t *texture)
{
	int i;
	int j;
	int Dbottom;
	int textOffsetY;
	int index;
	int color;

	i = 0;
	Dbottom = 0;
	textOffsetY = 0;
	index = 0;
	color = 0;
	while (i < w && i < WIDTH)
	{
		j = 0;
		while (j < p && y + j < HEIGHT)
		{
			Dbottom = (y + j) + ((p / 2) - (HEIGHT / 2));
			textOffsetY = Dbottom * ((float)texture->height / p);
			index = ((textOffsetY * texture->width) + textOffsetX) * 4;
			color = get_rgba(texture->pixels[index],
				texture->pixels[index + 1], texture->pixels[index + 2],
				texture->pixels[index + 3]);
			if (color != 0)
				mlx_put_pixel(player->map_img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void draw_ceiling(mlx_image_t *img, int x, int y, int color, int w)
{
    int i;
	int j;

	i = 0;
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
    int i = 0;
	int j = 0;
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
