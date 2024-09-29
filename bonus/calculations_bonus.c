/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:01:38 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/29 10:32:40 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

float degrees2rad(float degrees)
{
	return (degrees * (M_PI / 180.0));
}

void draw_line(mlx_image_t *img, float x1, float y1, float x2, float y2, int color)
{
	// Calculate differences
    float dx = x2 - x1;
    float dy = y2 - y1;

    // Determine the number of steps needed
    float steps = fmax(fabs(dx), fabs(dy));

    // Calculate increments per step
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    // Starting point
    float x = x1;
    float y = y1;

    // Draw the line
    for (int i = 0; i <= steps; i++) {
		if (x > 0 && y > 0)
    		mlx_put_pixel(img, (int)round(x), (int)round(y), color); // Plot rounded points
        x += xIncrement;  // Increment x
        y += yIncrement;  // Increment y
    }
}


float calculate_biggest_distance(t_player *player, t_ray *ray, t_point *wall1, t_point *wall2)
{
	float distance1 = 0;
	float distance2 = 0;

	distance1 = sqrt(pow(wall1->x - player->player_x, 2) + pow(wall1->y - player->player_y, 2));
	distance2 = sqrt(pow(wall2->x - player->player_x, 2) + pow(wall2->y - player->player_y, 2));
    if (wall1->x == -1)
    {
        ray->x = wall2->x;
        ray->y = wall2->y;
        ray->horizontal_wall = 0;
        ray->vertical_wall = 1;
        return (distance2);
    }
    else if (wall2->x == -1)
    {
        ray->x = wall1->x;
        ray->y = wall1->y;
        ray->horizontal_wall = 1;
        ray->vertical_wall = 0;
        return (distance1);
    }
    else
    {
        if (distance1 < distance2)
        {
            ray->x = wall1->x;
            ray->y = wall1->y;
            ray->horizontal_wall = 1;
            ray->vertical_wall = 0;
            return (distance1);
        }
        else
        {
            ray->x = wall2->x;
            ray->y = wall2->y;
            ray->horizontal_wall = 0;
            ray->vertical_wall = 1;
            return (distance2);
        }
    }
}

float get_smallest_door_distance(t_player *player, t_ray *ray, int j)
{
	t_point p1;
	t_point p2;
	float distance;

	p1.x = ray->d_h_xintersept[j];
	p1.y = ray->d_h_yintersept[j];
	p2.x = ray->d_v_xintersept[j];
	p2.y = ray->d_v_yintersept[j];
	
	float tmp_x = ray->x;
	float tmp_y = ray->y;

	distance = calculate_biggest_distance(player, ray, &p1, &p2);
	ray->d_x = ray->x;
	ray->d_y = ray->y;
	ray->x = tmp_x;
	ray->y = tmp_y;
	return (distance);
}

void	draw_door(t_player *player, float x, float y, int i, float distance)
{
	int textOffsetX = 0;
	float pWallHeight = 0;
	float wall_width = 1;
	float correct_wall_distance = 0;
	int ystart = 0;
	float d_projection = (WIDTH / 2) / tan(degrees2rad(FOV_ANGLE / 2));
	(void)distance;
	// player->rays[i].distance_to_door = distance;
	player->rays[i].distance_to_door = sqrt(pow(player->player_x - x, 2) + pow(player->player_y - y, 2));
	if (player->rays[i].distance_to_door < 0)
		player->rays[i].distance_to_door = 0;
	correct_wall_distance = fabs(player->rays[i].distance_to_door * cos(player->rays[i].angle - player->playerAngle));
	if (!correct_wall_distance)
		correct_wall_distance = 0.001;
	pWallHeight = (TILE_PX * d_projection) / correct_wall_distance;
	ystart = (HEIGHT / 2) - ((int)pWallHeight / 2);
	if (ystart < 0)
		ystart = 0;
	int j = 0;
	while (j < player->doors_count)
	{
		visibleSprite(player, player->door_sprite, j);
		if (player->door_sprite[j].visible
			&& x >= player->door_sprite[j].x && x <= player->door_sprite[j].x + TILE_PX
			&& y >= player->door_sprite[j].y && y <= player->door_sprite[j].y + TILE_PX)
		{
			if (player->rays[i].vertical_wall)
				textOffsetX = (int)y % player->door_sprite[j].texture->width;
			else
				textOffsetX = (int)x % player->door_sprite[j].texture->width;
			if (player->door_sprite[j].open_door == 0)
				player->rays[i].distance_to_wall = player->rays[i].distance_to_door;
			draw_rectangle_3d(player, i, ystart, wall_width, pWallHeight, textOffsetX, player->door_sprite[j].texture);
		}
		j++;
	}
}

