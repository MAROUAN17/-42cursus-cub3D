/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:10:50 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/09 11:27:21 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

void	cast_rays(t_player *player)
{
	int		i;
	float	angle_step;
	float	start_angle;
	t_point	wall_coord1;
	t_point	wall_coord2;

	i = 0;
	start_angle = player->player_angle - (player->p_fov_angle / 2);
	angle_step = player->p_fov_angle / WIDTH;
	while (i < WIDTH)
	{
		player->rays[i].angle = start_angle + (angle_step * i);
		player->rays[i].angle = normalize_ray_angle(player->rays[i].angle);
		update_ray_facing(&player->rays[i]);
		wall_coord1 = calculating_horizontal_intersections(player,
				&player->rays[i]);
		wall_coord2 = calculating_vertical_intersections(player,
				&player->rays[i]);
		player->rays[i].distance_to_wall = calculate_smallest_distance(player,
				&player->rays[i], &wall_coord1, &wall_coord2);
		player->rays[i].texture = get_texture(player,
				player->rays[i].vertical_wall, player->rays[i].x,
				player->rays[i].y);
		i++;
	}
}

int	check_corner(t_player *player, double new_y)
{
	int	check_y;
	int	check_x;

	check_y = (player->player_y + new_y) / TILE_PX;
	check_x = (player->player_x) / TILE_PX;
	if (player->map[check_y][check_x] != '1')
		return (1);
	return (0);
}

void	move(t_player *player, float angle)
{
	float	new_x;
	float	new_y;
	int		check_y;
	int		check_x;

	new_x = cos(angle) * (player->move_speed * player->mlx->delta_time);
	new_y = sin(angle) * (player->move_speed * player->mlx->delta_time);
	check_x = (player->player_x + new_x) / TILE_PX;
	check_y = (player->player_y + new_y) / TILE_PX;
	if (!check_corner(player, new_y))
		return ;
	if (player->map[check_y][(int)player->player_x / TILE_PX] != '1'
		&& player->map[(int)player->player_y / TILE_PX][check_x] != '1'
		&& player->map[check_y][check_x] != '1')
	{
		player->player_x += new_x;
		player->player_y += new_y;
	}
}

void	move_player(mlx_key_data_t keydata, void *v_player)
{
	t_player	*player;

	player = (t_player *)v_player;
	key_press(player, keydata);
	key_release(player, keydata);
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(player->mlx);
}

void	render(void *v_player)
{
	t_player	*player;

	player = (t_player *)v_player;
	mlx_delete_image(player->mlx, player->map_img);
	player->map_img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
	if (!player->map_img)
		mlx_close_window(player->mlx);
	if (mlx_image_to_window(player->mlx, player->map_img, 0, 0) == -1)
		mlx_close_window(player->mlx);
	if (player->w_key)
		move(player, player->player_angle);
	if (player->s_key)
		move(player, player->player_angle + M_PI);
	if (player->a_key)
		move(player, player->player_angle - M_PI / 2);
	if (player->d_key)
		move(player, player->player_angle + M_PI / 2);
	if (player->turn_left)
		player->player_angle += (player->rotation_speed
				+ player->mlx->delta_time) * 1;
	if (player->turn_right)
		player->player_angle += (player->rotation_speed
				+ player->mlx->delta_time) * -1;
	cast_rays(player);
	draw_wall(player);
}
