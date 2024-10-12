/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:54:52 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_bonus.h"

void	rotate_player(t_player *player, float rotationAngle)
{
	player->player_angle += rotationAngle;
	player->player_angle = normalize_ray_angle(player->player_angle);
}

void	mouse_rotation(t_player *player)
{
	int	x;
	int	y;
	int	delta_x;

	x = 0;
	y = 0;
	mlx_get_mouse_pos(player->mlx, &x, &y);
	delta_x = x - (WIDTH / 2);
	if (delta_x != 0 && x > 0 && x < WIDTH)
	{
		if (delta_x > 0)
			rotate_player(player, (player->rotation_speed
					+ (player->mlx->delta_time - 0.01)) * 1);
		else if (delta_x < 0)
			rotate_player(player, (player->rotation_speed
					+ (player->mlx->delta_time - 0.01)) * -1);
	}
	mlx_set_mouse_pos(player->mlx, WIDTH / 2, HEIGHT / 2);
}

void	check_change_position(t_player *player, float angle)
{
	float	new_x;
	float	new_y;
	int		check_y;
	int		check_x;

	new_x = cos(angle) * (player->move_speed * player->mlx->delta_time);
	new_y = sin(angle) * (player->move_speed * player->mlx->delta_time);
	check_y = (player->player_y + new_y) / TILE_PX;
	check_x = (player->player_x + new_x) / TILE_PX;
	if (player->map[check_y][(int)player->player_x / TILE_PX] != '1'
		&& player->map[(int)player->player_y / TILE_PX][check_x] != '1'
		&& player->map[check_y][check_x] != '1'
		&& (player->map[check_y][check_x] != 'D'
			|| is_open_door(player, check_x, check_y)))
	{
		player->player_x += new_x;
		player->player_y += new_y;
	}
}

void	move_player(t_player *player)
{
	if (player->w_key)
		check_change_position(player, player->player_angle);
	if (player->s_key)
		check_change_position(player, player->player_angle + M_PI);
	if (player->a_key)
		check_change_position(player, player->player_angle - M_PI / 2);
	if (player->d_key)
		check_change_position(player, player->player_angle + M_PI / 2);
	if (player->turn_left)
		rotate_player(player, (player->rotation_speed
				+ player->mlx->delta_time - 0.01) * 1);
	if (player->turn_right)
		rotate_player(player,
			(player->rotation_speed + player->mlx->delta_time - 0.01) * -1);
}
