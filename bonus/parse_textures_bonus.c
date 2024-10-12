/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:20:22 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/12 13:37:47 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_bonus.h"

int	get_file_type(char *line)
{
	int	len;

	len = ft_strlen(line);
	len--;
	while (line[len] == ' ' && len > 0)
	{
		line[len] = '\0';
		len--;
	}
	if (len < 4)
		return (0);
	if (ft_strncmp(line + len - 3, ".png", 5) == 0)
		return (1);
	else if (ft_strncmp(line + len - 5, ".xpm42", 7) == 0)
		return (2);
	return (0);
}

int	check_identifier(t_player *player, char *line)
{
	static int	f_flag;
	static int	c_flag;

	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_texture(&player->north_texture, &player->no_t, line));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_texture(&player->south_texture, &player->so_t, line));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_texture(&player->west_texture, &player->we_t, line));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_texture(&player->east_texture, &player->ea_t, line));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (set_color(&player->floor_color, line, &f_flag));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (set_color(&player->ceiling_color, line, &c_flag));
	else if (*line != '\0' && is_invalid_tex(player))
		return (print_err("Error\nMissing Textures!\n"), 0);
	else if (*line != '\0' && f_flag == 0)
		return (print_err("Error\nMissing Floor Color!\n"), 0);
	else if (*line != '\0' && c_flag == 0)
		return (print_err("Error\nMissing Ceilling Color!\n"), 0);
	else if (*line != '\0')
		return (2);
	return (1);
}

int	check_lines(t_player *player, int fd)
{
	char	*line;
	char	*tmp_ptr;
	int		identifier;
	int		count;

	count = 0;
	line = get_next_line(fd);
	if (!line)
		return (perror("Error\n"), close(fd), 0);
	while (line)
	{
		tmp_ptr = line;
		while (*tmp_ptr == ' ')
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
	close(fd);
	return (1);
}

int	get_textures(t_player *player, char *map_path)
{
	int	fd;
	int	count;

	player->north_texture = NULL;
	player->south_texture = NULL;
	player->east_texture = NULL;
	player->west_texture = NULL;
	player->floor_color = 0;
	player->ceiling_color = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nMap"), 0);
	count = check_lines(player, fd);
	if (count == -1)
		return (-1);
	if (is_invalid_tex(player))
		return (print_err("Error\nMissing Textures!\n"), -1);
	return (count);
}
