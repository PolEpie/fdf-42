/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:40:31 by pepie             #+#    #+#             */
/*   Updated: 2024/05/22 13:07:39 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	calculate_altitule(double in, t_data *win)
{
	return (in * win->amplitude);
}

void	draw_rect(t_rect rect, t_data *data)
{
	unsigned short int	i;
	unsigned short int	j;

	i = 0;
	while (i < rect.size_h && i + rect.y < data->height)
	{
		j = 0;
		while (j < rect.size_w && j + rect.x < data->width)
		{
			ft_mlx_pixel_put(data, j + rect.x, i + rect.y, rect.color);
			j++;
		}
		i++;
	}
}

void	process_line(t_draw_squares_args *args, t_data *win, t_list *lst_row)
{
	args->j = 0;
	args->is_border_left = true;
	while (args->j < win->points->w)
	{
		args->lst_content = args->lst->content;
		args->color = (args->lst_content[args->j])->color;
		if (args->j > 0)
			args->h_case_left = calculate_altitule(
					args->lst_content[args->j - 1]->y, win);
		else
			args->h_case_left = calculate_altitule(
					args->lst_content[args->j]->y, win);
		args->h_case_top = calculate_altitule(
				((t_map **)lst_row->content)[args->j]->y, win);
		draw_square(&(t_draw_square_args_norm){win, args->j, args->i,
			calculate_altitule(args->lst_content[args->j]->y, win)}, args);
		args->j++;
		args->is_border_left = false;
	}
	args->lst = args->lst->next;
	args->is_border_top = false;
}

int	draw_squares(t_data *win)
{
	t_draw_squares_args	*args;
	t_list				*lst_last_row;

	if (!win || !win->win)
		return (1);
	args = malloc(sizeof(t_draw_squares_args));
	if (!args)
		return (1);
	args->i = 0;
	args->j = 0;
	args->h_case_left = 0;
	args->h_case_top = 0;
	args->lst = *(win->points->row);
	args->is_border_top = true;
	lst_last_row = *(win->points->row);
	while (args->lst)
	{
		process_line(args, win, lst_last_row);
		if (args->i > 0)
			lst_last_row = lst_last_row->next;
		args->i++;
	}
	free(args);
	return (0);
}
