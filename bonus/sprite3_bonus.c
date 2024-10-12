/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:12:22 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/09 11:54:38 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_bonus.h"

void	change_sprite_index(t_player *player, int i, int texIndex)
{
	if (texIndex >= 0 && texIndex <= 10)
		player->sprite[i].texture = player->sprite[i].an_textures[
			(int)texIndex / 11];
	else if (texIndex > 10 && texIndex <= 20)
		player->sprite[i].texture = player->sprite[i].an_textures[
			(int)texIndex / 11];
	else if (texIndex > 20 && texIndex <= 30)
		player->sprite[i].texture = player->sprite[i].an_textures[
			(int)texIndex / 11];
	else if (texIndex > 30 && texIndex <= 40)
		player->sprite[i].texture = player->sprite[i].an_textures[
			(int)texIndex / 11];
	else if (texIndex > 40 && texIndex <= 50)
		player->sprite[i].texture = player->sprite[i].an_textures[
			(int)texIndex / 11];
}

void	draw_sprites(t_player *player, int x_out, int y_out, int sprIndex)
{
	if (player->sprite[sprIndex].visible)
	{
		player->color = 0x00FF00FF;
		draw_rectangle(player, x_out * player->minimap_factor, y_out
			* player->minimap_factor, (TILE_PX / 2) * player->minimap_factor);
	}
	else
	{
		player->color = 0x0044444F;
		draw_rectangle(player, x_out * player->minimap_factor, y_out
			* player->minimap_factor, (TILE_PX / 2) * player->minimap_factor);
	}
}

void	render_sprites_minimap(t_player *player, int sprIndex)
{
	float	x_out;
	float	y_out;

	x_out = player->sprite[sprIndex].x + player->map_x_offset;
	y_out = player->sprite[sprIndex].y + player->map_y_offset;
	if (x_out < 0)
		x_out = 0;
	if (y_out < 0)
		y_out = 0;
	if (x_out > 0 && y_out > 0 && x_out < 21 * TILE_PX && y_out < 21 * TILE_PX)
		draw_sprites(player, x_out, y_out, sprIndex);
}

void	calculating_sprite_width_height(t_sprite *sprite,
			float d_projection, int *ystart, int *yend)
{
	sprite->psprite_height = ((d_projection * sprite->texture->height)
			/ sprite->distance);
	sprite->psprite_width = ((d_projection * sprite->texture->width)
			/ sprite->distance);
	*ystart = (HEIGHT / 2) - (sprite->psprite_height / 2);
	if (*ystart < 0)
		*ystart = 0;
	*yend = (HEIGHT / 2) + (sprite->psprite_height / 2);
	if (*yend > HEIGHT)
		*yend = HEIGHT;
}

int	calculate_pixel_index(t_sprite *sprite,
		int ystart, int textOffsetX)
{
	int	dtop;
	int	indexc;
	int	color;
	int	textoffsety;

	color = 0;
	dtop = ystart + (sprite->psprite_height / 2) - (HEIGHT / 2);
	textoffsety = dtop * (sprite->texture->height
			/ sprite->psprite_height);
	indexc = ((textoffsety * sprite->texture->width) + textOffsetX) * 4;
	color = get_rgba(sprite->texture->pixels[indexc],
			sprite->texture->pixels[indexc + 1],
			sprite->texture->pixels[indexc + 2],
			sprite->texture->pixels[indexc + 3]);
	return (color);
}
