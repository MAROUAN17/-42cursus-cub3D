/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:09:30 by oait-laa          #+#    #+#             */
/*   Updated: 2024/10/04 15:53:44 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header.h"

int count_comma(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	return (count);
}
int count_2d_len(char **sep_str)
{
	int i;

	i = 0;
	while (sep_str[i])
		i++;
	return (i);
}

int num_length(char *str)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	if (*str == '0')
		count++;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		count++;
		i++;
	}
	return (count);
}

int translate_color(char *str, int *num)
{
	int tmp_num;
	int	length;
	
	tmp_num = ft_atoi(str);
	length = num_length(str);
	if (length <= 3 && length > 0
		&& (tmp_num <= 255 && tmp_num >= 0))
		*num = tmp_num;
	else
		return (0);
	return (1);
}

int	translate_rgb(char **sep_str, int *color)
{	
	int	r;
	int	g;
	int	b;

	if (!translate_color(sep_str[0], &r))
		return (0);
	if (!translate_color(sep_str[1], &g))
		return (0);
	if (!translate_color(sep_str[2], &b))
		return (0);
	*color = get_rgba(r, g, b, 255);
	return (1);
}
