#include "cub3d_header.h"

float calculate_smallest_distance(t_player *player, t_ray *ray, t_point *wall1, t_point *wall2)
{
	float distance1 = 0;
	float distance2 = 0;

	distance1 = sqrt(pow(wall1->x - player->player_x, 2) + pow(wall1->y - player->player_y, 2));
	distance2 = sqrt(pow(wall2->x - player->player_x, 2) + pow(wall2->y - player->player_y, 2));
	if (distance2 < distance1)
	{
		ray->x = wall2->x;
		ray->y = wall2->y;
		ray->horizontal_wall = 0;
		ray->vertical_wall = 1;
		return (distance2);
	}
	else
	{
		ray->x = wall1->x;
		ray->y = wall1->y;
		ray->horizontal_wall = 1;
		ray->vertical_wall = 0;
		return (distance1);
	}
}
