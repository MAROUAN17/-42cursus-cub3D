/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:25:52 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/06 10:21:49 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	is_wall(t_player *player, int x, int y)
{
	int	p_x;
	int	p_y;

	p_x = x / TILE_PX;
	p_y = y / TILE_PX;
	if (p_y < 0 || p_x < 0
		|| p_y >= player->map_height || p_x >= player->map_width)
		return (0);
	return (player->map[p_y][p_x] == '1');
}

mlx_texture_t	*get_texture(t_player *player, int is_vert, double x, double y)
{
	if (is_vert)
	{
		if (is_wall(player, x - 1, y))
			return (player->east_texture);
		else
			return (player->west_texture);
	}
	else
	{
		if (is_wall(player, x, y - 1))
			return (player->south_texture);
		else
			return (player->north_texture);
	}
}

void	draw_walls(t_player *player, int x, float y, int textOffsetX)
{
	int	j;
	int	d_bottom;
	int	text_offset_y;
	int	index;
	int	color;

	j = 0;
	while (j < (int)player->rays[x].wall_height && y + j < HEIGHT)
	{
		d_bottom = (y + j)
			+ (((int)player->rays[x].wall_height / 2) - (HEIGHT / 2));
		text_offset_y = d_bottom
			* ((float)player->rays[x].texture->height
				/ (int)player->rays[x].wall_height);
		index = ((text_offset_y * player->rays[x].texture->width)
				+ textOffsetX) * 4;
		color = get_rgba(player->rays[x].texture->pixels[index],
				player->rays[x].texture->pixels[index + 1],
				player->rays[x].texture->pixels[index + 2],
				player->rays[x].texture->pixels[index + 3]);
		if (color != 0)
			mlx_put_pixel(player->map_img, x, y + j, color);
		j++;
	}
}

void	draw_ceiling(mlx_image_t *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 1 && i < WIDTH)
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
