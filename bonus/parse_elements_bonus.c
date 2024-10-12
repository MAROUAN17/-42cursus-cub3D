/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:17:46 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:59 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_bonus.h"

int	check_top_bot_borders(char *line, char *comp_line)
{
	int	i;

	i = 0;
	if (!line || !comp_line)
		return (0);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		if (line[i] == ' ' && (comp_line[i] != ' ' && comp_line[i] != '1'))
			return (0);
		i++;
	}
	return (1);
}

int	skip_sp(char *line, int *i)
{
	int	j;

	j = *i;
	while (line[j] == ' ')
		j++;
	if (line[j] == '\0' && *i == 0)
	{
		*i = j;
		return (1);
	}
	else if (line[j] == '\0')
		return (1);
	*i = j;
	if (line[j] != '1')
		return (0);
	return (1);
}

int	check_line_chars(char *line, int *p_counter, int i, t_player *player)
{
	if (line[i] == 'D')
		player->doors_count++;
	if (line[i] != 'I' && line[i] != '1' && line[i] != ' '
		&& line[i] != '0' && line[i] != 'N' && line[i] != 'S'
		&& line[i] != 'W' && line[i] != 'E' && line[i] != 'D')
		return (0);
	if (line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'W' || line[i] == 'E')
		(*p_counter)++;
	if (line[i] == 'N')
		player->player_angle = 3 * M_PI / 2;
	else if (line[i] == 'S')
		player->player_angle = (M_PI / 2);
	else if (line[i] == 'W')
		player->player_angle = M_PI;
	else if (line[i] == 'E')
		player->player_angle = 0;
	return (1);
}

int	check_valid_line(char *line, char *top_line,
		int *p_counter, t_player *player)
{
	int	i;

	i = 0;
	if (compare_to_upper_line(line, top_line))
		return (0);
	if (skip_sp(line, &i) == 0)
		return (0);
	while (line[i])
	{
		if (!check_line_chars(line, p_counter, i, player))
			return (0);
		if ((line[i] == ' ' && line[i - 1] != '1' && line[i - 1] != ' ')
			|| (line[i] == ' ' && skip_sp(line, &i) == 0))
			return (0);
		i++;
	}
	i--;
	while (line[i] == ' ' && i > 0)
		i--;
	if (line[i] != '1' && line[i] != ' ')
		return (0);
	return (1);
}

int	check_map_valid(char **map, t_player *player)
{
	int	i;
	int	p_counter;

	i = 0;
	p_counter = 0;
	player->doors_count = 0;
	if (check_top_bot_borders(map[0], map[1]) == 0)
		return (print_err("Error\nInvalid Map!\n"), 0);
	i++;
	while (map[i])
	{
		if (check_valid_line(map[i], map[i - 1], &p_counter, player) == 0)
			return (print_err("Error\nInvalid Map!\n"), 0);
		i++;
	}
	if (check_top_bot_borders(map[i - 1], map[i - 2]) == 0)
		return (print_err("Error\nInvalid Map!\n"), 0);
	if (p_counter > 1)
		return (print_err("Error\nMultiple PLayers!\n"), 0);
	else if (p_counter == 0)
		return (print_err("Error\nNo PLayer?!\n"), 0);
	return (1);
}
