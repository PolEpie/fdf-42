/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 03:26:27 by pepie             #+#    #+#             */
/*   Updated: 2024/10/16 14:33:50 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*new_map(long color, int value)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->color = color;
	map->y = value;
	return (map);
}

static int	process_line(int i, char *line, t_map **list, t_points *points)
{
	char	**split;
	int		value;

	split = ft_split(line, ',');
	if (!split)
		return (0);
	value = ft_atoi(split[0]);
	if (!is_good_input(split[0]))
		return (ft_freesplit(split), free(split), 0);
	if (split[1])
	{
		if (!is_good_input(split[1]))
			return (ft_freesplit(split), free(split), 0);
		list[i] = new_map(ft_atol_base(split[1] + 2,
					"0123456789abcdef"), value);
	}
	else
		list[i] = new_map(0, value);
	if (value < points->min_z)
		points->min_z = value;
	if (value > points->max_z)
		points->max_z = value;
	ft_freesplit(split);
	free(split);
	return (1);
}

int	parse_line(char *line, t_map **list, int w, t_points *points)
{
	char	**splited;
	int		i;

	i = 0;
	if (!list)
		return (0);
	ft_strtolower(line);
	splited = ft_split(line, ' ');
	if (!splited)
		return (0);
	list[i] = NULL;
	while (splited[i] && i < w)
	{
		if (!process_line(i, splited[i], list, points))
			return (error_free(splited, line), 0);
		i++;
		list[i] = NULL;
	}
	return (ft_freesplit(splited), free(splited), free(line), 1);
}

int	get_line_lenght(char *line)
{
	char		**splited;
	int			i;

	i = 0;
	if (!line)
		return (0);
	splited = ft_split(line, ' ');
	if (!splited)
		return (-1);
	while (splited[i])
		i++;
	ft_freesplit(splited);
	free(splited);
	return (i);
}

int	parse_file(int fd, t_points *points)
{
	char		*line;
	int			i;
	int			*row;
	int			len;

	i = 0;
	line = NULL;
	while (line != NULL || i == 0)
	{
		line = get_next_line(fd);
		len = get_line_lenght(line);
		if (line == NULL)
			return (points->w != -1);
		if (points->w != -1 && points->w != len)
			return (free(line), 0);
		points->w = len;
		row = malloc(sizeof(t_map *) * (points->w + 1));
		if (!row)
			return (0);
		ft_lstadd_back(points->row, ft_lstnew(row));
		if (!parse_line(line, ft_lstlast(*(points->row))->content, len, points))
			return (0);
		i++;
	}
	return (i);
}
