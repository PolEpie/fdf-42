/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 00:03:38 by pepie             #+#    #+#             */
/*   Updated: 2024/05/16 16:39:17 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_mouse_move(int x, int y, t_data *win)
{
	float	xdelta;
	float	ydelta;

	xdelta = win->last_mouse->x - x;
	ydelta = win->last_mouse->y - y;
	if (win->mouse_pressed)
	{
		win->cam_ang->y += xdelta / 8;
		win->cam_ang->x += ydelta / 8;
	}
	win->last_mouse->x = x;
	win->last_mouse->y = y;
	return (0);
}

void	handle_mouse_scroll(bool is_up, t_data *win)
{
	if (is_up)
		win->cam_ang->z -= 1;
	else
		win->cam_ang->z += 1;
	if (win->cam_ang->z <= 1)
		win->cam_ang->z = 1;
}

int	handle_mouse_press(int button, int x, int y, t_data *win)
{
	(void)x;
	(void)y;
	if (button == 1)
		win->mouse_pressed = true;
	else if (button == SCROLL_UP)
		handle_mouse_scroll(true, win);
	else if (button == SCROLL_DOWN)
		handle_mouse_scroll(false, win);
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_data *win)
{
	(void)x;
	(void)y;
	if (button == 1)
		win->mouse_pressed = false;
	return (0);
}
