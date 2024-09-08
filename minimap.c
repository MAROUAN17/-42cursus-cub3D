#include "./cub3d_header.h"

void render_minimap(t_player *player)
{
	int     x = 0;
	int     y = 0;
    double  minimap_scale_factor = 0.2;

	while (player->map[y])
	{
		x = 0;
		while (player->map[y][x])
		{
			if (player->map[y][x] == '1')
				draw_rectangle(player->map_img, (x * TILE_PX) * minimap_scale_factor, (y * TILE_PX) * minimap_scale_factor, 0x000000FF, TILE_PX * 0.2);
			else
			{
				if (player->player_x == -1 && player->player_y == -1 && player->map[y][x] == 'P')
				{	
					player->player_x = x * TILE_PX;
					player->player_y = y * TILE_PX;
				}
				draw_rectangle(player->map_img, (x * TILE_PX) * minimap_scale_factor, (y * TILE_PX) *   minimap_scale_factor, 0xFFFFFFFF, TILE_PX * 0.2);
			}
			x++;
		}
		y++;
	}
}
