/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:57:11 by pepie             #+#    #+#             */
/*   Updated: 2024/05/16 14:00:34 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <X11/X.h>

# define KEY_ESC 65307

# define SCROLL_UP 4
# define SCROLL_DOWN 5

# define DBL_MAX 1.7976931348623158e+308 /* max value */
# define DBL_MIN 2.2250738585072014e-308 /* min positive value */

# define FLT_MAX 3.402823466e+38F /* max value */
# define FLT_MIN 1.175494351e-38F /* min positive value */

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_points
{
	int		w;
	int		h;
	int		scale;
	t_list	**row;
}	t_points;

typedef struct s_map
{
	long	color;
	int		y;
}	t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			height;
	int			width;
	int			endian;
	t_vector	*last_mouse;
	t_vector	*cam_ang;
	t_points	*points;
	int			mouse_pressed;
	float		amplitude;
}	t_data;

typedef struct s_rect
{
	unsigned short int	x;
	unsigned short int	y;
	unsigned short int	size_w;
	unsigned short int	size_h;
	int					color;
}	t_rect;

typedef struct s_line
{
	int		beginx;
	int		beginy;
	int		endx;
	int		endy;
	int		col;
}	t_line;

/* fdf.c */
int			kill_process(t_data *arg);

/* utils.c */
int			deg_to_rad(int angleInDegrees);
int			rad_to_deg(int angleInDegrees);

/* windows_mouse.c */
int			handle_mouse_move(int x, int y, t_data *win);
int			handle_mouse_press(int button, int x, int y, t_data *win);
int			handle_mouse_release(int button, int x, int y, t_data *win);

/* windows_keybinds.c */
int			handle_key_down(int keycode, t_data *vars);

/* camera.c */
t_vector	*handle_point(t_data *win, t_vector *v);

/* draw.c */
int			draw_points(t_data *win);

/* parser.c */
int			parse_file(int fd, t_points *points);

void		ft_mlx_pixel_put(t_data *data, int x, int y, int color);
t_vector	*matrix_multiply(const t_vector v_1[2], t_vector *v_2);
int			rgb_to_int(double r, double g, double b);
int			draw_line_ppos(t_data *data, t_line *line);
void		draw_rect(t_rect rect, t_data *data);
t_vector	*vector_new(double x, double y, double z);

#endif