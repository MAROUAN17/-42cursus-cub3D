/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:44:30 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/05 15:14:07 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_b.h"

void	change_sprite_index(t_player *player, int i, int texIndex)
{
	if (texIndex >= 0 && texIndex <= 10)
		player->sprite[i].texture = player->sprite[i].an_textures[(int)texIndex / 11];
	else if (texIndex > 10 && texIndex <= 20)
		player->sprite[i].texture = player->sprite[i].an_textures[(int)texIndex / 11];
	else if (texIndex > 20 && texIndex <= 30)
		player->sprite[i].texture = player->sprite[i].an_textures[(int)texIndex / 11];
	else if (texIndex > 30 && texIndex <= 40)
		player->sprite[i].texture = player->sprite[i].an_textures[(int)texIndex / 11];
	else if (texIndex > 40 && texIndex <= 50)
		player->sprite[i].texture = player->sprite[i].an_textures[(int)texIndex / 11];
}

void	render_sprites_minimap(t_player *player, int sprIndex)
{
	float x_out = player->sprite[sprIndex].x + player->map_x_offset;
	float y_out = player->sprite[sprIndex].y + player->map_y_offset;
	if (x_out < 0)
		x_out = 0;
	if (y_out < 0)
		y_out = 0;
	if (x_out > 0 && y_out > 0 && x_out < 21 * TILE_PX && y_out < 21 * TILE_PX)
	{
		draw_rectangle(player->map_img, x_out * MINIMAP_FACTOR, y_out * MINIMAP_FACTOR, 0xFFFFFFFF, 50 * MINIMAP_FACTOR);
		if (player->sprite[sprIndex].visible)
			draw_rectangle(player->map_img, x_out * MINIMAP_FACTOR, y_out * MINIMAP_FACTOR,
				0x00FF00FF, 50 * MINIMAP_FACTOR);
		else
			draw_rectangle(player->map_img, x_out * MINIMAP_FACTOR, y_out * MINIMAP_FACTOR,
				0x0044444F, 50 * MINIMAP_FACTOR);
	}
}

void	calculate_distance_coins(t_player *player)
{
	int i;

	i = 0;
	while (i < player->total_sprites)
	{
    	player->sprite[i].distance = sqrt(pow(player->sprite[i].x - player->player_x, 2) + pow(player->sprite[i].y - player->player_y, 2));
		i++;
	}
}

void visible_sprite_c(t_player *player, t_sprite *sprite, int index)
{
	double spritePlayer;

   	spritePlayer = player->playerAngle - atan2(sprite[index].y - player->player_y,
        sprite[index].x - player->player_x);
    if (spritePlayer > M_PI)
        spritePlayer -= 2 * M_PI;
    if (spritePlayer < -M_PI)
        spritePlayer += 2 * M_PI;
    sprite[index].angle = fabs(spritePlayer);
    if (sprite[index].angle < degrees2rad(FOV_ANGLE / 2) + 0.1)
        sprite[index].visible = 1;
    else
        sprite[index].visible = 0;
}

void visible_sprite_d(t_player *player, t_sprite *sprite, int index)
{
	double spritePlayer;

   	spritePlayer = player->playerAngle - atan2(sprite[index].y - player->player_y,
        sprite[index].x - player->player_x);
    if (spritePlayer > M_PI)
        spritePlayer -= 2 * M_PI;
    if (spritePlayer < -M_PI)
        spritePlayer += 2 * M_PI;
    sprite[index].angle = fabs(spritePlayer);
    if (sprite[index].angle < degrees2rad(FOV_ANGLE / 2) + 0.9)
        sprite[index].visible = 1;
    else
		sprite[index].visible = 0;
}

//calculating sprite start and sprite end in the projection
void calculating_sprite_x(t_player *player, t_sprite *sprite, float d_projection, float pSpriteWidth)
{
    sprite->angle = atan2(sprite->y - player->player_y,
        sprite->x - player->player_x) - player->playerAngle;
    sprite->spriteXstart = (WIDTH / 2) + (d_projection * tan(sprite->angle));
    sprite->spriteXend = sprite->spriteXstart + pSpriteWidth;
}

double	calculate_distance_door(t_player *player, t_sprite *sprite, int index)
{
    double distance;

    distance = sqrt(pow(sprite[index].x - player->player_x, 2) + pow(sprite[index].y - player->player_y, 2));
	return (distance);
}
