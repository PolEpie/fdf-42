/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:57:11 by pepie             #+#    #+#             */
/*   Updated: 2024/10/16 14:30:35 by pepie            ###   ########.fr       */
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

# define WINDOW_W 1920
# define WINDOW_H 1080

# define KEY_ESC 65307
# define KEY_CTRL 65507
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100

# define SCROLL_UP 4
# define SCROLL_DOWN 5

# define DBL_MAX 1.7976931348623158e+308 /* max value */
# define DBL_MIN 2.2250738585072014e-308 /* min positive value */

# define FLT_MAX 3.402823466e+38F /* max value */
# define FLT_MIN 1.175494351e-38F /* min positive value */

# ifndef COLOR_1
#  define COLOR_1 0x581845
# endif
# ifndef COLOR_2
#  define COLOR_2 0x900C3F
# endif
# ifndef COLOR_3
#  define COLOR_3 0xC70039
# endif
# ifndef COLOR_4
#  define COLOR_4 0xFF5733
# endif
# ifndef COLOR_5
#  define COLOR_5 0xFFC30F
# endif

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
	int		min_z;
	int		max_z;
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
	double		amplitude;
	bool		is_ctrl_press;
	int			offset_x;
	int			offset_y;
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

typedef struct s_draw_squares_args {
	t_list	*lst;
	t_list	*lst_last_row;
	double	h_case_top;
	double	h_case_left;
	bool	is_border_left;
	bool	is_border_top;
	int		i;
	int		j;
	t_map	**lst_content;
	long	color;
}	t_draw_squares_args;

typedef struct s_draw_square_args_norm {
	t_data	*win;
	int		x;
	int		y;
	int		z;
}	t_draw_square_args_norm;

/* fdf.c */
int			kill_process(t_data *arg);

/* utils.c */
int			deg_to_rad(int angleInDegrees);
int			rad_to_deg(int angleInDegrees);
void		free_row(void *list);

/* windows_mouse.c */
int			handle_mouse_move(int x, int y, t_data *win);
int			handle_mouse_press(int button, int x, int y, t_data *win);
int			handle_mouse_release(int button, int x, int y, t_data *win);

/* windows_keybinds.c */
int			handle_key_down(int keycode, t_data *vars);
int			handle_key_up(int keycode, t_data *vars);

/* camera.c */
t_vector	*handle_point(t_data *win, t_vector *v);

/* draw.c */
int			draw_points(t_data *win);

/* parser_error.c */
bool		is_good_input(char *str);
void		error_free(char **splited, char *line);

/* parser.c */
int			parse_file(int fd, t_points *points);

void		ft_mlx_pixel_put(t_data *data, int x, int y, int color);
t_vector	*matrix_multiply(const t_vector v_1[2], t_vector *v_2);
int			rgb_to_int(double r, double g, double b);
int			draw_line_ppos(t_data *data, t_line *line);
void		draw_rect(t_rect rect, t_data *data);
t_vector	*vector_new(double x, double y, double z);

void		draw_square(t_draw_square_args_norm *ac, t_draw_squares_args *ag);
int			draw_squares(t_data *win);

#endif