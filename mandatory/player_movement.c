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
				player->player_x = x * TILE_PX + (TILE_PX / 2);
				player->player_y = y * TILE_PX + (TILE_PX / 2);
			}
			x++;
		}
		y++;
	}
}

void key_press(t_player *player, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->w_key = 1;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->s_key = 1;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->a_key = 1;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->d_key = 1;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->turn_left = 1;
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->turn_right = 1;
}

void key_release(t_player *player, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		player->w_key = 0;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		player->s_key = 0;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		player->a_key = 0;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		player->d_key = 0;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE))
		player->turn_left = 0;
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE))
		player->turn_right = 0;
}
