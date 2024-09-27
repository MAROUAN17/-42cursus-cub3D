/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:04 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/27 14:05:52 by oait-laa         ###   ########.fr       */
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

// int main(int ac, char **av)
// {
// 	mlx_t		*mlx;
// 	int			map_width;
// 	int			map_height;
// 	t_player	player;
// 	t_ray		rays[WIDTH];
// 	t_sprite	sprite[NUM_SPRITE];
// 	mlx_texture_t	*textures[5];
// 	// mlx_texture_t	*door_textures[4];

// 	(void)ac;
// 	map_width = 0;
// 	map_height = 0;
// 	player.player_x = -1;
// 	player.player_y = -1;
// 	player.map = store_2d_array(&player, av[1], &map_height, &map_width);
// 	if (player.map == NULL)
// 		return (1);
// 	printf("here\n");
// 	int i = 0;
// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false)))
// 	{
// 		free_2d_arr(player.map);
// 		perror(strerror(mlx_errno));
// 		return (EXIT_FAILURE);
// 	}

// 	mlx_image_t *map_img = mlx_new_image(mlx, WIDTH, HEIGHT);
// 	player.map_img = map_img;
// 	while (i < WIDTH)
// 	{
// 		rays[i].map_img = map_img;
// 		rays[i].h_xintersept = 0;
// 		rays[i].h_yintersept = 0;
// 		rays[i].v_xintersept = 0;
// 		rays[i].v_yintersept = 0;
// 		rays[i].p_isFacingDown = 0;
// 		rays[i].p_isFacingUp = 0;
// 		rays[i].p_isFacingRight = 0;
// 		rays[i].p_isFacingLeft = 0;
// 		rays[i].horizontal_wall = 0;
// 		rays[i].vertical_wall = 0;
// 		i++;
// 	}
// 	// player.playerAngle = M_PI / 2;
// 	player.moveSpeed = 6.0;
// 	player.rotationSpeed = degrees2rad(2.5);
// 	// get_textures(&player, av[1]);
// 	player.map_height = map_height;
// 	player.map_width = map_width;
// 	player.rays = rays;
// 	player.mlx = mlx;
// 	player.door_textures[0] = resize_texture(mlx_load_png("./textures/Door1.png"), TILE_PX, TILE_PX);
// 	player.open_door = 0;
// 	textures[0] = mlx_load_png("./textures/MonedaD1.png");
// 	textures[1] = mlx_load_png("./textures/MonedaD2.png");
// 	textures[2] = mlx_load_png("./textures/MonedaD3.png");
// 	textures[3] = mlx_load_png("./textures/MonedaD4.png");
// 	textures[4] = mlx_load_png("./textures/MonedaD5.png");
// 	initialize_player_struct(&player, av[1], &map_width, &map_height);
// 	initialize_rays_struct(&player, rays);
// 	initialize_sprites_struct(&player, sprite, textures);
// 	mlx_image_to_window(player.mlx, player.map_img, 0, 0);
// 	mlx_key_hook(player.mlx, &move_player, &player);
// 	mlx_loop_hook(player.mlx, &render, &player);
// 	mlx_loop(player.mlx);
// 	mlx_terminate(player.mlx);
// 	free_2d_arr(player.map);
// 	return (EXIT_SUCCESS);
// }

int initialize_door_sprites(t_player *player, mlx_texture_t **textures)
{
    int j;
	t_sprite *sprite;

    j = 0;
	sprite = malloc(sizeof(t_sprite) * player->doors_count);
	if (!sprite)
		return (0);
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
	return (1);
}

int main(int ac, char **av)
{
    int            map_width;
    int            map_height;
    t_player    player;
    t_ray        rays[WIDTH];
    t_sprite    sprite[NUM_SPRITE];
    mlx_texture_t *textures[5];
	// t_sprite 		d_sprite[2];
	mlx_texture_t *d_textures[4];

    (void)ac;
    map_width = 0;
    map_height = 0;
	// player.door_textures[0] = resize_texture(mlx_load_png("./textures/Door1.png"), TILE_PX, TILE_PX);
	// player.door_textures[1] = resize_texture(mlx_load_png("./textures/Door2.png"), TILE_PX, TILE_PX);
	// player.door_textures[2] = resize_texture(mlx_load_png("./textures/Door3.png"), TILE_PX, TILE_PX);
	// player.door_textures[3] = resize_texture(mlx_load_png("./textures/Door4.png"), TILE_PX, TILE_PX);
	// player.curr_door_tex = player.door_textures[0];
	d_textures[0] = resize_texture(mlx_load_png("./textures/Door1.png"), TILE_PX, TILE_PX);
	d_textures[1] = resize_texture(mlx_load_png("./textures/Door2.png"), TILE_PX, TILE_PX);
	d_textures[2] = resize_texture(mlx_load_png("./textures/Door3.png"), TILE_PX, TILE_PX);
	d_textures[3] = resize_texture(mlx_load_png("./textures/Door4.png"), TILE_PX, TILE_PX);
    textures[0] = mlx_load_png("./textures/MonedaD1.png");
    textures[1] = mlx_load_png("./textures/MonedaD2.png");
    textures[2] = mlx_load_png("./textures/MonedaD3.png");
    textures[3] = mlx_load_png("./textures/MonedaD4.png");
    textures[4] = mlx_load_png("./textures/MonedaD5.png");
    initialize_player_struct(&player, av[1], &map_width, &map_height);
    initialize_rays_struct(&player, rays);
    initialize_sprites_struct(&player, sprite, textures);
	if (!initialize_door_sprites(&player, d_textures))
		return (1); // free map and textures here
    mlx_image_to_window(player.mlx, player.map_img, 0, 0);
    mlx_key_hook(player.mlx, &move_player, &player);
    mlx_loop_hook(player.mlx, &render, &player);
    mlx_loop(player.mlx);
    mlx_terminate(player.mlx);
    free_2d_arr(player.map);
    return (EXIT_SUCCESS);
}
