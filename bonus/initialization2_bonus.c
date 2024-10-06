/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:08:23 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/06 16:14:57 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_b.h"

int	initialize_rays_struct(t_player *player)
{
	int	i;

	i = 0;
	player->rays = malloc(sizeof(t_ray) * WIDTH);
	if (!player->rays)
		return (1);
	while (i < WIDTH)
	{
		player->rays[i].map_img = player->map_img;
		player->rays[i].h_xintersept = 0;
		if (alloc_d_rays(player, player->rays, i) == 0)
			return (free_old_rays(player->rays, i), 0);
		player->rays[i].h_yintersept = 0;
		player->rays[i].v_xintersept = 0;
		player->rays[i].v_yintersept = 0;
		player->rays[i].p_is_facing_down = 0;
		player->rays[i].p_is_facing_up = 0;
		player->rays[i].p_is_facing_right = 0;
		player->rays[i].p_is_facing_left = 0;
		player->rays[i].horizontal_wall = 0;
		player->rays[i].vertical_wall = 0;
		i++;
	}
	return (0);
}

int	initialize_sprites_struct(t_player *player, mlx_texture_t **textures)
{
	int	j;

	j = 0;
	player->total_sprites = calculate_number_sprites(player);
	player->sprite = malloc(sizeof(t_sprite) * player->total_sprites);
	if (!player->sprite)
		return (perror("malloc failed\n"), 1);
	while (j < player->total_sprites)
	{
		player->sprite[j].psprite_width = 0;
		player->sprite[j].psprite_height = 0;
		player->sprite[j].sprite_xstart = 0;
		player->sprite[j].sprite_xend = 0;
		player->sprite[j].collected = 0;
		player->sprite[j].x = -1;
		player->sprite[j].y = -1;
		player->sprite[j].texture = textures[0];
		player->sprite[j].visible = 0;
		player->sprite[j].an_textures = textures;
		j++;
	}
	return (0);
}

int	initialize_door_sprites(t_player *player,
		mlx_texture_t **textures)
{
	t_sprite	*sprite;
	int			j;

	j = 0;
	sprite = malloc(sizeof(t_sprite) * player->doors_count);
	if (!sprite)
		return (1);
	while (j < player->doors_count)
	{
		sprite[j].collected = 0;
		sprite[j].open_door = 0;
		sprite[j].start_a = 0;
		sprite[j].x = 0;
		sprite[j].y = 0;
		sprite[j].texture = textures[0];
		sprite[j].visible = 0;
		sprite[j].an_textures = textures;
		j++;
	}
	player->door_sprite = sprite;
	return (0);
}
