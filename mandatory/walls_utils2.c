/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:44:00 by maglagal          #+#    #+#             */
/*   Updated: 2024/09/26 13:07:17 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header.h"

//count the distance to wall the fisheye fix
float calculate_correct_wall_distance(t_player *player, int i)
{
    float correct_wall_distance;

    if (player->rays[i].distance_to_wall < 0)
        player->rays[i].distance_to_wall = 0;
    correct_wall_distance = fabs(player->rays[i].distance_to_wall * cos(player->rays[i].angle - player->playerAngle));
    if (!correct_wall_distance)
        correct_wall_distance = 0.001;
    return (correct_wall_distance);
}

//calculate texture offset x for walls textures
int calculate_offsetx_walls(t_player *player, int i)
{
    int textOffsetX;

    if (player->rays[i].vertical_wall)
        textOffsetX = (int)player->rays[i].y % player->rays[i].texture->width;
    else
        textOffsetX = (int)player->rays[i].x % player->rays[i].texture->width;
    return (textOffsetX);
}
