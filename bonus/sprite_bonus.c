/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:11:54 by maglagal          #+#    #+#             */
/*   Updated: 2024/09/27 10:38:48 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

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
    if (sprite[index].angle < degrees2rad(FOV_ANGLE / 2))
        sprite[index].visible = 1;
    else
        sprite[index].visible = 0;
	// printf("visible %d\n", sprite[index].visible);
	// printf("distance %f\n", sprite[index].distance);
}

void    calculate_sprite_projection_and_render(t_player *player, t_sprite *sprite, int index)
{
    double d_projection = (WIDTH / 2) / (tan(degrees2rad(FOV_ANGLE / 2)));
    double pSpriteHeight = (d_projection * sprite[index].texture->height) / sprite[index].distance;
    double pSpriteWidth = (d_projection * sprite[index].texture->width) / sprite[index].distance;
    int ystart = (HEIGHT / 2) - (pSpriteHeight / 2);
    if (ystart < 0)
        ystart = 0;
    int yend = (HEIGHT / 2) + (pSpriteHeight / 2);
    if (yend > HEIGHT)
        yend = HEIGHT;
    sprite[index].angle = atan2(sprite[index].y - player->player_y,
        sprite[index].x - player->player_x) - player->playerAngle;
    int spriteXstart = (WIDTH / 2) + (d_projection * tan(sprite[index].angle));
    int spriteXend = spriteXstart + pSpriteWidth;
    int tmpy = ystart;
    int tmpx = spriteXstart;
    while (spriteXstart < spriteXend)
    {
        double texelWidth = (sprite[index].texture->width / pSpriteWidth);
        int textOffsetX = (spriteXstart - tmpx) * texelWidth;
        ystart = tmpy;
        while (ystart < yend)
        {
			// printf("spriteXstart %d\n", spriteXstart);
			// printf("condition %d\n", sprite[index].distance < player->rays[spriteXstart].distance_to_wall);
            if (ystart < HEIGHT && spriteXstart < WIDTH && spriteXstart > 0 && ystart > 0
                && sprite[index].distance < player->rays[spriteXstart].distance_to_wall)
            {
                int DTop = ystart + (pSpriteHeight / 2) - (HEIGHT / 2);
			    int textOffsetY = DTop * (sprite[index].texture->height / pSpriteHeight);
                int indexC = ((textOffsetY * sprite[index].texture->width) + textOffsetX) * 4;
			    int color = get_rgba(sprite[index].texture->pixels[indexC],
				    sprite[index].texture->pixels[indexC + 1], sprite[index].texture->pixels[indexC + 2],
				    sprite[index].texture->pixels[indexC + 3]);
                if (color != 0 && sprite[index].collected == 0)
                    mlx_put_pixel(player->map_img, spriteXstart, ystart, color);
            }
            ystart++;
        }
        spriteXstart++;
    }
}

void render_sprites(t_player *player, int texIndex)
{
    int j = 0;

	while (j < NUM_SPRITE)
	{
        if (player->sprite[j].collected == 0)
        {
            render_sprites_minimap(player, j);
            visibleSprite(player, player->sprite, j);
            change_sprite_index(player, texIndex);
            if (player->sprite[j].visible)
                calculate_sprite_projection_and_render(player, player->sprite, j);
            if (player->sprite[j].distance < 20 && player->sprite[j].collected == 0)
            {
                player->sprite[j].collected = 1;
                player->nbr_collected++;
            }
        }
		j++;
	}
}
