/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 00:12:47 by pepie             #+#    #+#             */
/*   Updated: 2024/10/16 14:31:00 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_data	*create_window(void)
{
	t_data	*win;
	void	*mlx;
	void	*win2;

	mlx = mlx_init();
	if (!mlx)
		return (NULL);
	win2 = mlx_new_window(mlx, WINDOW_W, WINDOW_H, "Fdf pepie");
	win = malloc(sizeof(t_data));
	if (!win)
		return (NULL);
	win->mlx = mlx;
	win->win = win2;
	win->img = mlx_new_image(win->mlx, WINDOW_W, WINDOW_H);
	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
			&win->line_length, &win->endian);
	win->width = WINDOW_W;
	win->height = WINDOW_H;
	win->mouse_pressed = false;
	win->is_ctrl_press = false;
	win->offset_x = 0;
	win->offset_y = 0;
	win->amplitude = 1;
	return (win);
}

int	run_window(t_data *win)
{
	win->cam_ang = vector_new(0.625000, -0.500000, 20);
	if (!win->cam_ang)
		return (free(win), 1);
	win->last_mouse = vector_new(0, 0, 0);
	if (!win->last_mouse)
		return (free(win), 1);
	mlx_hook(win->win, ON_MOUSEDOWN, (1L << 2), handle_mouse_press, win);
	mlx_hook(win->win, ON_MOUSEUP, (1L << 3), handle_mouse_release, win);
	mlx_hook(win->win, ON_MOUSEMOVE, (1L << 6), handle_mouse_move, win);
	mlx_hook(win->win, ON_KEYDOWN, (1L << 0), handle_key_up, win);
	mlx_key_hook(win->win, handle_key_down, win);
	mlx_loop_hook(win->mlx, draw_points, win);
	mlx_hook(win->win, DestroyNotify, 0, (int (*)())kill_process, win);
	mlx_loop(win->mlx);
	return (0);
}

int	handle_file_with_verif(int fd, t_points *points)
{
	int	h;

	points->row = malloc(sizeof(t_list *));
	if (!(points->row))
		return (0);
	*(points->row) = NULL;
	points->w = -1;
	points->min_z = 0;
	points->max_z = 0;
	h = parse_file(fd, points);
	if (h == 0)
		return (ft_lstclear(points->row, &free_row), free(points->row), 0);
	points->h = h;
	points->scale = 10000 / ft_mathmax(points->w, points->h);
	return (1);
}

int	main(int argv, char **argc)
{
	int			fd;
	t_points	*points;
	t_data		*data;

	if (argv != 2)
		return (write(2, "Wrong args: Exemple ./fdf test_maps/42.fdf\n", 43)
			, 1);
	fd = open(*(argc + 1), O_RDONLY);
	if (fd < 0)
		return (write(2, "Wrong file: Can't open\n", 23), 1);
	points = malloc(sizeof(t_points));
	if (!points)
		return (1);
	ft_printf("Parsing...\n");
	if (!handle_file_with_verif(fd, points))
		return (ft_printf("ERROR MAP!\n"), free(points), close(fd), 1);
	close(fd);
	data = create_window();
	if (data == NULL)
		return (ft_printf("ERROR MALLOC!\n"), free(points), 1);
	data->points = points;
	ft_printf("Parsed !\n");
	return (run_window(data));
}

int	kill_process(t_data *arg)
{
	arg->width = -1;
	if (arg->last_mouse)
		free(arg->last_mouse);
	if (arg->points)
	{
		ft_lstclear(arg->points->row, &free_row);
		free(arg->points->row);
		free(arg->points);
	}
	if (arg->cam_ang)
		free(arg->cam_ang);
	mlx_destroy_image(arg->mlx, arg->img);
	mlx_destroy_window(arg->mlx, arg->win);
	mlx_destroy_display(arg->mlx);
	free(arg->mlx);
	free(arg);
	arg = NULL;
	exit(0);
	return (0);
}
