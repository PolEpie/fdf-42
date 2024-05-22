/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_keybinds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 03:45:30 by pepie             #+#    #+#             */
/*   Updated: 2024/05/22 13:06:16 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_down(int keycode, t_data *vars)
{
	if (keycode == KEY_ESC)
		kill_process(vars);
	else if (keycode == KEY_CTRL)
		vars->is_ctrl_press = false;
	return (0);
}

int	handle_key_up(int keycode, t_data *vars)
{
	if (keycode == KEY_CTRL)
		vars->is_ctrl_press = true;
	return (0);
}
