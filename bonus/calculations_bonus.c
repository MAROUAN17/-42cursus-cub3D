/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:01:38 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/23 12:22:59 by maglagal         ###   ########.fr       */
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
			textOffsetX = (int)player->rays[i].y % TILE_PX;
		else
			textOffsetX = (int)player->rays[i].x % TILE_PX;
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

float normalize_rayAngle(float ray_angle)
{
	ray_angle = remainder(ray_angle, 2 * M_PI);
	if (ray_angle < 0)
		ray_angle = (2 * M_PI) + ray_angle;
	return (ray_angle);
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
		// draw_line(player->map_img, player->player_x * MINIMAP_FACTOR, player->player_y * MINIMAP_FACTOR,
		// player->rays[i].x * MINIMAP_FACTOR, player->rays[i].y * MINIMAP_FACTOR, 0xFF0000FF);
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
	float new_x = cos(angle) * player->moveSpeed;
	float new_y = sin(angle) * player->moveSpeed;
	int	check_y;
	int	check_x;
	if (!check_corner(player, new_x, new_y))
	{
		new_x = 0;
		new_y = 0;
	}
	check_y = (player->player_y + new_y) / TILE_PX;
	check_x = (player->player_x + new_x) / TILE_PX;
	if (player->map[check_y][check_x] != '1')

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
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		player->w_key = 0;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		player->s_key = 0;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		player->a_key = 0;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		player->d_key = 0;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE))
		player->turnLeft = 0;
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE))
		player->turnRight = 0;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(player->mlx);
}

void rotate_player(t_player *player, double rotationAngle)
{
	player->playerAngle += rotationAngle;
	player->playerAngle = normalize_rayAngle(player->playerAngle);
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
		rotate_player(player, player->rotationSpeed * 1);
	if (player->turnRight)
		rotate_player(player, player->rotationSpeed * -1);
	cast_rays(player);
	draw_wall(player);
	render_minimap(player);
	draw_casted_rays(player);
	visibleSprite(player);
	draw_rectangle(player->map_img, player->player_x * MINIMAP_FACTOR, player->player_y * MINIMAP_FACTOR,
		0xFF0000FF, 10 * MINIMAP_FACTOR);
	if (player->sprite->visible)
	{	
		draw_rectangle(player->map_img, player->sprite->x * MINIMAP_FACTOR, player->sprite->y * MINIMAP_FACTOR,
			0x00FF00FF, 10 * MINIMAP_FACTOR);
		calculate_sprite_projection_and_render(player);
	}
	else
		draw_rectangle(player->map_img, player->sprite->x * MINIMAP_FACTOR, player->sprite->y * MINIMAP_FACTOR,
			0x0044444F, 10 * MINIMAP_FACTOR);
	mlx_image_to_window(player->mlx, player->map_img, 0, 0);
}
