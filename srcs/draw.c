/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 00:38:30 by pepie             #+#    #+#             */
/*   Updated: 2024/05/16 14:35:44 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_data *win, t_vector *v1, t_vector *v2, long color)
{
	t_vector	*pos1;
	t_vector	*pos2;

	if (color == 0)
		color = 0xFFFFFF;
	pos1 = handle_point(win, v1);
	if (!pos1)
		return ;
	pos2 = handle_point(win, v2);
	if (!pos2)
		return ;
	draw_line_ppos(win, &(t_line){(int)pos1->x, (int)pos1->y, (int)pos2->x,
		(int)pos2->y, color});
	free(pos1);
	free(pos2);
}

void	draw_square(t_draw_square_args_norm *argc, t_draw_squares_args *arg)
{
	t_vector	*v1;
	t_vector	*v2;

	if (!(argc->win) || !(argc->win->points) || !(argc->win->points->w))
		return ;
	argc->x -= (argc->win->points->w / 2);
	argc->y -= (argc->win->points->h / 2);
	v1 = vector_new(argc->x + 1, argc->y, arg->h_case_top);
	v2 = vector_new(argc->x + 1, argc->y + 1, argc->z);
	draw_line(argc->win, v1, v2, arg->color);
	v1 = vector_new(argc->x + 1, argc->y + 1, argc->z);
	v2 = vector_new(argc->x, argc->y + 1, arg->h_case_left);
	draw_line(argc->win, v1, v2, arg->color);
	if (arg->is_border_left)
	{
		v1 = vector_new(argc->x, argc->y, arg->h_case_top);
		v2 = vector_new(argc->x, argc->y + 1, argc->z);
		draw_line(argc->win, v1, v2, arg->color);
	}
	if (arg->is_border_top)
	{
		v1 = vector_new(argc->x, argc->y, arg->h_case_left);
		v2 = vector_new(argc->x + 1, argc->y, argc->z);
		draw_line(argc->win, v1, v2, arg->color);
	}
}

int	draw_points(t_data *win)
{
	if (win == NULL)
		return (1);
	if (win->img == NULL || win->width == -1)
		return (1);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	draw_rect((t_rect){0, 0, win->width, win->height, 0x000000}, win);
	draw_squares(win);
	return (0);
}
