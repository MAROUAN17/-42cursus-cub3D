/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement3_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:31:43 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_bonus.h"

void	key_press(mlx_key_data_t keydata, t_player *player)
{
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		player->w_key = 1;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		player->s_key = 1;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		player->a_key = 1;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		player->d_key = 1;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		player->turn_left = 1;
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		player->turn_right = 1;
}

void	key_release(mlx_key_data_t keydata, t_player *player)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		player->w_key = 0;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		player->s_key = 0;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		player->a_key = 0;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		player->d_key = 0;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		player->turn_left = 0;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		player->turn_right = 0;
}

void	movement_key_pressing(mlx_key_data_t keydata, t_player *player)
{
	key_press(keydata, player);
	key_release(keydata, player);
}
