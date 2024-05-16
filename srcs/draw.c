/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 00:38:30 by pepie             #+#    #+#             */
/*   Updated: 2024/05/16 13:43:17 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_data *win, t_vector *v1, t_vector *v2, long color)
{
	t_vector	*pos1;
	t_vector	*pos2;

	if (color == 0)
		color = 0xFFFFFF;
	//ft_printf("v1: %lu\n", color);
	pos1 = handle_point(win, v1);
	if (!pos1)
		return ;
	pos2 = handle_point(win, v2);
	if (!pos2)
		return ;
    //printf("pos1: x: %f->%f | y: %f->%f\n", pos1->x, pos2->x, pos1->y, pos2->y);
	draw_line_ppos(win, &(t_line){(int)pos1->x, (int)pos1->y, (int)pos2->x,
		(int)pos2->y, color});
	//ft_printf("oh\n");
	free(pos1);
	free(pos2);
}

float	calculate_altitule(int in, t_data *win)
{
	return (in * win->amplitude);
}

typedef struct s_draw_square_args_norm {
	t_data	*win;
	int		x;
	int		y;
	int		z;
}	t_draw_square_args_norm;

typedef struct s_draw_squares_args {
	t_list	*lst;
	t_list	*lst_last_row;
	float	h_case_top;
	float	h_case_left;
	bool	is_border_left;
	bool	is_border_top;
	int		i;
	int		j;
	t_map	**lst_content;
	long	color;
}	t_draw_squares_args;

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
	//ft_printf("T\n");
	draw_line(argc->win, v1, v2, arg->color);
	v1 = vector_new(argc->x + 1, argc->y + 1, argc->z);
	v2 = vector_new(argc->x, argc->y + 1, arg->h_case_left);
	//ft_printf("E\n");
	draw_line(argc->win, v1, v2, arg->color);
	if (arg->is_border_left)
	{
		v1 = vector_new(argc->x, argc->y, arg->h_case_top);
		v2 = vector_new(argc->x, argc->y + 1, argc->z);
		//ft_printf("S\n");
		draw_line(argc->win, v1, v2, arg->color);
	}
	if (arg->is_border_top)
	{
		v1 = vector_new(argc->x, argc->y, arg->h_case_left);
		v2 = vector_new(argc->x + 1, argc->y, argc->z);
		//ft_printf("TE\n");
		draw_line(argc->win, v1, v2, arg->color);
	}
	//ft_printf("FRF\n");
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
		args->j = 0;
		args->is_border_left = true;
		while (args->j < win->points->w)
		{
			args->lst_content = args->lst->content;
			//ft_printf("TESE %d\n", args->j);
			args->color = (args->lst_content[args->j])->color;
			//ft_printf("TESE\n");
			if (args->j > 0)
				args->h_case_left = calculate_altitule(args->lst_content[args->j - 1]->y, win);
			else
				args->h_case_left = calculate_altitule(args->lst_content[args->j]->y, win);
			//ft_printf("%d\n", args->lst_content[args->j]->y);
			args->h_case_top = calculate_altitule(((t_map **)lst_last_row->content)[args->j]->y, win);
			draw_square(&(t_draw_square_args_norm){win, args->j, args->i,
				calculate_altitule(args->lst_content[args->j]->y, win)}, args);
			args->j++;
			args->is_border_left = false;
			//ft_printf("OH NON\n");
		}
		//ft_printf("---------------\n");
		if (args->i > 0)
			lst_last_row = lst_last_row->next;
		//ft_printf("FFFFF c'est ninho\n");
		args->i++;
		args->lst = args->lst->next;
		args->is_border_top = false;
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
	draw_rect((t_rect){0, 0, win->width, win->height, 0x000000}, win);
	draw_squares(win);
	//ft_printf("@@@@@@@@@@@@@@\n");
	return (0);
}
