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
				if (player->player_x == -1 && player->player_y == -1 && (player->map[y][x] == 'N' || player->map[y][x] == 'S' || player->map[y][x] == 'W' || player->map[y][x] == 'E'))
				{	
					// if (player->map[y][x] == 'N')
					// 	player->playerAngle = 3 * M_PI / 2;
					// else if (player->map[y][x] == 'S')
					// 	player->playerAngle = (M_PI / 2);
					// else if (player->map[y][x] == 'W')
					// 	player->playerAngle = 2 * (M_PI / 2);
					// else if (player->map[y][x] == 'E')
					// 	player->playerAngle = 0;
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
	int			map_width;
	int			map_height;
	t_player	player;
	t_ray		rays[WIDTH];

	(void)ac;
	map_width = 0;
	map_height = 0;
	initialize_player_struct(&player, av[1], &map_width, &map_height);
	initialize_rays_struct(&player, rays);
	mlx_image_to_window(player.mlx, player.map_img, 0, 0);
	mlx_key_hook(player.mlx, &move_player, &player);
	mlx_loop_hook(player.mlx, &render, &player);
	mlx_loop(player.mlx);
	mlx_terminate(player.mlx);
	free_2d_arr(player.map);
	return (EXIT_SUCCESS);
}
