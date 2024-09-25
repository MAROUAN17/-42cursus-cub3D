/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:04 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/25 17:55:18 by maglagal         ###   ########.fr       */
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
