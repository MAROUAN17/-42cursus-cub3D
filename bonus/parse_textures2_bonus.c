/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:40:14 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_bonus.h"

int	which_type(mlx_texture_t **texture, xpm_t **xpm,
			char *line, int type)
{
	if (type == 1)
	{
		*xpm = NULL;
		*texture = mlx_load_png(line);
		*texture = resize_texture(*texture, TILE_PX, TILE_PX);
		if (!*texture)
			return (print_err("Error\nInvalid Textures!\n"), 0);
	}
	else if (type == 2)
	{
		*xpm = mlx_load_xpm42(line);
		if (!*xpm)
			return (print_err("Error\nInvalid Textures!\n"), 0);
		*texture = resize_texture(&(*xpm)->texture, TILE_PX, TILE_PX);
		if (!*texture)
			return (0);
	}
	else
		return (print_err("Error\nInvalid Textures!\n"), 0);
	return (1);
}

int	set_texture(mlx_texture_t **texture, xpm_t **xpm, char *line)
{
	int	i;
	int	type;

	i = 0;
	line += 3;
	while (*line == ' ')
		line++;
	type = get_file_type(line);
	if (*texture == NULL)
	{
		if (!which_type(texture, xpm, line, type))
			return (0);
		return (1);
	}
	else
		return (print_err("Error\nDuplicated Textures!\n"), 0);
}
