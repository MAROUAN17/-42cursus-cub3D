/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:28:27 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/17 11:58:40 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

int	set_color(int *color, char *line)
{
	int i;

	i = 0;
	line += 2;
	while(*line == ' ')
		line++;
	if (*color == 0)
	{
		// line[ft_strlen(line) - 1] = '\0';
		// printf("|%s|\n", line);
		// texture = mlx_load_png(line);
		// if (!texture)
		// 	return (0);
		return (1);
	}
	else
		return (0);
}
int	set_texture(mlx_texture_t **texture, char *line)
{
	int i;

	i = 0;
	line += 3;
	while(*line == ' ')
		line++;
	if (*texture == NULL)
	{
		// line[ft_strlen(line) - 1] = '\0';
		// printf("|%s|\n", line);
		*texture = mlx_load_png(line);
		if (!*texture)
			return (0);
		return (1);
	}
	else
		return (0);
}
int	check_identifier(t_player *player, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_texture(&player->north_texture, line));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_texture(&player->south_texture, line));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_texture(&player->west_texture, line));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_texture(&player->east_texture, line));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (set_color(&player->floor_color, line));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (set_color(&player->ceiling_color, line));
	else if (*line != '\0')
		return (2);
	return (1);
}

int	get_textures(t_player *player, char *map_path)
{
	int fd;
	char *line;
	char *tmp_ptr;
	int	count;
	int identifier;

	count = 0;
	player->north_texture = NULL;
	player->south_texture = NULL;
	player->east_texture = NULL;
	player->west_texture = NULL;
	player->floor_color = 0;
	player->ceiling_color = 0;
	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	if (fd == -1 || !line)
		return (free(line), 0);
	while (line)
	{
		tmp_ptr = line;
		while(*tmp_ptr == ' ')
			tmp_ptr++;
		identifier = check_identifier(player, tmp_ptr);
		if (identifier == 0)
			return (free(line), close(fd), -1);
		else if (identifier == 2)
			return (free(line), close(fd), count);
		free(line);
		count++;
		line = get_next_line(fd);
	}
	return (1);
}

void	count_height(char *map_path, int *map_height, int *map_width)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	if (fd == -1 || !line) 
	{
		free(line);
		return ;
	}
	while (line)
	{
		*map_width = ft_strlen(line);
		free(line);
		(*map_height)++;
		line = get_next_line(fd);
	}
	close(fd);
}

int	skip_lines(int n, int fd)
{
	int i;
	char *line;

	i = 0;
	while (i < n)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		free(line);
		i++;	
	}
	return (1);
}

char	**store_2d_array(t_player *player, char *map_path, int *map_height, int *map_width)
{
	int		fd;
	char	*line;
	char	**d_map;
	int		i = 0;
	int		skip_n;
	// int j = 0;

	skip_n = get_textures(player, map_path);
	fd = open(map_path, O_RDONLY);
	skip_lines(skip_n, fd);
	line = get_next_line(fd);
	if (fd == -1 || !line)
		return (free(line), NULL);
	while (line)
	{
		*map_width = ft_strlen(line);
		free(line);
		(*map_height)++;
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	skip_lines(skip_n, fd);
	d_map = malloc(sizeof(char *) * (*map_height + 1));
	if (!d_map)
		return (NULL);
	while (i < *map_height)
	{
		d_map[i] = get_next_line(fd);
		if (!d_map[i])
			return (free_memory(d_map, i), NULL);
		free(line);
		i++;
	}
	d_map[i] = NULL;
	close(fd);
	return (d_map);
}
