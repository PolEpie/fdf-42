/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:40:31 by pepie             #+#    #+#             */
/*   Updated: 2024/10/16 13:31:34 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > WINDOW_W || y > WINDOW_H || x < 0 || y < 0)
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

void	clamp_line(t_line *line)
{
	if (line->beginx < 0)
		line->beginx = 0;
	if (line->beginy < 0)
		line->beginy = 0;
	if (line->endx < 0)
		line->endx = 0;
	if (line->endy < 0)
		line->endy = 0;
	if (line->beginx > WINDOW_W)
		line->beginx = WINDOW_W;
	if (line->beginy > WINDOW_H)
		line->beginy = WINDOW_H;
	if (line->endx > WINDOW_W)
		line->endx = WINDOW_W;
	if (line->endy > WINDOW_H)
		line->endy = WINDOW_H;
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