void draw_wall(t_player *player)
{
	int textOffsetX = 0;
	int i = 0;
	float pWallHeight = 0;
	float wall_width = 1;
	float correct_wall_distance = 0;
	int ystart = 0;
	float d_projection = (WIDTH / 2) / tan(degrees2rad(FOV_ANGLE / 2));
	float n_distance_to_wall;

	while (i < WIDTH)
	{
		if (player->rays[i].distance_to_wall < 0)
			player->rays[i].distance_to_wall = 0;
		correct_wall_distance = fabs(player->rays[i].distance_to_wall * cos(player->rays[i].angle - player->playerAngle));
		if (!correct_wall_distance)
			correct_wall_distance = 0.001;
		pWallHeight = (TILE_PX * d_projection) / correct_wall_distance;
		ystart = (HEIGHT / 2) - ((int)pWallHeight / 2);
		if (ystart < 0)
			ystart = 0;
		draw_ceiling(player->map_img, i, ystart, player->ceiling_color, wall_width);
		if (player->rays[i].vertical_wall)
			textOffsetX = (int)player->rays[i].y % player->rays[i].texture->width;
		else
			textOffsetX = (int)player->rays[i].x % player->rays[i].texture->width;
		draw_rectangle_3d(player, i, ystart, wall_width, pWallHeight, textOffsetX, player->rays[i].texture);
		if (ystart + pWallHeight < HEIGHT)
			draw_floor(player->map_img, i, ystart + pWallHeight, player->floor_color, wall_width);
		int j = 2;
		while (j >= 0)
		{
			if ((player->rays[i].d_h_xintersept[j] != -1 && player->rays[i].d_h_yintersept[j] != -1)
				|| (player->rays[i].d_v_xintersept[j] != -1 && player->rays[i].d_v_yintersept[j] != -1))
				n_distance_to_wall = get_smallest_door_distance(player, &player->rays[i], j);
			if (((player->rays[i].d_h_xintersept[j] != -1 && player->rays[i].d_h_yintersept[j] != -1)
				|| (player->rays[i].d_v_xintersept[j] != -1 && player->rays[i].d_v_yintersept[j] != -1))
					&& n_distance_to_wall < player->rays[i].distance_to_wall)
			{
				float h_d = sqrt(pow(player->player_x - player->rays[i].d_h_xintersept[j], 2) + pow(player->player_y - player->rays[i].d_h_yintersept[j], 2));
				float v_d = sqrt(pow(player->player_x - player->rays[i].d_v_xintersept[j], 2) + pow(player->player_y - player->rays[i].d_v_yintersept[j], 2));
				if (player->rays[i].vertical_wall && player->rays[i].d_v_xintersept[j] != -1 && player->rays[i].d_h_xintersept[j] != -1)
				{
					player->rays[i].vertical_wall = 0;
					if (h_d < player->rays[i].distance_to_wall)
						draw_door(player, player->rays[i].d_h_xintersept[j], player->rays[i].d_h_yintersept[j], i, n_distance_to_wall);
					player->rays[i].vertical_wall = 1;
						draw_door(player, player->rays[i].d_v_xintersept[j], player->rays[i].d_v_yintersept[j], i, n_distance_to_wall);
				}
				else if (player->rays[i].d_h_xintersept[j] != -1 && player->rays[i].d_v_xintersept[j] != -1)
				{
					player->rays[i].vertical_wall = 1;
					if (v_d < player->rays[i].distance_to_wall)
						draw_door(player, player->rays[i].d_v_xintersept[j], player->rays[i].d_v_yintersept[j], i, n_distance_to_wall);
					player->rays[i].vertical_wall = 0;
						draw_door(player, player->rays[i].d_h_xintersept[j], player->rays[i].d_h_yintersept[j], i, n_distance_to_wall);
				}
				else
					draw_door(player, player->rays[i].d_x, player->rays[i].d_y, i, n_distance_to_wall);
			}
			j--;
		}
		// if (ystart + pWallHeight < HEIGHT)
		// 	draw_floor(player->map_img, i, ystart + pWallHeight, player->floor_color, wall_width);
		i++;
	}
}

