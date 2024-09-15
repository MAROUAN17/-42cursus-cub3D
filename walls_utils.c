#include "./cub3d_header.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void draw_rectangle_3d(t_player *player, mlx_image_t *img, int x, int y, int w, int p, int textOffsetX)
{
	int i = 0;
	int j = 0;
	// (void)player;
	while (i < w && i < WIDTH)
	{
		j = 0;
		while (j < p && j < HEIGHT)
		{
			// int jBottom = abs(j + ((p / 2) - (HEIGHT / 2)));
			int textOffsetY = j * ((double)player->walls_texture->height / p);
			unsigned int index = ((textOffsetY * player->walls_texture->width) + textOffsetX) * 4;
			int color = get_rgba(player->walls_texture->pixels[index], player->walls_texture->pixels[index + 1], player->walls_texture->pixels[index + 2], player->walls_texture->pixels[index + 3]);
			mlx_put_pixel(img, x + i, y + j, color);
			// mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void draw_ceiling(mlx_image_t *img, int x, int y, int color, int w)
{
    int i = 0;
	int j = 0;

	while (i < w && i < WIDTH)
	{
		j = 0;
		while (j < y && j < HEIGHT)
		{
			mlx_put_pixel(img, x + i, j, color);
			j++;
		}
		i++;
	}
}

void draw_floor(mlx_image_t *img, int x, int y, int color, int w)
{
    int i = 0;
	int j = 0;
	while (i < w && i < WIDTH)
	{
		j = 0;
		while (y + j < HEIGHT)
		{
			mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
