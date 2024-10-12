/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:49:57 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/12 11:44:58 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

void	set_new_pixels(mlx_texture_t *texture, mlx_texture_t *new_texture,
	double x_ratio, double y_ratio)
{
	int	x;
	int	y;
	int	index;
	int	new_index;

	y = 0;
	while (y < (int)new_texture->height)
	{
		x = 0;
		while (x < (int)new_texture->width)
		{
			index = ((int)(y * y_ratio)
					*(texture->width) + (int)(x * x_ratio)) * 4;
			new_index = (y * new_texture->width + x) * 4;
			new_texture->pixels[new_index] = texture->pixels[index];
			new_texture->pixels[new_index + 1] = texture->pixels[index + 1];
			new_texture->pixels[new_index + 2] = texture->pixels[index + 2];
			new_texture->pixels[new_index + 3] = texture->pixels[index + 3];
			x++;
		}
		y++;
	}
}

mlx_texture_t	*resize_texture(mlx_texture_t *texture,
	int new_width, int new_height)
{
	mlx_texture_t	*new_texture;
	double			x_ratio;
	double			y_ratio;

	if (!texture)
		return (NULL);
	new_texture = malloc(sizeof(mlx_texture_t));
	if (!new_texture)
		return (perror("Error\nTexture"), NULL);
	new_texture->width = new_width;
	new_texture->height = new_height;
	new_texture->pixels = malloc(new_width * new_height * 4);
	if (!new_texture->pixels)
		return (free(new_texture), perror("Error\nTexture"), NULL);
	x_ratio = (double)texture->width / new_width;
	y_ratio = (double)texture->height / new_height;
	set_new_pixels(texture, new_texture, x_ratio, y_ratio);
	mlx_delete_texture(texture);
	return (new_texture);
}

int	compare_to_upper_line(char *line, char *top_line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == ' ' && top_line[i] != '1' && top_line[i] != ' ')
			|| (line[i] == '0' && top_line[i] == ' ')
			|| ((line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
					|| line[i] == 'E')
				&& (top_line[i] == ' '))
			|| ((top_line[i] == 'N' || top_line[i] == 'S' || top_line[i] == 'W'
					|| top_line[i] == 'E')
				&& (line[i] == ' ')))
			return (1);
		i++;
	}
	return (0);
}

char	**fill_map(int fd, int *map_height, int *map_width)
{
	char	**d_map;
	int		i;

	i = 0;
	d_map = malloc(sizeof(char *) * (*map_height + 1));
	if (!d_map)
		return (perror("Error\nMap"), NULL);
	while (i < *map_height)
	{
		d_map[i] = get_next_line(fd);
		if (!d_map[i] || !fill_gaps(&d_map[i], *map_width))
			return (free_memory(d_map, i), perror("Error\nMap"), NULL);
		i++;
	}
	d_map[i] = NULL;
	return (d_map);
}

int	store_texture(mlx_texture_t **texture, xpm_t **xpm, char *line, int type)
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
