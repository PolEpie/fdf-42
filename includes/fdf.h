#ifndef FTC_H
#define FTC_H

# define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
# define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

# include "mlx.h"
# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct	s_vector {
	float x;
	float y;
	float z;
}	t_vector;

typedef struct	s_points {
	int w;
	int h;
	int **row;
} 	t_points;

typedef struct	s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			height;
	int 		width;
	int 		endian;
	t_vector 	*last_mouse;
	t_vector 	*cam_ang;
	t_points 	*points;
} t_data;

typedef struct s_rect {
	unsigned short int	x;
	unsigned short int	y;
	unsigned short int	size_w;
	unsigned short int	size_h;
	int			color;
}	t_rect;

void		ft_mlx_pixel_put(t_data *data, int x, int y, int color);
t_vector	*matrix_multiply(const t_vector v_1[2], t_vector *v_2);
int			rgb_to_int(double r, double g, double b);
int 		draw_line_with_ppos(t_data *data, int beginX, int beginY, int endX, int endY, int color);
void		draw_rect(t_rect rect, t_data *data);
t_vector 	*Vector(float x, float y, float z);
#endif