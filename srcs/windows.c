/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:40:31 by pepie             #+#    #+#             */
/*   Updated: 2024/05/16 13:40:45 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 1920 || y > 1080 || x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	rgb_to_int(double r, double g, double b)
{
	int	color;

	color = 0;
	color |= (int)(b * 255);
	color |= (int)(g * 255) << 8;
	color |= (int)(r * 255) << 16;
	return (color);
}

int	draw_line_ppos(t_data *data, t_line *line)
{
	double	deltax;
	double	deltay;
	double	pixx;
	double	pixy;
	int		pixels;

	if (line->beginx == line->endx && line->beginy == line->endy)
		return (1);
	if (line->beginx < 0)
		line->beginx = 0;
	if (line->beginy < 0)
		line->beginy = 0;
	if (line->endx < 0)
		line->endx = 0;
	if (line->endy < 0)
		line->endy = 0;
	if (line->beginx > 1920)
		line->beginx = 1920;
	if (line->beginy > 1920)
		line->beginy = 1920;
	if (line->endx > 1920)
		line->endx = 1920;
	if (line->endy > 1920)
		line->endy = 1920;
	deltay = line->endy - line->beginy;
	deltax = line->endx - line->beginx;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixx = line->beginx;
	pixy = line->beginy;
	while (pixels)
	{
		ft_mlx_pixel_put(data, pixx, pixy, line->col);
		pixx += deltax;
		pixy += deltay;
		--pixels;
	}
	return (1);
}

void	draw_rect(t_rect rect, t_data *data)
{
	unsigned short int	i;
	unsigned short int	j;

	i = 0;
	while (i < rect.size_h && i + rect.y < data->height)
	{
		j = 0;
		while (j < rect.size_w && j + rect.x < data->width)
		{
			ft_mlx_pixel_put(data, j + rect.x, i + rect.y, rect.color);
			j++;
		}
		i++;
	}
}
