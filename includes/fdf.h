/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:57:11 by pepie             #+#    #+#             */
/*   Updated: 2024/01/03 04:01:02 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define KEY_ESC 65307

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_points
{
	int		w;
	int		h;
	t_list	**row;
}	t_points;

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
	bool		mouse_pressed;
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
	float	beginx;
	float	beginy;
	float	endx;
	float	endy;
	int		col;
}	t_line;

/* fdf.c */
void		kill_process(t_data *arg);

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
t_vector	*vector_new(float x, float y, float z);

#endif