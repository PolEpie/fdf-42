/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 00:12:47 by pepie             #+#    #+#             */
/*   Updated: 2023/12/18 03:27:38 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	run_window(t_points *points)
{
	t_data	win;

	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, 500, 500, "Fenetre de bg");
	win.img = mlx_new_image(win.mlx, 500, 500);
	win.addr = mlx_get_data_addr(win.img, &win.bits_per_pixel, &win.line_length,
			&win.endian);
	win.width = 500;
	win.height = 500;
	win.mouse_pressed = false;
	win.cam_ang = vector_new(deg_to_rad(20), deg_to_rad(0), deg_to_rad(0));
	if (!win.cam_ang)
		return (1);
	win.last_mouse = vector_new(0, 0, 0);
	win.points = points;
	if (!win.last_mouse)
		return (1);
	mlx_do_key_autorepeaton(win.mlx);
	mlx_hook(win.win, ON_MOUSEDOWN, (1L << 2), handle_mouse_press, &win);
	mlx_hook(win.win, ON_MOUSEUP, (1L << 3), handle_mouse_release, &win);
	mlx_hook(win.win, ON_MOUSEMOVE, (1L << 6), handle_mouse_move, &win);
	mlx_loop_hook(win.mlx, draw_points, &win);
	mlx_loop(win.mlx);
	return (0);
}

int	init_points(t_points *points)
{
	points->row = malloc(sizeof(t_list *));
	if (!(points->row))
		return (0);
	*(points->row) = NULL;
	if (points->w < 0)
		return (0);
	return (1);
}

int	main(int argv, char **argc)
{
	int			fd;
	t_points	*points;

	if (argv != 2)
		return (write(2, "Wrong args: Exemple ./fdf test_maps/42.fdf\n", 43)
			, 1);
	fd = open(*(argc + 1), O_RDONLY);
	if (fd < 0)
		return (write(2, "Wrong file: Can't open\n", 23), 1);
	points = malloc(sizeof(t_points));
	if (!points)
		return (1);
	if (!init_points(points))
		return (1);
	if (!parse_file(fd, points))
		return (1);
	return (run_window(points));
}
