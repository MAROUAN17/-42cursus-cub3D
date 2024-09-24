#include "cub3d_header.h"

t_point	finding_wall_horizontal(t_player *player, t_ray *ray, float xstep, float ystep)
{
	t_point wall;
	float xcheck = 0;
	float ycheck = 0;

	while (ray->h_xintersept > 0 && ray->h_yintersept > 0
		&& ray->h_xintersept < WIDTH
		&& ray->h_yintersept < HEIGHT)
	{
		xcheck = ray->h_xintersept;
		if (ray->p_isFacingUp)
			ycheck = ray->h_yintersept - 1;
		else
			ycheck = ray->h_yintersept;
		// mlx_put_pixel(player->map_img, xcheck, ycheck, 0x00FF00FF);
		// if (ycheck < 0)
		// 	printf("negatif %f\n", ycheck);
		if ((int)(ycheck / TILE_PX) < player->map_height
			&& (int)(ycheck / TILE_PX) >= 0
			&& (int)(xcheck / TILE_PX) < player->map_width
			&& (int)(xcheck / TILE_PX) >= 0
			&& player->map[(int)(ycheck / TILE_PX)][(int)(xcheck / TILE_PX)] == '1')
		{
			// printf("y -> %d | x -> %d | line -> %s\n", (int)(ycheck / TILE_PX), (int)(xcheck / TILE_PX),  player->map[(int)(ycheck / TILE_PX)]);
			wall.x = ray->h_xintersept;
			wall.y = ray->h_yintersept;
			return (wall);
		}
		// printf("condition -> %d\n", player->map[(int)(ycheck / TILE_PX)][(int)(xcheck / TILE_PX)] == '1');
		ray->h_xintersept += xstep;
		ray->h_yintersept += ystep;
	}
	// printf("H = condit -> %d | checkx -> %d | checky -> %d\n", player->map[(int)(ycheck / TILE_PX)][(int)(xcheck / TILE_PX)] == '1',  (int)(xcheck / TILE_PX), (int)(ycheck / TILE_PX));
	// printf("H = x -> %f | y -> %f | line -> %s | char -> %c\n", ray->h_xintersept, ray->h_yintersept,  player->map[(int)(ycheck / TILE_PX)], player->map[(int)(ycheck / TILE_PX)][(int)(xcheck / TILE_PX)]);
	wall.x = ray->h_xintersept;
	wall.y = ray->h_yintersept;
	// wall.x = INT_MAX;
	// wall.y = INT_MAX;
	return (wall);
}

t_point	finding_wall_vertical(t_player *player, t_ray *ray, float xstep, float ystep)
{
	t_point wall;
	float xcheck = 0;
	float ycheck = 0;
	int count = 0;

	while (ray->v_xintersept >= 0 && ray->v_yintersept >= 0
		&& ray->v_yintersept <= HEIGHT
		&& ray->v_xintersept <= WIDTH)
	{
		if (ray->p_isFacingLeft)
			xcheck = ray->v_xintersept - 1;
		else
			xcheck = ray->v_xintersept;
		ycheck = ray->v_yintersept;
		if ((int)(ycheck / TILE_PX) < player->map_height
			&& (int)(ycheck / TILE_PX) >= 0
			&& (int)(xcheck / TILE_PX) < player->map_width
			&& (int)(xcheck / TILE_PX) >= 0
			&& player->map[(int)(ycheck / TILE_PX)][(int)(xcheck / TILE_PX)] == '1')
		{
			// printf("y -> %d | x -> %d | line -> %s\n", (int)(ycheck / TILE_PX), (int)(xcheck / TILE_PX),  player->map[(int)(ycheck / TILE_PX)]);
			wall.x = ray->v_xintersept;
			wall.y = ray->v_yintersept;
			// printf("count -> %d\n", count);
			return (wall);
		}
		ray->v_xintersept += xstep;
		ray->v_yintersept += ystep;
		count++;
	}
	// printf("V = x -> %f | y -> %f | line -> %s | char -> %c\n", ray->h_xintersept, ray->h_yintersept,  player->map[(int)(ycheck / TILE_PX)], player->map[(int)(ycheck / TILE_PX)][(int)(xcheck / TILE_PX)]);
	wall.x = ray->v_xintersept;
	wall.y = ray->v_yintersept;
	// wall.x = INT_MAX;
	// wall.y = INT_MAX;
	return (wall);
}
