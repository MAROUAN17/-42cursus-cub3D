/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:10:01 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_bonus.h"

void	destroy_t_door(mlx_texture_t **d_textures)
{
	mlx_delete_texture(d_textures[0]);
	mlx_delete_texture(d_textures[1]);
	mlx_delete_texture(d_textures[2]);
	mlx_delete_texture(d_textures[3]);
}

void	destroy_t_coins(mlx_texture_t **c_textures)
{
	mlx_delete_texture(c_textures[0]);
	mlx_delete_texture(c_textures[1]);
	mlx_delete_texture(c_textures[2]);
	mlx_delete_texture(c_textures[3]);
	mlx_delete_texture(c_textures[4]);
}
