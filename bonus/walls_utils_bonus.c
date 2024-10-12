/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:31 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_bonus.h"

int	is_wall(t_player *player, int x, int y)
{
	int	p_x;
	int	p_y;

	p_x = x / TILE_PX;
	p_y = y / TILE_PX;
	if (p_y < 0 || p_x < 0)
		return (0);
	return (player->map[p_y][p_x] == '1');
}

mlx_texture_t	*get_texture(t_player *player, int is_vert, float x, float y)
{
	int	wall;

	if (is_vert)
	{
		wall = is_wall(player, x - 1, y);
		if (wall == 1)
			return (player->east_texture);
		else
			return (player->west_texture);
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

void	draw_rectangle_3d(t_player *player, int x, float y, int textOffsetX)
{
	int	j;
	int	dbottom;
	int	textoffsety;
	int	index;
	int	color;

	j = 0;
	while (j < (int)player->rays[x].wall_height && y + j < HEIGHT)
	{
		dbottom = (y + j) + (((int)player->rays[x].wall_height / 2)
				- (HEIGHT / 2));
		textoffsety = dbottom * ((float)player->rays[x].texture->height
				/ (int)player->rays[x].wall_height);
		index = ((textoffsety * player->rays[x].texture->width)
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
	while (i < 1)
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

void	draw_floor(mlx_image_t *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 1)
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
