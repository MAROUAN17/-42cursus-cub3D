#include "cub3d_header.h"

double degrees2rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

void draw_line(mlx_image_t *img, double x1, double y1, double x2, double y2, int color)
{
	// Calculate differences
    double dx = x2 - x1;
    double dy = y2 - y1;

    // Determine the number of steps needed
    double steps = fmax(fabs(dx), fabs(dy));

    // Calculate increments per step
    double xIncrement = dx / steps;
    double yIncrement = dy / steps;

    // Starting point
    double x = x1;
    double y = y1;

    // Draw the line
    for (int i = 0; i <= steps; i++) {
        mlx_put_pixel(img, (int)round(x), (int)round(y), color); // Plot rounded points
        x += xIncrement;  // Increment x
        y += yIncrement;  // Increment y
    }
}

void draw_rectangle_3d(mlx_image_t *img, int x, int y, int color, int w, int p)
{
	int i = 0;
	int j = 0;
	while (i < w && i < WIDTH)
	{
		j = 0;
		while (j < p && j < HEIGHT)
		{
			mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void draw_wall(t_player *player)
{
	int i = 0;
	double pWallHeight = 0;
	double wall_width = 2;
	double correct_wall_distance = 0;
	int ystart = 0;
	double d_projection = (WIDTH / 2) / tan(degrees2rad(FOV_ANGLE / 2));

	while (i < WIDTH)
	{
		if (player->rays[i].distance_to_wall < 0)
			player->rays[i].distance_to_wall = 0;
		correct_wall_distance = player->rays[i].distance_to_wall * cos(player->rays[i].angle - player->playerAngle);
		if (!correct_wall_distance)
			correct_wall_distance = 0.1;
		pWallHeight = (TILE_PX * d_projection) / correct_wall_distance;
		ystart = (HEIGHT / 2) - ((int)pWallHeight / 2);
		if (ystart < 0)
			ystart = 0;
		draw_rectangle_3d(player->map_img, i, ystart, 0xFFFFFFFF, wall_width, pWallHeight);
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

double normalize_rayAngle(double ray_angle)
{
	ray_angle = remainder(ray_angle, 2 * M_PI);
	if (ray_angle < 0)
		ray_angle = (2 * M_PI) + ray_angle;
	return (ray_angle);
}

void	cast_rays(t_player *player)
{
    int i;
    double angle_step;
	double halfFov = player->p_fov_angle / 2;
	double startAngle = player->playerAngle - halfFov;
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
		draw_line(player->map_img, player->player_x * MINIMAP_FACTOR, player->player_y * MINIMAP_FACTOR,
		player->rays[i].x * MINIMAP_FACTOR, player->rays[i].y * MINIMAP_FACTOR, 0xFF0000FF);
        i++;
    }
}

void	move(t_player *player, double angle)
{
	double new_x = cos(angle) * player->moveSpeed;
	double new_y = sin(angle) * player->moveSpeed;
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
		player->w_key = 'W';
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->s_key = 'S';
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->a_key = 'A';
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->d_key = 'D';
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->turnDirection = 1;
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->turnDirection = -1;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(player->mlx);
}

void render(void *v_player)
{
	t_player	*player;

	player = (t_player *)v_player;
	mlx_delete_image(player->mlx, player->map_img);
	player->map_img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
	// render_2dmap(player, player->map);
	if (player->w_key == 'W')
		move(player, player->playerAngle);
	if (player->s_key == 'S')
		move(player, player->playerAngle + M_PI);
	if (player->a_key == 'A')
		move(player, player->playerAngle - M_PI / 2);
	if (player->d_key == 'D')
		move(player, player->playerAngle + M_PI / 2);
	if (player->turnDirection == 1 || player->turnDirection == -1)
		player->playerAngle += player->rotationSpeed * player->turnDirection;
	player->w_key = 0;
	player->s_key = 0;
	player->a_key = 0;
	player->d_key = 0;
	player->turnDirection = 0;
	draw_wall(player);
	render_minimap(player);
	cast_rays(player);
	draw_rectangle(player->map_img, player->player_x * MINIMAP_FACTOR, player->player_y * MINIMAP_FACTOR,
		0xFF0000FF, 10 * MINIMAP_FACTOR);
	mlx_image_to_window(player->mlx, player->map_img, 0, 0);
}
