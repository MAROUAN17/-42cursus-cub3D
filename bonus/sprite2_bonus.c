/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:44:30 by maglagal          #+#    #+#             */
/*   Updated: 2024/09/27 16:20:43 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_b.h"

void	change_sprite_index(t_player *player, int texIndex)
{
	int i = 0;
	while (i < NUM_SPRITE)
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
		i++;
	}
}

void render_sprites_minimap(t_player *player, int sprIndex)
{
	if (player->sprite[sprIndex].visible)
		draw_rectangle(player->map_img, player->sprite[sprIndex].x * MINIMAP_FACTOR, player->sprite[sprIndex].y * MINIMAP_FACTOR,
			0x00FF00FF, 10 * MINIMAP_FACTOR);
	else
		draw_rectangle(player->map_img, player->sprite[sprIndex].x * MINIMAP_FACTOR, player->sprite[sprIndex].y * MINIMAP_FACTOR,
			0x0044444F, 10 * MINIMAP_FACTOR);
}

double calculate_distance_sprites(t_player *player, t_sprite *sprite, int index)
{
    double distance;

    distance = sqrt(pow(sprite[index].x - player->player_x, 2) + pow(sprite[index].y - player->player_y, 2));
    return (distance);
}

void visibleSprite(t_player *player, t_sprite *sprite, int index)
{
    double spritePlayer = player->playerAngle - atan2(sprite[index].y - player->player_y,
        sprite[index].x - player->player_x);
    if (spritePlayer > M_PI)
        spritePlayer -= 2 * M_PI;
    if (spritePlayer < -M_PI)
        spritePlayer += 2 * M_PI;
    sprite[index].angle = fabs(spritePlayer);
	// printf("angle %f\n", sprite[index].angle);
    sprite[index].distance = calculate_distance_sprites(player, sprite, index);
	// printf("distance %f\n", sprite[index].distance);
	// printf("angle %f\n", sprite[index].angle);
	// printf("fov %f\n", degrees2rad(FOV_ANGLE / 2));
    if (sprite[index].angle < degrees2rad(FOV_ANGLE / 2) + 0.4)
        sprite[index].visible = 1;
    else
        sprite[index].visible = 0;
	// printf("visible %d\n", sprite[index].visible);
	// printf("distance %f\n", sprite[index].distance);
}

//calculating sprite start and sprite end in the projection
void calculating_sprite_x(t_player *player, t_sprite *sprite, float d_projection, float pSpriteWidth)
{
    sprite->angle = atan2(sprite->y - player->player_y,
        sprite->x - player->player_x) - player->playerAngle;
    sprite->spriteXstart = (WIDTH / 2) + (d_projection * tan(sprite->angle));
    sprite->spriteXend = sprite->spriteXstart + pSpriteWidth;
}
