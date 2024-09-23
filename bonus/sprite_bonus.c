/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:11:54 by maglagal          #+#    #+#             */
/*   Updated: 2024/09/23 12:40:13 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

double calculate_distance_sprites(t_player *player)
{
    double distance;

    distance = sqrt(pow(player->sprite->x - player->player_x, 2) + pow(player->sprite->y - player->player_y, 2));
    return (distance);
}

void visibleSprite(t_player *player)
{
    double spritePlayer = player->playerAngle - atan2(player->sprite->y - player->player_y,
        player->sprite->x - player->player_x);
    if (spritePlayer > M_PI)
        spritePlayer -= 2 * M_PI;
    if (spritePlayer < -M_PI)
        spritePlayer += 2 * M_PI;
    player->sprite->angle = fabs(spritePlayer);
    player->sprite->distance = calculate_distance_sprites(player);
    calculate_distance_sprites(player);
    if (player->sprite->angle < degrees2rad(FOV_ANGLE / 2))
        player->sprite->visible = 1;
    else
        player->sprite->visible = 0;
}


void    calculate_sprite_projection_and_render(t_player *player)
{
    double d_projection = (WIDTH / 2) / (tan(degrees2rad(FOV_ANGLE / 2)));
    double pSpriteHeight = (d_projection * player->sprite->texture->height) / player->sprite->distance;
    double pSpriteWidth = (d_projection * player->sprite->texture->width) / player->sprite->distance;
    int ystart = (HEIGHT / 2) - (pSpriteHeight / 2);
    if (ystart < 0)
        ystart = 0;
    int yend = (HEIGHT / 2) + (pSpriteHeight / 2);
    if (yend > HEIGHT)
        yend = HEIGHT;
    player->sprite->angle = atan2(player->sprite->y - player->player_y,
        player->sprite->x - player->player_x) - player->playerAngle;
    int spriteXstart = (WIDTH / 2) + (d_projection * tan(player->sprite->angle));
    int spriteXend = spriteXstart + pSpriteWidth;
    int tmpy = ystart;
    int tmpx = spriteXstart;
    while (spriteXstart < spriteXend)
    {
        int texelWidth = (player->sprite->texture->width / pSpriteWidth);
        int textOffsetX = (spriteXstart - tmpx) * texelWidth;
        ystart = tmpy;
        while (ystart < yend)
        {
            if (ystart < HEIGHT && spriteXstart < WIDTH && spriteXstart > 0 && ystart > 0
                && player->sprite->distance < player->rays[spriteXstart].distance_to_wall)
            {
                int DTop = ystart + (pSpriteHeight / 2) - (HEIGHT / 2);
			    int textOffsetY = DTop * (player->sprite->texture->height / pSpriteHeight);
                int index = ((textOffsetY * player->sprite->texture->width) + textOffsetX) * 4;
			    int color = get_rgba(player->sprite->texture->pixels[index],
				    player->sprite->texture->pixels[index + 1], player->sprite->texture->pixels[index + 2],
				    player->sprite->texture->pixels[index + 3]);
                mlx_put_pixel(player->map_img, spriteXstart, ystart, color);
            }
            ystart++;
        }
        spriteXstart++;
    }
}
