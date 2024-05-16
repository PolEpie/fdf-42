/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 00:16:48 by pepie             #+#    #+#             */
/*   Updated: 2024/05/16 14:17:28 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	*rotate_point(t_data *win, t_vector *v)
{
	const t_vector	rotationx[3] = {
	{1, 0, 0},
	{0, cos(win->cam_ang->x), -sin(win->cam_ang->x)},
	{0, sin(win->cam_ang->x), cos(win->cam_ang->x)}
	};
	const t_vector	rotationz[3] = {
	{cos(win->cam_ang->y), 0, -sin(win->cam_ang->y)},
	{0, 1, 0},
	{sin(win->cam_ang->y), 0, cos(win->cam_ang->y)}
	};
	t_vector		*rotated;

	rotated = matrix_multiply(rotationx, v);
	rotated = matrix_multiply(rotationz, rotated);
	return (rotated);
}

t_vector	*scale_point(float z, t_vector *vector, int scale)
{
	const t_vector	projection[3] = {
	{z, 0, 0},
	{0, z, 0},
	{0, 0, 0},
	};

	vector = matrix_multiply(projection, vector);
	if (vector->x)
		vector->x *= scale;
	if (vector->y)
		vector->y *= scale;
	if (vector->z)
		vector->z *= scale;
	return (vector);
}

t_vector	*handle_point(t_data *win, t_vector *v)
{
	double			distance;
	double			z;
	t_vector		*rotated;

	if (!win->cam_ang)
		return (0);
	rotated = rotate_point(win, v);
	distance = win->cam_ang->z;
	z = 1 / distance;
	rotated = scale_point(z, v, win->points->scale);
	rotated->x += win->width / 2;
	rotated->y += win->height / 2;
	return (rotated);
}
