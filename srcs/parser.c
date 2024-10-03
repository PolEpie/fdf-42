/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 03:26:27 by pepie             #+#    #+#             */
/*   Updated: 2024/10/03 13:34:13 by pepie            ###   ########.fr       */
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

static int	process_line(int i, char *line, t_map **list)
{
	char	**splited_w_col;
	int		value;

	splited_w_col = ft_split(line, ',');
	if (!splited_w_col)
		return (0);
	value = ft_atoi(splited_w_col[0]);
	if (splited_w_col[1])
		list[i] = new_map(ft_atol_base(splited_w_col[1] + 2,
					"0123456789ABCDEF"), value);
	else
		list[i] = new_map(0, value);
	ft_freesplit(splited_w_col);
	free(splited_w_col);
	return (1);
}

void	error_free(char **splited, char *line)
{
	ft_freesplit(splited);
	free(splited);
	free(line);
}

int	parse_line(char *line, t_map **list, int w)
{
	char	**splited;
	int		i;

	i = 0;
	if (!list)
		return (0);
	splited = ft_split(line, ' ');
	if (!splited)
		return (0);
	while (splited[i] && i < w)
	{
		if (!process_line(i, splited[i], list))
			return (error_free(splited, line), 0);
		i++;
	}
	list[i] = NULL;
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
		if ((points->w != -1 && points->w != len) || len == 0)
			return (free(line), 0);
		points->w = len;
		row = malloc(sizeof(t_map *) * (points->w + 1));
		if (!row)
			return (0);
		ft_lstadd_back(points->row, ft_lstnew(row));
		if (!parse_line(line, ft_lstlast(*(points->row))->content, len))
			return (0);
		i++;
	}
	points->h = i;
	points->scale = 10000 / ft_mathmax(points->w, points->h);
	return (1);
}
