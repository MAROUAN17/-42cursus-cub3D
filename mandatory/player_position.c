#include "cub3d_header.h"

void draw_rectangle(mlx_image_t *img, float x, float y, int color, float p)
{
	float i = 0;
	float j = 0;
	while (i < p && x + j < WIDTH)
	{
		j = 0;
		while (j < p && y + i < HEIGHT)
		{
			// printf("y + i -> %f\n", y + i);
			mlx_put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void save_player_coordinates(t_player *player)
{
	int     x = 0;
	int     y = 0;

	while (player->map[y])
	{
		x = 0;
		while (player->map[y][x])
		{
			if (player->player_x == -1 && player->player_y == -1 && (player->map[y][x] == 'N' || player->map[y][x] == 'S' || player->map[y][x] == 'W' || player->map[y][x] == 'E'))
			{
				player->player_x = x * TILE_PX;
				player->player_y = y * TILE_PX;
			}
			x++;
		}
		y++;
	}
}