void	draw_casted_rays(t_player *player)
{
	int i = 0;
	while (i < WIDTH)
	{
		draw_line(player->map_img, player->player_x * MINIMAP_FACTOR, player->player_y * MINIMAP_FACTOR,
			player->rays[i].x * MINIMAP_FACTOR, player->rays[i].y * MINIMAP_FACTOR, 0xFF0000FF);
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

void	cast_rays(t_player *player)
{
    int i;
    float angle_step;
	float halfFov = player->p_fov_angle / 2;
	float startAngle = player->playerAngle - halfFov;
	t_point wall_coord1;
	t_point wall_coord2;

    i = 0;
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

void handle_door(t_player *player, int *doorIndex)
{
	int i = 0;
	while (i < player->doors_count)
	{
		if (player->door_sprite[i].start_a && player->door_sprite[i].open_door == 0)
		{
			player->door_sprite[i].texture = player->door_sprite[i].an_textures[*doorIndex / 10];
			if (*doorIndex == 30)
			{
				player->door_sprite[i].open_door = 1;
				player->door_sprite[i].start_a = 0;
			}
		}
		else if (player->door_sprite[i].start_a && player->door_sprite[i].open_door)
		{
			player->door_sprite[i].texture = player->door_sprite[i].an_textures[3 - (*doorIndex / 10)];
			if (*doorIndex == 30)
			{
				player->door_sprite[i].open_door = 0;
				player->door_sprite[i].start_a = 0;
			}
		}
		i++;
	}
}

void render(void *v_player)
{
	static int texIndex;
	static int doorIndex;
	t_player	*player;

	player = (t_player *)v_player;
	mlx_delete_image(player->mlx, player->map_img);
	player->map_img = NULL;
	player->map_img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
	mouse_rotation(player);
	if (texIndex == 51)
		texIndex = 0;
	if (doorIndex == 31)
		doorIndex = 0;
	handle_door(player, &doorIndex);
	if (player->w_key)
		check_change_position(player, player->playerAngle);
	if (player->s_key)
		check_change_position(player, player->playerAngle + M_PI);
	if (player->a_key)
		check_change_position(player, player->playerAngle - M_PI / 2);
	if (player->d_key)
		check_change_position(player, player->playerAngle + M_PI / 2);
	if (player->turnLeft)
		rotate_player(player, player->rotationSpeed * 1);
	if (player->turnRight)
		rotate_player(player, player->rotationSpeed * -1);
	cast_rays(player);
	draw_wall(player);
	render_minimap(player);
	draw_casted_rays(player);
	draw_rectangle(player->map_img, player->player_x * MINIMAP_FACTOR, player->player_y * MINIMAP_FACTOR,
		0xFF0000FF, 10 * MINIMAP_FACTOR);
	render_sprites(player, texIndex);
	// render_door(player);
	texIndex++;
	doorIndex++;
	mlx_image_to_window(player->mlx, player->map_img, 0, 0);
}
