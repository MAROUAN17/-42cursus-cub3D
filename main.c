#include "cub3d_header.h"

void free_2d_arr(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**store_2d_array(char *map_path, int *map_height, int *map_width)
{
	int		fd;
	char	*line;
	char	**d_map;
	int		i = 0;

	fd = open(map_path, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		*map_width = ft_strlen(line);
		free(line);
		(*map_height)++;
	}
	close(fd);
	fd = open(map_path, O_RDONLY);
	d_map = malloc(sizeof(char *) * (*map_height + 1));
	while (i < *map_height)
	{
		d_map[i] = ft_strdup(get_next_line(fd));
		free(line);
		i++;
	}
	d_map[i] = NULL;
	close(fd);
	return (d_map);
}

void draw_rectangle(mlx_image_t *img, int x, int y, int color, int p)
{
	int i = 0;
	int j = 0;
	while (i < p)
	{
		j = 0;
		while (j < p)
		{
			mlx_put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void render_2dmap(t_player *player, char **map)
{
	int x = 0;
	int y = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_rectangle(player->map_img, x * TILE_PX, y * TILE_PX, 0x000000FF, TILE_PX);
			else
			{
				if (player->player_x == -1 && player->player_y == -1 && map[y][x] == 'P')
				{	
					player->player_x = x * TILE_PX;
					player->player_y = y * TILE_PX;
				}
				draw_rectangle(player->map_img, x * TILE_PX, y * TILE_PX, 0xFFFFFFFF, TILE_PX);
			}
			x++;
		}
		y++;
	}
}

int main(int ac, char **av)
{
	mlx_t		*mlx;
	int			map_width;
	int			map_height;
	t_player	player;
	t_ray		rays[WIDTH];

	(void)ac;
	player.p_fov_angle = degrees2rad(60);
	map_width = 0;
	map_height = 0;
	player.player_x = -1;
	player.player_y = -1;
	int i = 0;
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true)))
	{
		free_2d_arr(player.map);
		perror(strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_image_t *map_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	player.map_img = map_img;
	while (i < WIDTH)
	{
		rays[i].map_img = map_img;
		rays[i].h_xintersept = 0;
		rays[i].h_yintersept = 0;
		rays[i].v_xintersept = 0;
		rays[i].v_yintersept = 0;
		rays[i].p_isFacingDown = 0;
		rays[i].p_isFacingUp = 0;
		rays[i].p_isFacingRight = 0;
		rays[i].p_isFacingLeft = 0;
		i++;
	}
	player.playerAngle = M_PI / 2;
	player.moveSpeed = 12.0;
	player.rotationSpeed = degrees2rad(8);
	player.map = store_2d_array(av[1], &map_height, &map_width);
	player.map_height = map_height;
	player.map_width = map_width;
	player.rays = rays;
	player.mlx = mlx;
	// mlx_texture_t *texture = mlx_load_png("./textures/white_image.png");
	// player.white_img = mlx_texture_to_image(player.mlx, texture);
	// mlx_texture_t *texture2 = mlx_load_png("./textures/dot.png");
	// player.player_img = mlx_texture_to_image(player.mlx, texture2);
	// mlx_texture_t *texture3 = mlx_load_png("./textures/red_dot.png");
	// player.view_img = mlx_texture_to_image(player.mlx, texture3);
	// render_2dmap(&player, player.map);
	// cast_rays(&player);
	mlx_image_to_window(mlx, player.map_img, 0, 0);
	mlx_key_hook(mlx, &move_player, &player);
	mlx_loop_hook(mlx, &render, &player);
	// double n_point_y = find_closest_horizontal_yintersec(player.player_y);
	// double n_point_x = find_closest_horizontal_xintersec(player.player_x, player.player_y, n_point_y);
	// int xstep = calculate_xstep();
	// printf("player x -> %d\n", player.player_x);
	// printf("player y -> %d\n", player.player_y);
	// printf("closest horizontal intersection point x -> %f\n", n_point_x);
	// printf("closest horizontal intersection point y -> %f\n", n_point_y);
	// printf("xstep -> %d\n", xstep);
	// mlx_image_t *img = mlx_new_image(mlx, map_width * TILE_PX, map_height * TILE_PX);
	// if (mlx_image_to_window(mlx, img, 0, 0) == -1)
	// {
	// 	mlx_close_window(mlx);
	// 	perror(strerror(mlx_errno));
	// 	return (EXIT_FAILURE);
	// }
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_2d_arr(player.map);
	return (EXIT_SUCCESS);
}
