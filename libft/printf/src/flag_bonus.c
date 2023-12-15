/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:49:00 by pepie             #+#    #+#             */
/*   Updated: 2023/11/24 13:52:42 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

enum e_flag	get_flag_type(char c)
{
	if (c == '#')
		return (FLAG_HASHTAG);
	if (c == ' ')
		return (FLAG_WHITESPACE);
	if (c == '+')
		return (FLAG_PLUS);
	if (c == '.')
		return (FLAG_DOT);
	if (c == '0')
		return (FLAG_ZERO);
	if (c >= '1' && c <= '9')
		return (FLAG_NUMBER);
	if (c == '-')
		return (FLAG_DASH);
	return (FLAG_ERROR);
}

bool	add_flag_to_parser(t_parser *parser, enum e_flag flag_type)
{
	if (flag_type == FLAG_HASHTAG)
		parser->is_hashtag = true;
	else if (flag_type == FLAG_WHITESPACE)
		parser->is_whitespace = true;
	else if (flag_type == FLAG_PLUS)
		parser->is_plus = true;
	else if (flag_type == FLAG_ZERO)
		parser->is_zero = true;
	else if (flag_type == FLAG_DOT)
		parser->is_point = true;
	else if (flag_type == FLAG_NUMBER)
		return (true);
	else if (flag_type == FLAG_DASH)
		parser->is_dash = true;
	return (false);
}

char	*get_number_flag(char *str, t_parser *parser, int flag_type)
{
	int	num;

	num = ft_atoi(str);
	if (flag_type == FLAG_DOT)
		parser->dot_number = num;
	else if (flag_type == FLAG_ZERO)
		parser->zero_number = num;
	else
		parser->space_number = num;
	return (str + get_num_len(num));
}

void	init_parser(t_parser *parser)
{
	parser->is_hashtag = false;
	parser->is_plus = false;
	parser->is_whitespace = false;
	parser->is_zero = false;
	parser->is_dash = false;
	parser->is_point = false;
	parser->space_number = 0;
	parser->dot_number = 0;
	parser->zero_number = 0;
	parser->temp = 0;
	parser->is_negative = false;
	parser->minus_printed = false;
}
