/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 03:26:27 by pepie             #+#    #+#             */
/*   Updated: 2024/05/07 15:16:05 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_split(char **elem)
{
	int	i;

	if (!elem)
		return ;
	i = 0;
	while (elem[i])
	{
		free(elem[i]);
		i++;
	}
	free(elem);
}

t_map	*new_map(long color, int value)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->color = color;
	map->y = value;
	return (map);
}

int	parse_line(char *line, t_map **list)
{
	char	**splited;
	char	**splited_with_col;
	int		i;
	int		value;

	i = 0;
	if (!list)
		return (0);
	ft_printf("line: %s\n", line);
	splited = ft_split(line, ' ');
	if (!splited)
		return (0);
	while (splited[i])
	{
		splited_with_col = ft_split(splited[i], ',');
		if (!splited_with_col)
			return (0);
		value = ft_atoi(splited_with_col[0]);
		if (splited_with_col[1])
			list[i] = new_map(ft_atol_base(splited_with_col[1] + 2,
						"0123456789ABCDEF"), value);
		else
			list[i] = new_map(0, value);
		ft_printf("value: %d | %s (%s)\n", i, splited[i], splited_with_col[0]);
		i++;
		free_split(splited_with_col);
	}
	list[i] = NULL;
	return (free_split(splited), free(line), 1);
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
	free_split(splited);
	return (i);
}

int	parse_file(int fd, t_points *points)
{
	char		*line;
	int			i;
	int			*row;
	int			len;

	line = get_next_line(fd);
	i = 0;
	len = get_line_lenght(line);
	if (points->w != 0 && points->w != len)
		return (0);
	points->w = len;
	while (line != NULL)
	{
		row = malloc(sizeof(t_map *) * (points->w + 1));
		if (!row)
			return (0);
		ft_lstadd_back(points->row, ft_lstnew(row));
		if (!parse_line(line, ft_lstlast(*(points->row))->content))
			return (0);
		line = get_next_line(fd);
		ft_printf("T (%s)\n", line);
		i++;
	}
	points->h = i;
	return (1);
}
