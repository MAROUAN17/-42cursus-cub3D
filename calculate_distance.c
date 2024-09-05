#include "./cub3d_header.h"

double calculate_smallest_distance(t_player *player, t_ray *ray, t_point *wall1, t_point *wall2)
{
	double distance1 = 0;
	double distance2 = 0;

	distance1 = sqrt(pow(wall1->x - player->player_x, 2) + pow(wall1->y - player->player_y, 2));
	distance2 = sqrt(pow(wall2->x - player->player_x, 2) + pow(wall2->y - player->player_y, 2));
	if (distance1 > distance2)
	{
		ray->x = wall2->x;
		ray->y = wall2->y;
		return (distance2);
	}
	else
	{
		ray->x = wall1->x;
		ray->y = wall1->y;
		return (distance1);
	}
}
