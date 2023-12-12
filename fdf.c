#include "fdf.h"

t_vector	*handle_point(t_data *win, t_vector *v)
{
	float scale = 100;
	const t_vector rotationX[3] = {
		{1, 0, 0},
		{0, cos(win->cam_ang->x), -sin(win->cam_ang->x)},
		{0, sin(win->cam_ang->x), cos(win->cam_ang->x)}
	};
	const t_vector rotationY[3] = {
		{cos(win->cam_ang->y),0,-sin(win->cam_ang->y)},
		{0, 1, 0},
		{sin(win->cam_ang->y),0, cos(win->cam_ang->y)}
	};
	const t_vector rotationZ[3] = {
		{cos(win->cam_ang->z), -sin(win->cam_ang->z), 0},
		{sin(win->cam_ang->z), cos(win->cam_ang->z), 0},
		{0, 0, 1}
	};
	t_vector *projected2d;
	t_vector *rotated;


	rotated = matrix_multiply(rotationX, v);
	rotated = matrix_multiply(rotationY, rotated);
	rotated = matrix_multiply(rotationZ, rotated);

	float distance = 4;
	//float z = 1;
	float z = 1 / (distance - rotated->z);
	const t_vector projection[3] = {
		{z, 0, 0},
		{0, z, 0},
		{0, 0, 0},
	};
	projected2d = matrix_multiply(projection, rotated);
	
	if (projected2d->x)
		projected2d->x *= scale;
	if (projected2d->y)
		projected2d->y *= scale;
	if (projected2d->z)
		projected2d->z *= scale;
	projected2d->x += win->width / 2; // - ((win->points->w / 2) * scale)
	projected2d->y += win->height / 2;
	return (projected2d);
}

void draw_line(t_data *win, t_vector *v1, t_vector *v2)
{
	t_vector *pos1;
	t_vector *pos2;

	pos1 = handle_point(win, v1);
	pos2 = handle_point(win, v2);

	draw_line_with_ppos(win, pos1->x, pos1->y, pos2->x, pos2->y, rgb_to_int(0, 0, 255));
}

void	draw_square(t_data *win, int x, int y)
{
	t_vector v1;
	t_vector v2;

	v1.z = win->points->row[y][x];
	v2.z = win->points->row[y][x];
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

int draw_points(t_data *win)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	draw_rect((t_rect){0, 0, win->width, win->height, rgb_to_int(0, 0, 0)}, win);
	while (i < win->points->h)
	{
		j = 0;
		while (j < win->points->w)
		{
			draw_square(win, j, i);
			j++;
		}
		i++;
	}
	return (0);
}

int init_points(t_data *win, int w, int h)
{
	int i;
	int j;

	i = 0;
	j = 0;
	win->points = malloc(sizeof(t_points));
	if (!win->points)
		return (1);
	win->points->w = w;
	win->points->h = h;
	win->points->row = malloc(sizeof(int *) * h);
	while (i < h)
	{
		win->points->row[i] = malloc(sizeof(int) * w);
		j = 0;
		while (j < w)
		{
			win->points->row[i][j] = i - 1;
			j++;
		}
		i++;
	}
	return (0);
}

int handle_mouse_move(int x, int y, t_data *param)
{
	param->last_mouse->x = x;
	param->last_mouse->y = y;
	ft_printf("%d %d %d \n", x, y, param->height);
	return (0);
}

int handle_mouse_event(int button)
{
	ft_printf("%d \n", button);
	return (0);
}



int main(void)
{
	t_data win;

	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, 500, 500, "Fenetre de bg");
	win.img = mlx_new_image(win.mlx, 500, 500);

	win.addr = mlx_get_data_addr(win.img, &win.bits_per_pixel, &win.line_length,
								 &win.endian);

	win.width = 500;
	win.height = 500;

	win.cam_ang = Vector(degToRad(20), degToRad(0), degToRad(0));
	if (!win.cam_ang)
		return (1);
	win.last_mouse = Vector(0, 0, 0);
	if (!win.last_mouse)
		return (1);
	if (init_points(&win, 3, 3))
		return (1);
	mlx_do_key_autorepeaton(win.mlx);
	// mlx_hook(win.win, ON_KEYDOWN, (1L<<2), handle_keydown, &win);
	mlx_hook(win.win, ON_KEYUP, 1L<<1, handle_mouse_move, &win);
	mlx_hook(win.win, ON_MOUSEUP, 1L<<3, handle_mouse_move, &win);
	mlx_hook(win.win, ON_MOUSEMOVE, 1L << 6, handle_mouse_move, &win);
	//mlx_mouse_hook(win.win, handle_mouse_event, &win);
	mlx_loop_hook(win.mlx, draw_points, &win);
	mlx_loop(win.mlx);
}