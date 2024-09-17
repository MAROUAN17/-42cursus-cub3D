#include "./cub3d_header.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void draw_rectangle_3d(t_player *player, int x, float y, int w, int p, int textOffsetX)
{
	int i = 0;
	int j = 0;
	int Dbottom = 0;
	int textOffsetY = 0;
	int index = 0;
	int color = 0;
	// if (p > HEIGHT)
	// 	p = HEIGHT;
	while (i < w && i < WIDTH)
	{
		j = 0;
		while (j < p && y + j < HEIGHT)
		{
			Dbottom = (y + j) + ((p / 2) - (HEIGHT / 2));
			textOffsetY = Dbottom * ((float)player->walls_texture->height / p);
			index = ((textOffsetY * player->walls_texture->width) + textOffsetX) * 4;
			color = get_rgba(player->walls_texture->pixels[index],
				player->walls_texture->pixels[index + 1], player->walls_texture->pixels[index + 2],
				player->walls_texture->pixels[index + 3]);
			mlx_put_pixel(player->map_img, x + i, y + j, color);
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
