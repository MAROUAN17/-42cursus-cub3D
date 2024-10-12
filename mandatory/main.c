/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 09:47:06 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/12 11:43:41 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

void	free_2d_arr(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	main(int ac, char **av)
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
	if (mlx_image_to_window(player.mlx, player.map_img, 0, 0) == -1)
	{
		mlx_delete_image(player.mlx, player.map_img);
		free_and_exit(&player);
	}
	mlx_key_hook(player.mlx, &move_player, &player);
	mlx_loop_hook(player.mlx, &render, &player);
	mlx_loop(player.mlx);
	destroy_textures(&player);
	free_2d_arr(player.map);
	mlx_terminate(player.mlx);
	return (EXIT_SUCCESS);
}
