/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:11:54 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/03 14:19:38 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

//calculating sprite width and height in the projection
void calculating_sprite_width_height(t_sprite *sprite, float d_projection, int *ystart, int *yend)
{
	sprite->pSpriteHeight = ((d_projection * sprite->texture->height) / sprite->distance) + ((sprite->texture->height % TILE_PX) * 2);
	sprite->pSpriteWidth = ((d_projection * sprite->texture->width) / sprite->distance) + ((sprite->texture->width % TILE_PX) * 2);
	*ystart = (HEIGHT / 2) - (sprite->pSpriteHeight / 2);
	if (*ystart < 0)
		*ystart = 0;
	*yend = (HEIGHT / 2) + (sprite->pSpriteHeight / 2);
	if (*yend > HEIGHT)
		*yend = HEIGHT;
} 

//calculate the pixel index to render the correct pixel in the pixels array in the texture
int calculate_pixel_index(t_sprite *sprite, int ystart, int textOffsetX)
{
	int     DTop;
	int     indexC;
	int     color;
	int     textOffsetY;

	color = 0;
	DTop = ystart + (sprite->pSpriteHeight / 2) - (HEIGHT / 2);
	textOffsetY = DTop * (sprite->texture->height / sprite->pSpriteHeight);    
	indexC = ((textOffsetY * sprite->texture->width) + textOffsetX) * 4;
	color = get_rgba(sprite->texture->pixels[indexC],
		sprite->texture->pixels[indexC + 1], sprite->texture->pixels[indexC + 2],
		sprite->texture->pixels[indexC + 3]);
	return (color);
}

//the correct offset to render the correct pixel in the width of the texture
int calculate_offsetX(t_sprite *sprite, int xstart)
{
	float  texelWidth;
	int     textOffsetX;

	texelWidth = (sprite->texture->width / sprite->pSpriteWidth);
	textOffsetX = (xstart - sprite->spriteXstart) * texelWidth;
	return (textOffsetX);
}

//render the sprite to the projection
void render_one_sprite(t_player *player, t_sprite *sprite, int ystart, int yend)
{
	int	xstart;
	int	tmpy;
	int	color;
	int	textOffsetX;

	xstart = sprite->spriteXstart;
	tmpy = ystart;
	while (xstart < sprite->spriteXend)
	{
		textOffsetX = calculate_offsetX(sprite, xstart);
		ystart = tmpy;
		while (ystart < yend)
		{
			if (ystart < HEIGHT && xstart < WIDTH && xstart > 0 && ystart > 0
				&& sprite->distance < player->rays[xstart].distance_to_wall)
			{
				color = calculate_pixel_index(sprite, ystart, textOffsetX);
				if (color != 0)
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
	calculating_sprite_width_height(&player->sprite[index], d_projection, &ystart, &yend);
	calculating_sprite_x(player, &player->sprite[index], d_projection, player->sprite[index].pSpriteWidth);
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
		if (player->sprite[j].collected == 0)
		{
			visible_sprite_c(player, player->sprite, j);
			render_sprites_minimap(player, j);
			change_sprite_index(player, j, texIndex);
			if (player->sprite[j].visible)
			{
				calculate_sprite_projection_and_render(player, j);
				if (player->sprite[j].distance < 50)
				{
					player->sprite[j].collected = 1;
					player->nbr_collected++;
				}
			}
		}
		j++;
	}
}
