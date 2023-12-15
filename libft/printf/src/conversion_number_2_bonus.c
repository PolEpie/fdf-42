/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_number_2_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:40:48 by pepie             #+#    #+#             */
/*   Updated: 2023/11/24 12:08:16 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_leading_charts_end_int(t_parser *parser, int len_num)
{
	int	len;

	len = 0;
	if (parser->is_dash)
	{
		if (parser->dot_number > len_num)
			len += add_leading_chars(parser->dot_number, parser,
					parser->space_number, 0);
		else
			len += add_leading_chars(len_num,
					parser, parser->space_number, 0);
	}
	return (len);
}

int	get_num_len_without_sign(int nb, t_parser *parser)
{
	if (nb < 0 && parser->is_point)
		return (get_unum_len(nb * -1));
	if (nb == 0 && parser->is_point)
		return (0);
	return (get_num_len(nb));
}

int	handle_leading_charts_start_int(unsigned int num, t_parser *parser)
{
	int	len;

	len = 0;
	if (!parser->is_dash || (parser->is_dash && parser->dot_number
			> (get_num_len_without_sign(num, parser) - parser->is_negative)))
	{
		if (parser->is_dash)
			len += add_leading_chars(get_num_len_without_sign(num, parser),
					parser, 0, parser->dot_number);
		else
			len += add_leading_chars(get_num_len_without_sign(num, parser),
					parser, parser->space_number, parser->dot_number);
	}
	else if (parser->is_negative && !parser->minus_printed)
	{
		parser->minus_printed = true;
		len += write(1, "-", 1);
	}
	else if (parser->dot_number)
		len += add_leading_chars(get_num_len_without_sign(num, parser), parser,
				0, parser->dot_number);
	return (len);
}
