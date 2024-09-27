/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:11:54 by maglagal          #+#    #+#             */
/*   Updated: 2024/09/27 11:36:59 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

//calculating sprite width and height in the projection
void calculating_sprite_width_height(t_sprite *sprite, float d_projection, int *ystart, int *yend)
{
    sprite->pSpriteHeight = (d_projection * sprite->texture->height) / sprite->distance;
    sprite->pSpriteWidth = (d_projection * sprite->texture->width) / sprite->distance;
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
    int     xstart;
    int     tmpy;
    // int     color;
    int     textOffsetX;

    xstart = sprite->spriteXstart;
    tmpy = ystart;
    while (xstart < sprite->spriteXend)
    {
        textOffsetX = calculate_offsetX(sprite, xstart);
        ystart = tmpy;
        while (ystart < yend)
        {
            if (ystart < HEIGHT && xstart < WIDTH && xstart > 0 && ystart > 0
                && sprite->distance < player->rays[(int)xstart].distance_to_wall)
            {
                int color = calculate_pixel_index(sprite, ystart, textOffsetX);
                if (color != 0 && sprite->collected == 0)
                    mlx_put_pixel(player->map_img, xstart, ystart, color);
            }
            ystart++;
        }
        xstart++;
    }
}

void    calculate_sprite_projection_and_render(t_player *player, int index)
{
    int ystart;
    int yend;
    float d_projection;

    ystart = 0;
    yend = 0;
    d_projection = (WIDTH / 2) / (tan(degrees2rad(FOV_ANGLE / 2)));
    calculating_sprite_width_height(&player->sprite[index], d_projection, &ystart, &yend);
    calculating_sprite_x(player, &player->sprite[index], d_projection, player->sprite[index].pSpriteWidth);
    render_one_sprite(player, &player->sprite[index], ystart, yend);
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
                calculate_sprite_projection_and_render(player, j);
            if (player->sprite[j].distance < 20 && player->sprite[j].collected == 0)
            {
                player->sprite[j].collected = 1;
                player->nbr_collected++;
            }
        }
		j++;
	}
}
