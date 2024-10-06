/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:04 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/06 16:15:50 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

void	print_err(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		write(2, &line[i], 1);
		i++;
	}
}

void	a(void)
{
	system("leaks cub3D_bonus");
}

int	main(int ac, char **av)
{
	t_player		player;
	mlx_texture_t	*c_textures[5];
	mlx_texture_t	*d_textures[4];

	(void)ac;
	if (initialize_all(&player, av[1], c_textures, d_textures))
		return (EXIT_FAILURE);
	mlx_image_to_window(player.mlx, player.map_img, 0, 0);
	mlx_set_cursor_mode(player.mlx, MLX_MOUSE_HIDDEN);
	mlx_key_hook(player.mlx, &move_keys_handler, &player);
	mlx_loop_hook(player.mlx, &render, &player);
	mlx_loop(player.mlx);
	mlx_terminate(player.mlx);
	free_allocated_memory(&player, c_textures, d_textures);
	atexit(a);
	return (EXIT_SUCCESS);
}
