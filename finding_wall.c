#include "./cub3d_header.h"

t_point	finding_wall_horizontal(t_player *player, t_ray *ray, double xstep, double ystep)
{
	t_point wall;
	double wallHitX = ray->h_xintersept;
	double wallHitY = ray->h_yintersept;

	while (wallHitX >= 0 && wallHitY >= 0
		&& wallHitY <= HEIGHT
		&& wallHitX <= WIDTH)
	{
		if ((int)((wallHitY - ray->p_isFacingUp) / TILE_PX) < player->map_height
			&& (int)((wallHitY - ray->p_isFacingUp) / TILE_PX) >= 0
			&& (int)(wallHitX / TILE_PX) < player->map_width
			&& (int)(wallHitX / TILE_PX) >= 0
			&& player->map[(int)((wallHitY - ray->p_isFacingUp) / TILE_PX)][(int)(wallHitX / TILE_PX)] == '1')
		{
			wall.x = wallHitX;
			wall.y = wallHitY;
			return (wall);
		}
		wallHitX += xstep;
		wallHitY += ystep;
	}
	wall.x = wallHitX;
	wall.y = wallHitY;
	return (wall);
}

t_point	finding_wall_vertical(t_player *player, t_ray *ray, double xstep, double ystep)
{
	t_point wall;
	double wallHitX = ray->v_xintersept;
	double wallHitY = ray->v_yintersept;

	while (wallHitX >= 0 && wallHitY >= 0
		&& wallHitY <= HEIGHT
		&& wallHitX <= WIDTH)
	{
		if ((int)(wallHitY / TILE_PX) < player->map_height
			&& (int)(wallHitY / TILE_PX) >= 0
			&& (int)((wallHitX - ray->p_isFacingLeft) / TILE_PX) < player->map_width
			&& (int)((wallHitX - ray->p_isFacingLeft) / TILE_PX) >= 0
			&& player->map[(int)(wallHitY / TILE_PX)][(int)((wallHitX - ray->p_isFacingLeft) / TILE_PX)] == '1')
		{
			wall.x = wallHitX;
			wall.y = wallHitY;
			return (wall);
		}
		wallHitX += xstep;
		wallHitY += ystep;
	}
	wall.x = wallHitX;
	wall.y = wallHitY;
	return (wall);
}
