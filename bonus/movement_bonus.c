/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:45:51 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/05 16:32:14 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_b.h"

int	check_corner(t_player *player, float new_x, float new_y)
{
	int	check_y;
	int	check_x;
	(void)new_y;

	check_y = (player->player_y) / TILE_PX;
	check_x = (player->player_x + new_x) / TILE_PX;
	if (player->map[check_y][check_x] != '1')
		return (1);
	return (0);
}

float normalize_ray_angle(float ray_angle)
{
	ray_angle = remainder(ray_angle, 2 * M_PI);
	if (ray_angle < 0)
		ray_angle = (2 * M_PI) + ray_angle;
	if (fabs(tan(ray_angle)) < 0.000001)
		ray_angle += 0.0001;
	return (ray_angle);
}

int	is_open_door(t_player *player, int check_x, int check_y)
{
	int	i;

	i = 0;
	while (i < player->doors_count)
	{
		if (check_x == player->door_sprite[i].x / TILE_PX
			&& check_y == (player->door_sprite[i].y) / TILE_PX
			&& player->door_sprite[i].open_door)
			return (1);
		i++;
	}
	return (0);
}

int	is_inside_door(t_player *player, int i)
{
	if ((int)player->player_x / TILE_PX == (int)player->door_sprite[i].x / TILE_PX 
		&& (int)player->player_y / TILE_PX == (int)player->door_sprite[i].y / TILE_PX)
		return (1);
	return (0);
}

void	move_keys_handler(mlx_key_data_t keydata, void *v_player)
{
	int			i;
	t_player	*player;

	player = (t_player *)v_player;
	if (keydata.key == MLX_KEY_SPACE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		i = 0;
		while (i < player->doors_count)
		{
			if (calculate_distance_door(player, player->door_sprite, i) < TILE_PX * 2 && !is_inside_door(player, i))
			{
				player->door_sprite[i].start_a = 1;
				player->doorIndex = 0;
			}
			i++;
		}
	}
	movement_key_pressing(keydata, player);
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(player->mlx);
}
