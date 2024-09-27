/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:31 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/26 10:40:03 by oait-laa         ###   ########.fr       */
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
	if (player->map[p_y][p_x] == '0')
		return (0);
	else if (player->map[p_y][p_x] == '1')
		return (1);
	else if (player->map[p_y][p_x] == 'D')
		return (2);
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

mlx_texture_t *get_texture(t_player *player, int is_vert, double x, double y)
{
	int wall;
	// if (!is_vert && is_door(player, x, y + 1))
	// 	return (player->curr_door_tex);
	if (is_vert)
	{
		wall = is_wall(player, x - 1, y);
		if (wall == 1)
			return (player->east_texture);
		// else if (wall == 2)
		// 	return (player->door_textures[0]);
		else
			return  (player->west_texture);
	}
	else
	{
		wall = is_wall(player, x, y - 1);
		if (wall == 1)
			return (player->south_texture);
		// else if (wall == 2)
		// 	return (player->door_textures[0]);
		else if (wall == 0)
			return (player->north_texture);
	}
	return (NULL);
}

void draw_rectangle_3d(t_player *player, int x, double y, int w, int p, int textOffsetX, mlx_texture_t *texture)
{
	int i = 0;
	int j = 0;
	int Dbottom = 0;
	int textOffsetY = 0;
	int index = 0;
	int color = 0;
	// if (p > HEIGHT)
	// 	p = HEIGHT;
	while (i < w && i < WIDTH)
	{
		j = 0;
		while (j < p && y + j < HEIGHT)
		{
			Dbottom = (y + j) + ((p / 2) - (HEIGHT / 2));
			textOffsetY = Dbottom * ((double)texture->height / p);
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
