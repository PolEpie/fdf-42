/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 03:26:27 by pepie             #+#    #+#             */
/*   Updated: 2023/12/18 03:28:07 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_line(char *line, int *list)
{
	char	**splited;
	int		i;
	int		value;

	i = 0;
	splited = ft_split(line, ' ');
	if (!splited)
		return (0);
	while (splited[i])
	{
		value = ft_atoi(splited[i]);
		list[i] = value;
		i++;
	}
	list[i] = -1;
	return (1);
}

int	get_line_lenght(char *line)
{
	char		**splited;
	int			i;

	i = 0;
	splited = ft_split(line, ' ');
	if (!splited)
		return (-1);
	while (splited[i])
		i++;
	free(line);
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
		row = malloc(sizeof(int) *(points->w + 1));
		if (!row)
			return (0);
		ft_lstadd_back(points->row, ft_lstnew(row));
		if (!parse_line(line, ft_lstlast(*(points->row))->content))
			return (0);
		line = get_next_line(fd);
		i++;
	}
	points->h = i;
	return (1);
}
