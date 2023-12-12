#include "fdf.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int rgb_to_int(double r, double g, double b)
{
	int color = 0;
    color |= (int)(b * 255);
    color |= (int)(g * 255) << 8;
    color |= (int)(r * 255) << 16;
    return (color);
}

int draw_line_with_ppos(t_data *data, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;

	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels; // 1
	deltaY /= pixels; // 0

	double pixelX = beginX;
	double pixelY = beginY;

	while (pixels)
	{
		if ((pixelX > 0 && pixelX < data->width) && (pixelY > 0 && pixelY < data->height))
			ft_mlx_pixel_put(data, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return 1;
}

void	draw_rect(t_rect rect, t_data *data) {
	unsigned short int	i;
	unsigned short int	j;

	i = 0;
	while (i < rect.size_h && i + rect.y < data->height) {
		j = 0;
		while (j < rect.size_w && j + rect.x < data->width) {
			ft_mlx_pixel_put(data, j + rect.x, i + rect.y, rect.color);
			j++;
		}
		i++;
	}
}