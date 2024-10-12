/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:44:30 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/09 11:54:32 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_bonus.h"

void	calculate_distance_coins(t_player *player)
{
	int	i;

	i = 0;
	while (i < player->total_sprites)
	{
		player->sprite[i].distance = sqrt(pow(player->sprite[i].x
					- player->player_x, 2) + pow(player->sprite[i].y
					- player->player_y, 2));
		i++;
	}
}

void	visible_sprite_c(t_player *player, t_sprite *sprite, int index)
{
	double	sprite_player;

	sprite_player = player->player_angle - atan2(sprite[index].y
			- player->player_y, sprite[index].x - player->player_x);
	if (sprite_player > M_PI)
		sprite_player -= 2 * M_PI;
	if (sprite_player < -M_PI)
		sprite_player += 2 * M_PI;
	sprite[index].angle = fabs(sprite_player);
	if (sprite[index].angle < degrees2rad(FOV_ANGLE / 2) + 0.1)
		sprite[index].visible = 1;
	else
		sprite[index].visible = 0;
}

void	visible_sprite_d(t_player *player, t_sprite *sprite, int index)
{
	double	sprite_player;

	sprite_player = player->player_angle - atan2(sprite[index].y
			- player->player_y, sprite[index].x - player->player_x);
	if (sprite_player > M_PI)
		sprite_player -= 2 * M_PI;
	if (sprite_player < -M_PI)
		sprite_player += 2 * M_PI;
	sprite[index].angle = fabs(sprite_player);
	if (sprite[index].angle < degrees2rad(FOV_ANGLE / 2) + 0.9
		|| calculate_distance_door(player,
			player->door_sprite, index) < TILE_PX * 2)
		sprite[index].visible = 1;
	else
		sprite[index].visible = 0;
}

void	calculating_sprite_x(t_player *player, t_sprite *sprite,
			float d_projection, float psprite_width)
{
	sprite->angle = atan2(sprite->y - player->player_y,
			sprite->x - player->player_x) - player->player_angle;
	sprite->sprite_xstart = (WIDTH / 2) + (d_projection * tan(sprite->angle));
	sprite->sprite_xend = sprite->sprite_xstart + psprite_width;
}

double	calculate_distance_door(t_player *player, t_sprite *sprite, int index)
{
	double	distance;

	distance = sqrt(pow(sprite[index].x - player->player_x, 2)
			+ pow(sprite[index].y - player->player_y, 2));
	return (distance);
}
