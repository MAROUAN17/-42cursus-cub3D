#include "./cub3d_header.h"

t_point	finding_wall_horizontal(t_player *player, t_ray *ray, double xstep, double ystep)
{
	t_point wall;
	double xcheck = 0;
	double ycheck = 0;

	while (ray->h_xintersept >= 0 && ray->h_yintersept >= 0
		&& ray->h_xintersept <= WIDTH
		&& ray->h_yintersept <= HEIGHT)
	{
		xcheck = ray->h_xintersept;
		if (ray->p_isFacingUp)
			ycheck = ray->h_yintersept - 1;
		else
			ycheck = ray->h_yintersept;
		// printf("y -> %d | x -> %d\n", (int)(ycheck / TILE_PX), (int)(xcheck / TILE_PX));
		if ((int)(ycheck / TILE_PX) < player->map_height
			&& (int)(ycheck / TILE_PX) >= 0
			&& (int)(xcheck / TILE_PX) < player->map_width
			&& (int)(xcheck / TILE_PX) >= 0
			&& player->map[(int)(ycheck / TILE_PX)][(int)(xcheck / TILE_PX)] == '1')
		{
			wall.x = ray->h_xintersept;
			wall.y = ray->h_yintersept;
			return (wall);
		}
		ray->h_xintersept += xstep;
		ray->h_yintersept += ystep;
	}
	wall.x = ray->h_xintersept;
	wall.y = ray->h_yintersept;
	return (wall);
}

t_point	finding_wall_vertical(t_player *player, t_ray *ray, double xstep, double ystep)
{
	t_point wall;
	double xcheck = 0;
	double ycheck = 0;

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
			wall.x = ray->v_xintersept;
			wall.y = ray->v_yintersept;
			return (wall);
		}
		ray->v_xintersept += xstep;
		ray->v_yintersept += ystep;
	}
	wall.x = ray->v_xintersept;
	wall.y = ray->v_yintersept;
	return (wall);
}
