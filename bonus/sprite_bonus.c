/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:11:54 by maglagal          #+#    #+#             */
/*   Updated: 2024/09/24 11:24:52 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

void	change_sprite_index(t_player *player, int texIndex)
{
	int i = 0;
	while (i < NUM_SPRITE)
	{
		if (texIndex >= 0 && texIndex <= 10)
			player->sprite[i].texture = mlx_load_png("./textures/MonedaD1.png");
		else if (texIndex > 10 && texIndex <= 20)
			player->sprite[i].texture = mlx_load_png("./textures/MonedaD2.png");
		else if (texIndex > 20 && texIndex <= 30)
			player->sprite[i].texture = mlx_load_png("./textures/MonedaD3.png");
		else if (texIndex > 35 && texIndex <= 40)
			player->sprite[i].texture = mlx_load_png("./textures/MonedaD4.png");
		else if (texIndex > 40 && texIndex <= 50)
			player->sprite[i].texture = mlx_load_png("./textures/MonedaD5.png");
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

double calculate_distance_sprites(t_player *player, int index)
{
    double distance;

    distance = sqrt(pow(player->sprite[index].x - player->player_x, 2) + pow(player->sprite[index].y - player->player_y, 2));
    return (distance);
}

void visibleSprite(t_player *player, int index)
{
    double spritePlayer = player->playerAngle - atan2(player->sprite[index].y - player->player_y,
        player->sprite[index].x - player->player_x);
    if (spritePlayer > M_PI)
        spritePlayer -= 2 * M_PI;
    if (spritePlayer < -M_PI)
        spritePlayer += 2 * M_PI;
    player->sprite[index].angle = fabs(spritePlayer);
    player->sprite[index].distance = calculate_distance_sprites(player, index);
    if (player->sprite[index].angle < degrees2rad(FOV_ANGLE / 2))
        player->sprite[index].visible = 1;
    else
        player->sprite[index].visible = 0;
}


void    calculate_sprite_projection_and_render(t_player *player, int index)
{
    double d_projection = (WIDTH / 2) / (tan(degrees2rad(FOV_ANGLE / 2)));
    double pSpriteHeight = (d_projection * player->sprite[index].texture->height) / player->sprite[index].distance;
    double pSpriteWidth = (d_projection * player->sprite[index].texture->width) / player->sprite[index].distance;
    int ystart = (HEIGHT / 2) - (pSpriteHeight / 2);
    if (ystart < 0)
        ystart = 0;
    int yend = (HEIGHT / 2) + (pSpriteHeight / 2);
    if (yend > HEIGHT)
        yend = HEIGHT;
    player->sprite[index].angle = atan2(player->sprite[index].y - player->player_y,
        player->sprite[index].x - player->player_x) - player->playerAngle;
    int spriteXstart = (WIDTH / 2) + (d_projection * tan(player->sprite[index].angle));
    int spriteXend = spriteXstart + pSpriteWidth;
    int tmpy = ystart;
    int tmpx = spriteXstart;
    while (spriteXstart < spriteXend)
    {
        double texelWidth = (player->sprite[index].texture->width / pSpriteWidth);
        int textOffsetX = (spriteXstart - tmpx) * texelWidth;
        ystart = tmpy;
        while (ystart < yend)
        {
            if (ystart < HEIGHT && spriteXstart < WIDTH && spriteXstart > 0 && ystart > 0
                && player->sprite[index].distance < player->rays[spriteXstart].distance_to_wall)
            {
                int DTop = ystart + (pSpriteHeight / 2) - (HEIGHT / 2);
			    int textOffsetY = DTop * (player->sprite[index].texture->height / pSpriteHeight);
                int indexC = ((textOffsetY * player->sprite[index].texture->width) + textOffsetX) * 4;
			    int color = get_rgba(player->sprite[index].texture->pixels[indexC],
				    player->sprite[index].texture->pixels[indexC + 1], player->sprite[index].texture->pixels[indexC + 2],
				    player->sprite[index].texture->pixels[indexC + 3]);
                if (color != 0)
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
		render_sprites_minimap(player, j);
		visibleSprite(player, j);
		change_sprite_index(player, texIndex);
        if (player->sprite[j].visible)
		    calculate_sprite_projection_and_render(player, j);
		j++;
	}
}
