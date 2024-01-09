/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 00:38:30 by pepie             #+#    #+#             */
/*   Updated: 2024/01/09 02:07:25 by pepie            ###   ########.fr       */
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
	free(pos1);
	free(pos2);
}

typedef struct s_draw_square_args_norm {
	t_data	*win;
	int		x;
	int		y;
	int		z;
}	t_draw_square_args_norm;

typedef struct s_draw_squares_args {
	t_list	*lst;
	int		last_x;
	int		last_y;
	int		i;
	int		j;
	int		*lst_content;
}	t_draw_squares_args;

void	draw_square(t_draw_square_args_norm *argc, t_draw_squares_args *arg)
{
	t_vector	*v1;
	t_vector	*v2;

	if (!(argc->win) || !(argc->win->points) || !(argc->win->points->w))
		return ;
	argc->x -= (argc->win->points->w / 2);
	argc->y -= (argc->win->points->h / 2);
	v1 = vector_new(argc->x, argc->y, argc->z);
	v2 = vector_new(argc->x + 1, argc->y, argc->z);
	draw_line(argc->win, v1, v2);
	v1 = vector_new(argc->x + 1, argc->y + 1, argc->z);
	v2 = vector_new(argc->x + 1, argc->y, argc->z);
	draw_line(argc->win, v1, v2);
	v1 = vector_new(argc->x + 1, argc->y + 1, argc->z);
	v2 = vector_new(argc->x, argc->y + 1, argc->z);
	draw_line(argc->win, v1, v2);
	v1 = vector_new(argc->x, argc->y, argc->z);
	v2 = vector_new(argc->x, argc->y + 1, argc->z);
	draw_line(argc->win, v1, v2);
	v1 = vector_new(argc->x, argc->y, argc->z);
	v2 = vector_new(argc->x, argc->y, arg->last_x);
	draw_line(argc->win, v1, v2);
	arg->last_x = argc->z;
	arg->last_y = argc->z;
}

int	draw_squares(t_data *win)
{
	t_draw_squares_args	*args;

	if (!win || !win->win)
		return (1);
	args = malloc(sizeof(t_draw_squares_args));
	if (!args)
		return (1);
	args->i = 0;
	args->j = 0;
	args->last_x = 0;
	args->lst = *(win->points->row);
	while (args->lst)
	{
		args->j = 0;
		while (args->j < win->points->w)
		{
			args->lst_content = args->lst->content;
			draw_square(&(t_draw_square_args_norm){win, args->j, args->i,
				args->lst_content[args->j]}, args);
			args->j++;
		}
		args->i++;
		args->lst = args->lst->next;
	}
	free(args);
	return (0);
}

int	draw_points(t_data *win)
{
	if (win == NULL)
		return (1);
	if (win->img == NULL || win->width == -1)
		return (1);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	draw_rect(
		(t_rect){0, 0, win->width, win->height, rgb_to_int(0, 0, 0)}, win);
	draw_squares(win);
	return (0);
}
