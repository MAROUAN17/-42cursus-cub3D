/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:10:50 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/05 13:34:59 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

float	degrees2rad(float degrees)
{
	return (degrees * (M_PI / 180.0));
}

void	draw_wall(t_player *player)
{
	int		textOffsetX;
	int		i;
	int		ystart;
	// float	pWallHeight;
	// float	correct_wall_distance;
	// float	d_projection;

	i = 0;
	// pWallHeight = 0;
	ystart = 0;
	// d_projection = (WIDTH / 2) / tan(degrees2rad(FOV_ANGLE / 2));
	while (i < WIDTH)
	{
		player->rays[i].wall_height = calculate_wall_height(player, i);
		ystart = (HEIGHT / 2) - ((int)player->rays[i].wall_height / 2);
		if (ystart < 0)
			ystart = 0;
		draw_ceiling(player->map_img, i, ystart, player->ceiling_color, 1);
		textOffsetX = calculate_offsetx_walls(player, i);
		draw_walls(player, i, ystart, textOffsetX);
		if (ystart + player->rays[i].wall_height < HEIGHT)
			draw_floor(player->map_img, i, ystart + player->rays[i].wall_height, player->floor_color, 1);
		i++;
	}
}

void	update_ray_facing(t_ray *ray)
{
	ray->p_isFacingDown = 0;
	ray->p_isFacingUp = 0;
	ray->p_isFacingRight = 0;
	ray->p_isFacingLeft = 0;
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->p_isFacingDown = 1;
	ray->p_isFacingUp = !ray->p_isFacingDown;
	if (ray->angle < M_PI / 2 || ray->angle > (1.5 * M_PI))
		ray->p_isFacingRight = 1;
	ray->p_isFacingLeft = !ray->p_isFacingRight;
}

float normalize_rayAngle(float ray_angle)
{
	ray_angle = remainder(ray_angle, 2 * M_PI);
	if (ray_angle < 0)
		ray_angle = (2 * M_PI) + ray_angle;
	if (fabs(tan(ray_angle)) < 0.000001)
		ray_angle += 0.0001;
	return (ray_angle);
}

void	cast_rays(t_player *player)
{
	int i;
	float angle_step;
	float halfFov;
	float startAngle;
	t_point wall_coord1;
	t_point wall_coord2;

	i = 0;
	halfFov = player->p_fov_angle / 2;
	startAngle = player->playerAngle - halfFov;
	angle_step = player->p_fov_angle / WIDTH;
	while (i < WIDTH)
	{
		player->rays[i].angle = startAngle + (angle_step * i);
		player->rays[i].angle = normalize_rayAngle(player->rays[i].angle);
		update_ray_facing(&player->rays[i]);
		wall_coord1 = calculating_horizontal_intersections(player, &player->rays[i]);
		wall_coord2 = calculating_vertical_intersections(player, &player->rays[i]);
		player->rays[i].distance_to_wall = calculate_smallest_distance(player, &player->rays[i],
			&wall_coord1, &wall_coord2);
		player->rays[i].texture = get_texture(player, player->rays[i].vertical_wall, player->rays[i].x, player->rays[i].y);
		i++;
	}
}

int	check_corner(t_player *player, double new_x, double new_y)
{
	int	check_y;
	int	check_x;
	(void)new_x;

	check_y = (player->player_y + new_y) / TILE_PX;
	check_x = (player->player_x) / TILE_PX;
	if (player->map[check_y][check_x] != '1')
		return (1);
	return (0);
}

void	move(t_player *player, float angle)
{
	float new_x;
	float new_y;

	new_x = cos(angle) * (player->moveSpeed * player->mlx->delta_time);
	new_y = sin(angle) * (player->moveSpeed * player->mlx->delta_time);
	if (!check_corner(player, new_x, new_y))
		return ;
	if (player->map[(int)((player->player_y + new_y) / TILE_PX)][(int)((player->player_x + new_x) / TILE_PX)] != '1')
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

void render(void *v_player)
{
	t_player	*player;

	player = (t_player *)v_player;
	mlx_delete_image(player->mlx, player->map_img);
	player->map_img = NULL;
	player->map_img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
	if (player->w_key)
		move(player, player->playerAngle);
	if (player->s_key)
		move(player, player->playerAngle + M_PI);
	if (player->a_key)
		move(player, player->playerAngle - M_PI / 2);
	if (player->d_key)
		move(player, player->playerAngle + M_PI / 2);
	if (player->turnLeft)
		player->playerAngle += (player->rotationSpeed 
			+ player->mlx->delta_time) * 1;
	if (player->turnRight)
		player->playerAngle += (player->rotationSpeed 
			+ player->mlx->delta_time) * -1;
	cast_rays(player);
	draw_wall(player);
	mlx_image_to_window(player->mlx, player->map_img, 0, 0);
}
