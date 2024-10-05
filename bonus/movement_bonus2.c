/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:54:52 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/04 10:34:33 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_b.h"

void rotate_player(t_player *player, float rotationAngle)
{
	player->playerAngle += rotationAngle;
	player->playerAngle = normalize_rayangle(player->playerAngle);
}

void mouse_rotation(t_player *player)
{
	int x;
	int y;
	int deltaX;

	x = 0;
	y = 0;
	mlx_get_mouse_pos(player->mlx, &x, &y);
	deltaX = x - (WIDTH / 2);
	if (deltaX != 0 && x > 0 && x < WIDTH)
	{
		if (deltaX > 0)
			rotate_player(player, (player->rotationSpeed + (player->mlx->delta_time - 0.01)) * 1);
		else if (deltaX < 0)
			rotate_player(player, (player->rotationSpeed + (player->mlx->delta_time - 0.01)) * -1);
	}
	mlx_set_mouse_pos(player->mlx, WIDTH / 2, HEIGHT / 2);
}

void	check_change_position(t_player *player, float angle)
{
	float new_x;
	float new_y;
	int	check_y;
	int	check_x;

	
	new_x = cos(angle) * (player->moveSpeed * player->mlx->delta_time);
	new_y = sin(angle) * (player->moveSpeed * player->mlx->delta_time);
	check_y = (player->player_y + new_y) / TILE_PX;
	check_x = (player->player_x + new_x) / TILE_PX;
	if (player->map[check_y][(int)(player->player_x) / TILE_PX] != '1'
		&& player->map[(int)(player->player_y) / TILE_PX][check_x] != '1'
		&& player->map[check_y][check_x] != '1'
		&& (player->map[check_y][check_x] != 'D'
			|| is_open_door(player, check_x, check_y)))
	{
		player->player_x += new_x;
		player->player_y += new_y;
	}
}

void move_player(t_player *player)
{
	if (player->w_key)
		check_change_position(player, player->playerAngle);
	if (player->s_key)
		check_change_position(player, player->playerAngle + M_PI);
	if (player->a_key)
		check_change_position(player, player->playerAngle - M_PI / 2);
	if (player->d_key)
		check_change_position(player, player->playerAngle + M_PI / 2);
	if (player->turnLeft)
		rotate_player(player, (player->rotationSpeed + player->mlx->delta_time - 0.01) * 1);
	if (player->turnRight)
		rotate_player(player, (player->rotationSpeed + player->mlx->delta_time - 0.01) * -1);
}

void	movement_key_pressing(mlx_key_data_t keydata, t_player *player)
{
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->w_key = 1;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->s_key = 1;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->a_key = 1;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->d_key = 1;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->turnLeft = 1;
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->turnRight = 1;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		player->w_key = 0;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		player->s_key = 0;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		player->a_key = 0;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		player->d_key = 0;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		player->turnLeft = 0;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		player->turnRight = 0;
}
