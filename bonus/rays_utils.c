/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:52:01 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/08 14:39:45 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_b.h"

float	degrees2rad(float degrees)
{
	return (degrees * (M_PI / 180.0));
}

void	draw_ray_projection(t_player *player, int i)
{
	int	textoffsetx;
	int	ystart;

	ystart = 0;
	textoffsetx = 0;
	player->rays[i].wall_height = calculate_wall_height(player, i);
	ystart = (HEIGHT / 2) - ((int)player->rays[i].wall_height / 2);
	if (ystart < 0)
		ystart = 0;
	draw_ceiling(player->map_img, i, ystart, player->ceiling_color);
	if (player->rays[i].vertical_wall)
		textoffsetx = (int)player->rays[i].y % player->rays[i].texture->width;
	else
		textoffsetx = (int)player->rays[i].x % player->rays[i].texture->width;
	draw_rectangle_3d(player, i, ystart, textoffsetx);
	if (ystart + player->rays[i].wall_height < HEIGHT)
		draw_floor(player->map_img, i,
			ystart + player->rays[i].wall_height, player->floor_color);
}

void	update_ray_facing(t_ray *ray)
{
	ray->p_is_facing_down = 0;
	ray->p_is_facing_up = 0;
	ray->p_is_facing_right = 0;
	ray->p_is_facing_left = 0;
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->p_is_facing_down = 1;
	ray->p_is_facing_up = !ray->p_is_facing_down;
	if (ray->angle < M_PI / 2 || ray->angle > (1.5 * M_PI))
		ray->p_is_facing_right = 1;
	ray->p_is_facing_left = !ray->p_is_facing_right;
}

void	calculate_ray(t_player *player, float start_angle,
			float angle_step, int i)
{
	t_point	wall_coord1;
	t_point	wall_coord2;

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
	draw_ray_projection(player, i);
	handle_door_intersect(player, i);
}

void	cast_rays_draw(t_player *player)
{
	int		i;
	float	angle_step;
	float	half_fov;
	float	start_angle;

	i = 0;
	half_fov = player->p_fov_angle / 2;
	start_angle = player->player_angle - half_fov;
	angle_step = player->p_fov_angle / WIDTH;
	while (i < WIDTH)
	{
		calculate_ray(player, start_angle, angle_step, i);
		i++;
	}
}
