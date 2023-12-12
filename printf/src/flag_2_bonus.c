/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:54:45 by pepie             #+#    #+#             */
/*   Updated: 2023/11/24 13:59:46 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	space_get_space_len(int num, t_parser *parser, int space_n)
{
	int		i;

	i = num - space_n;
	if (parser->is_point && parser->is_zero && parser->temp == 0)
	{	
		i = num - parser->zero_number;
		parser->temp = space_n;
	}
	else if (parser->is_point && parser->is_zero
		&& parser->zero_number > parser->temp)
	{
		if (parser->zero_number > num
			&& parser->conversion_type == CONVERSION_PERCENT)
		{
			i = 0;
			parser->temp = parser->zero_number;
		}
		else if (num > parser->temp)
			i = -parser->zero_number + parser->temp + (num - parser->temp);
		else
			i = -parser->zero_number + parser->temp;
	}
	return (i);
}

int	handle_space(int num, t_parser *parser, int space_num)
{
	int		i;
	int		len_written;

	len_written = 0;
	if (parser->is_point && (parser->conversion_type == CONVERSION_CHARACTER
			|| parser->conversion_type == CONVERSION_POINTER))
		return (0);
	i = space_get_space_len(num, parser, space_num);
	if (parser->is_negative && i < 0 && parser->is_point)
	{
		i += 1;
		parser->space_removed = true;
	}
	while (i < 0)
	{
		len_written += write(1, " ", 1);
		i++;
	}
	return (len_written);
}

int	handle_zero_2(int i, t_parser *parser)
{
	int	len_written;

	len_written = 0;
	while (i < 0)
	{
		if (parser->is_zero && !parser->is_dash
			&& (parser->conversion_type == CONVERSION_INTEGER
				|| parser->conversion_type == CONVERSION_DECIMAL
				|| parser->conversion_type == CONVERSION_UNSIGNED
				|| parser->conversion_type == CONVERSION_HEX_LOWER
				|| parser->conversion_type == CONVERSION_HEX_UPPER
				|| parser->conversion_type == CONVERSION_PERCENT))
			len_written += write(1, "0", 1);
		else if (parser->is_point
			&& (parser->conversion_type == CONVERSION_INTEGER
				|| parser->conversion_type == CONVERSION_DECIMAL
				|| parser->conversion_type == CONVERSION_UNSIGNED
				|| parser->conversion_type == CONVERSION_HEX_LOWER
				|| parser->conversion_type == CONVERSION_HEX_UPPER))
			len_written += write(1, "0", 1);
		i++;
	}
	return (len_written);
}

int	handle_zero(int num, t_parser *parser)
{
	int		i;

	i = num - parser->temp;
	if (parser->temp == 0 && parser->zero_number && !parser->is_point)
		i = num - parser->zero_number;
	return (handle_zero_2(i, parser));
}

int	add_leading_chars(int num, t_parser *parser, int space_num, int dot_number)
{
	int		len_written;

	len_written = 0;
	parser->temp = dot_number;
	if (parser->is_point && (parser->conversion_type == CONVERSION_CHARACTER
			|| parser->conversion_type == CONVERSION_POINTER))
		return (0);
	len_written += handle_space(num, parser, space_num);
	if (parser->is_negative && !parser->minus_printed)
	{
		len_written += write(1, "-", 1);
		parser->minus_printed = true;
	}
	len_written += handle_zero(num, parser);
	return (len_written);
}
