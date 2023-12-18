/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 00:38:30 by pepie             #+#    #+#             */
/*   Updated: 2023/12/18 03:24:20 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_data *win, t_vector *v1, t_vector *v2)
{
	t_vector	*pos1;
	t_vector	*pos2;

	pos1 = handle_point(win, v1);
	if (!pos1)
		return ;
	pos2 = handle_point(win, v2);
	if (!pos2)
		return ;
	draw_line_ppos(win, &(t_line){pos1->x, pos1->y, pos2->x,
		pos2->y, rgb_to_int(0, 0, 255)});
}

void	draw_square(t_data *win, int x, int y, int z)
{
	t_vector	v1;
	t_vector	v2;

	v1.z = z;
	v2.z = z;
	x -= (win->points->w / 2);
	y -= (win->points->h / 2);
	v1.x = x;
	v1.y = y;
	v2.x = x + 1;
	v2.y = y;
	draw_line(win, &v1, &v2);
	v1.x = x + 1;
	v1.y = y + 1;
	draw_line(win, &v1, &v2);
	v2.x = x;
	v2.y = y + 1;
	draw_line(win, &v1, &v2);
	v1.x = x;
	v1.y = y;
	draw_line(win, &v1, &v2);
}

int	draw_points(t_data *win)
{
	t_list	*lst;
	int		*lst_content;
	int		i;
	int		j;

	i = 0;
	j = 0;
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	draw_rect(
		(t_rect){0, 0, win->width, win->height, rgb_to_int(0, 0, 0)}, win);
	lst = *(win->points->row);
	while (lst)
	{
		j = 0;
		while (j < win->points->w)
		{
			lst_content = lst->content;
			draw_square(win, j, i, lst_content[j]);
			j++;
		}
		i++;
		lst = lst->next;
	}
	return (0);
}
