/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_wall2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:47:05 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_bonus.h"

void	count_xcheck_ycheck(t_ray *ray, float *p_xcheck, float *p_ycheck)
{
	*p_ycheck = 0;
	*p_xcheck = ray->h_xintersept;
	if (ray->p_is_facing_up)
		*p_ycheck = ray->h_yintersept - 1;
	else
		*p_ycheck = ray->h_yintersept;
}

t_point	h_set_interse_wall(t_ray *ray, int *index)
{
	t_point	wall;

	wall.x = ray->h_xintersept;
	wall.y = ray->h_yintersept;
	*index = 0;
	return (wall);
}

void	h_set_interse_door(t_ray *ray, int *index)
{
	ray->d_h_xintersept[*index] = ray->h_xintersept;
	ray->d_h_yintersept[*index] = ray->h_yintersept;
	(*index)++;
}

t_point	v_set_interse_wall(t_ray *ray, int *index)
{
	t_point	wall;

	wall.x = ray->v_xintersept;
	wall.y = ray->v_yintersept;
	*index = 0;
	return (wall);
}

void	v_set_interse_door(t_ray *ray, int *index)
{
	ray->d_v_xintersept[*index] = ray->v_xintersept;
	ray->d_v_yintersept[*index] = ray->v_yintersept;
	(*index)++;
}
