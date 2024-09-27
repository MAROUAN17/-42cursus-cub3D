/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:17:46 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/26 13:06:39 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

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
		if (line[i] == ' ' && comp_line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	skip_sp(char *line, int *i)
{
	int j;

	j = *i;
	while (line[j] == ' ')
		j++;
	// printf("c -> %c\n", line[*i]);
	if (line[j] == '\0' && *i == 0)
	{
		*i = j;
		return (0);
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
	if (line[i] != '1' && line[i] != ' '
		&& line[i] != '0' && line[i] != 'N' && line[i] != 'S'
		&& line[i] != 'W' && line[i] != 'E')
		return (0);
	if (line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'W' || line[i] == 'E')
		(*p_counter)++;
	if (line[i] == 'N')
		player->playerAngle = 3 * M_PI / 2;
	else if (line[i] == 'S')
		player->playerAngle = (M_PI / 2);
	else if (line[i] == 'W')
		player->playerAngle = 2 * (M_PI / 2);
	else if (line[i] == 'E')
		player->playerAngle = 0;
	return (1);
}

int	check_valid_line(char *line, char *top_line, int *p_counter, t_player *player)
{
	int	i;

	i = 0;
	if (skip_sp(line, &i) == 0)
		return (0);
	while (line[i])
	{
		if (!check_line_chars(line, p_counter, i, player))
			return (0);
		if (line[i] == ' ' && top_line[i] != '1' && top_line[i] != ' ')
			return (0);
		if ((line[i] == ' ' && line[i - 1] != '1' && line[i - 1] != ' ') || (line[i] == ' ' && skip_sp(line, &i) == 0))
			return (0);
		i++;
	}
	i--;
	while (line[i] == ' ' && i > 0)
		i--;
	if (line[i] != '1')
		return (0);
	return (1);
}

int	check_map_valid(char **map, t_player *player)
{
	int	i;
	int	p_counter;

	i = 0;
	p_counter = 0;
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
