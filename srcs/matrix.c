/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:40:25 by pepie             #+#    #+#             */
/*   Updated: 2023/12/18 01:26:48 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	*matrix_multiply(const t_vector v_1[2], t_vector *v_2)
{
	t_vector	*res;

	res = malloc(sizeof(t_vector));
	if (!res)
		return (NULL);
	res->x = (v_1[0].x * v_2->x) + (v_1[0].y * v_2->y) + (v_1[0].z * v_2->z);
	res->y = (v_1[1].x * v_2->x) + (v_1[1].y * v_2->y) + (v_1[1].z * v_2->z);
	res->z = (v_1[2].x * v_2->x) + (v_1[2].y * v_2->y) + (v_1[2].z * v_2->z);
	return (res);
}

t_vector	*vector_new(float x, float y, float z)
{
	t_vector	*vector;

	vector = malloc(sizeof(vector));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}
