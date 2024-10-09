/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:01:38 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/08 14:43:54 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

void	render(void *v_player)
{
	static int	tex_index;
	t_player	*player;

	player = (t_player *)v_player;
	mlx_delete_image(player->mlx, player->map_img);
	player->map_img = NULL;
	player->map_img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
	if (tex_index == 51)
		tex_index = 0;
	if (player->door_index == 16)
		player->door_index = 0;
	mouse_rotation(player);
	handle_door(player);
	move_player(player);
	cast_rays_draw(player);
	render_coins(player, tex_index);
	render_minimap(player);
	tex_index++;
	player->door_index++;
	mlx_image_to_window(player->mlx, player->map_img, 0, 0);
}
