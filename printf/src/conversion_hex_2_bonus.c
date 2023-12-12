/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_hex_2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:33:27 by pepie             #+#    #+#             */
/*   Updated: 2023/11/24 11:35:32 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_leading_charts_start_hex(int num, t_parser *parser)
{
	int	len;

	len = 0;
	if (!parser->is_dash)
		len += add_leading_chars(get_total_hex_len(num, parser), parser,
				parser->space_number, parser->dot_number);
	else if (parser->is_point)
		len += add_leading_chars(get_total_hex_len(num, parser), parser, 0,
				parser->dot_number);
	return (len);
}
