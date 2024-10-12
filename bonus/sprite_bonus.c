/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:11:54 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/09 11:54:30 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_bonus.h"

int	calculate_offsetx(t_sprite *sprite, int xstart)
{
	float	texel_width;
	int		textoffsetx;

	texel_width = (sprite->texture->width / sprite->psprite_width);
	textoffsetx = (xstart - sprite->sprite_xstart) * texel_width;
	return (textoffsetx);
}

void	render_one_sprite(t_player *player, t_sprite *sprite,
			int ystart, int yend)
{
	int	xstart;
	int	tmpy;
	int	color;
	int	textoffsetx;

	xstart = sprite->sprite_xstart;
	tmpy = ystart;
	while (xstart < sprite->sprite_xend)
	{
		textoffsetx = calculate_offsetx(sprite, xstart);
		ystart = tmpy;
		while (ystart < yend)
		{
			if (ystart < HEIGHT && xstart < WIDTH && xstart >= 0 && ystart >= 0
				&& sprite->distance < player->rays[xstart].distance_to_wall)
			{
				color = calculate_pixel_index(sprite, ystart, textoffsetx);
				if (color)
					mlx_put_pixel(player->map_img, xstart, ystart, color);
			}
			ystart++;
		}
		xstart++;
	}
}

void	calculate_sprite_projection_and_render(t_player *player, int index)
{
	float	d_projection;
	int		ystart;
	int		yend;

	ystart = 0;
	yend = 0;
	d_projection = (WIDTH / 2) / (tan(degrees2rad(FOV_ANGLE / 2)));
	calculating_sprite_width_height(&player->sprite[index],
		d_projection, &ystart, &yend);
	calculating_sprite_x(player, &player->sprite[index], d_projection,
		player->sprite[index].psprite_width);
	render_one_sprite(player, &player->sprite[index], ystart, yend);
}

void	sort_sprites(t_player *player)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < player->total_sprites - 1)
	{
		j = i + 1;
		while (j < player->total_sprites)
		{
			if (player->sprite[i].distance < player->sprite[j].distance
				&& !player->sprite[i].collected && !player->sprite[j].collected)
			{
				tmp = player->sprite[i];
				player->sprite[i] = player->sprite[j];
				player->sprite[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	render_coins(t_player *player, int texIndex)
{
	int	j;

	j = 0;
	calculate_distance_coins(player);
	sort_sprites(player);
	while (j < player->total_sprites)
	{
		visible_sprite_c(player, player->sprite, j);
		if (player->sprite[j].collected == 0)
		{
			render_sprites_minimap(player, j);
			change_sprite_index(player, j, texIndex);
			if (player->sprite[j].visible)
			{
				calculate_sprite_projection_and_render(player, j);
				if (player->sprite[j].distance < TILE_PX / 2)
				{
					player->sprite[j].collected = 1;
					player->nbr_collected++;
				}
			}
		}
		j++;
	}
}
