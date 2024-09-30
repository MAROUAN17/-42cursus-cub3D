/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:20:56 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/30 15:26:52 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

void	save_door_cord(t_player *player, int x, int y, int *d_index)
{
	int	color;
	player->door_sprite[*d_index].x = x * TILE_PX;
	player->door_sprite[*d_index].y = y * TILE_PX;
	color = get_rgba(149, 69, 53, 255);
	draw_rectangle(player->map_img, (x * TILE_PX) * MINIMAP_FACTOR,
		(y * TILE_PX) * MINIMAP_FACTOR, color, TILE_PX * MINIMAP_FACTOR);
	(*d_index)++;
}
