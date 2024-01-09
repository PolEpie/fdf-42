/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_keybinds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 03:45:30 by pepie             #+#    #+#             */
/*   Updated: 2024/01/06 03:36:31 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_down(int keycode, t_data *vars)
{
	if (keycode == KEY_ESC)
		kill_process(vars);
	return (0);
}
