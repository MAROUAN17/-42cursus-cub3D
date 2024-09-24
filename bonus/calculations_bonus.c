/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:01:38 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/24 15:19:23 by oait-laa         ###   ########.fr       */
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

void draw_wall(t_player *player)
{
	int textOffsetX = 0;
	int i = 0;
	float pWallHeight = 0;
	float wall_width = 1;
	float correct_wall_distance = 0;
	int ystart = 0;
	float d_projection = (WIDTH / 2) / tan(degrees2rad(FOV_ANGLE / 2));

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

void my_scrollhook(double xdelta, double ydelta, void* param)
{
	(void)param;
	(void)ydelta;
	if (xdelta < 0)
		printf("left\n");
	else if (xdelta > 0)
		printf("right\n");
}

void render(void *v_player)
{
	static int texIndex;
	t_player	*player;

	player = (t_player *)v_player;
	mlx_delete_image(player->mlx, player->map_img);
	player->map_img = NULL;
	player->map_img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
	mouse_rotation(player);
	if (texIndex == 51)
		texIndex = 0;
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
	texIndex++;
	mlx_image_to_window(player->mlx, player->map_img, 0, 0);
}
