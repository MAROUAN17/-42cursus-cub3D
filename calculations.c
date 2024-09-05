#include "cub3d_header.h"

double degrees2rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

void draw_line(mlx_image_t* img, double x1, double y1, double x2, double y2, uint32_t color) {
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

double	cast_rays(t_player *player)
{
    int i;
	t_point wall_coord1;
	t_point wall_coord2;
    double angle_step;
	double halfFov = player->p_fov_angle / 2;
	double startAngle = player->playerAngle - halfFov;
	double distance = 0;

    i = 0;
    angle_step = player->p_fov_angle / WIDTH;
    while (i < WIDTH)
    {
		printf("----------------------------------------\n");
		player->rays[i].angle = startAngle + (angle_step * i);
		player->rays[i].angle = normalize_rayAngle(player->rays[i].angle);
		update_ray_facing(&player->rays[i]);
		wall_coord1 = calculating_horizontal_intersections(player, &player->rays[i]);
		wall_coord2 = calculating_vertical_intersections(player, &player->rays[i]);
		printf("horizontal wall x -> %f\n", wall_coord1.x);
		printf("horizontal wall y -> %f\n", wall_coord1.y);
		printf("vertical wall x -> %f\n", wall_coord2.x);
		printf("vertical wall y -> %f\n", wall_coord2.y);
		distance = calculate_smallest_distance(player, &player->rays[i], &wall_coord1, &wall_coord2);
        draw_line(player->map_img, player->player_x, player->player_y,
			player->rays[i].x, player->rays[i].y, 0xFF0000FF);
		printf("----------------------------------------\n");
        i++;
    }
	return (distance);
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
		move(player, player->playerAngle);
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move(player, player->playerAngle + M_PI);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move(player, player->playerAngle - M_PI / 2);
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move(player, player->playerAngle + M_PI / 2);
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{	
		player->turnDirection = 1;
		player->playerAngle += player->rotationSpeed * player->turnDirection;
	}
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{	
		player->turnDirection = -1;
		player->playerAngle += player->rotationSpeed * player->turnDirection;
	}
	else if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(player->mlx);
}

void render(void *v_player)
{
	t_player	*player;

	player = (t_player *)v_player;
	mlx_delete_image(player->mlx, player->map_img);
	player->map_img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
	// render
	render_2dmap(player, player->map);
	// draw_line(player->map_img, player->player_x * TILE_PX, player->player_y * TILE_PX,
	// 	cos(player->playerAngle) * 20 + (player->player_x * TILE_PX), sin(player->playerAngle) * 20 + (player->player_y * TILE_PX), 0xFF0000FF);
	draw_rectangle(player->map_img, player->player_x, player->player_y, 0xFF0000FF, 10);
	double distance = cast_rays(player);
	(void)distance;
	// printf("wall x -> %f\n", wall.x);
	// printf("wall y -> %f\n", wall.y);
	// if (wall.x && wall.y)
	// {
	// 	double distance_wall = sqrt(pow(wall.x / TILE_PX - player->player_x / TILE_PX, 2)
	// 		+ pow(wall.y / TILE_PX - player->player_y / TILE_PX, 2));
	// 	printf("distance_wall -> %f\n", distance_wall);
	// }
	// cast_rays(player);
	mlx_image_to_window(player->mlx, player->map_img, 0, 0);
}
