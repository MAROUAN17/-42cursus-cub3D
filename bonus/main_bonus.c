/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:04 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/25 14:44:25 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

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
			else if (map[y][x] == 'I')
			{
				player->sprite->x = x * TILE_PX;
				player->sprite->x = y * TILE_PX;
			}
			else
			{
				if (player->player_x == -1 && player->player_y == -1 && (player->map[y][x] == 'N' || player->map[y][x] == 'S' || player->map[y][x] == 'W' || player->map[y][x] == 'E'))
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
	int			map_width;
	int			map_height;
	t_player	player;
	t_ray		rays[WIDTH];
	t_sprite	sprite[NUM_SPRITE];
	mlx_texture_t *textures[5];

	(void)ac;
	map_width = 0;
	map_height = 0;
	textures[0] = mlx_load_png("./textures/MonedaD1.png");
	textures[1] = mlx_load_png("./textures/MonedaD2.png");
	textures[2] = mlx_load_png("./textures/MonedaD3.png");
	textures[3] = mlx_load_png("./textures/MonedaD4.png");
	textures[4] = mlx_load_png("./textures/MonedaD5.png");
	initialize_player_struct(&player, av[1], &map_width, &map_height);
	initialize_rays_struct(&player, rays);
	initialize_sprites_struct(&player, sprite, textures);
	mlx_image_to_window(player.mlx, player.map_img, 0, 0);
	mlx_key_hook(player.mlx, &move_player, &player);
	mlx_loop_hook(player.mlx, &render, &player);
	mlx_loop(player.mlx);
	mlx_terminate(player.mlx);
	free_2d_arr(player.map);
	return (EXIT_SUCCESS);
}
