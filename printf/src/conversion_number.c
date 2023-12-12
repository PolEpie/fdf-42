/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_number.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:35:54 by pepie             #+#    #+#             */
/*   Updated: 2023/11/24 12:08:34 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_unum_len(unsigned int nb)
{
	int				len;
	unsigned int	num;

	num = nb;
	len = 0;
	if (nb == 0)
		return (1);
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

int	get_num_len(int nb)
{
	if (nb < 0)
	{
		return (get_unum_len(nb * -1) + 1);
	}
	return (get_unum_len(nb));
}

int	get_unum_len_without_sign(unsigned int nb, t_parser *parser)
{
	if (nb == 0 && parser->is_point)
		return (0);
	return (get_unum_len(nb));
}

int	conversion_int(va_list *args, t_parser *parser)
{
	int		len;
	int		num;
	char	*str;

	num = va_arg(*args, int);
	len = 0;
	parser->is_negative = (num < 0);
	if (parser->is_plus && num >= 0)
		len += write(1, "+", 1);
	else if (parser->is_whitespace && num >= 0)
		len += write(1, " ", 1);
	if (parser->is_negative)
		str = ft_uitoa(num * -1);
	else
		str = ft_itoa(num);
	len += handle_leading_charts_start_int(num, parser);
	if (parser->is_point && num == 0)
		*str = '\0';
	len += write(1, str, ft_strlen(str));
	len += handle_leading_charts_end_int(parser,
			get_num_len_without_sign(num, parser));
	free(str);
	return (len);
}

int	conversion_unsigned_int(va_list *args, t_parser *parser)
{
	int				len;
	unsigned int	num;
	char			*str;

	num = va_arg(*args, unsigned int);
	len = 0;
	if (parser->is_plus)
		len += write(1, "+", 1);
	else if (parser->is_whitespace)
		len += write(1, " ", 1);
	if (!parser->is_dash)
		len += add_leading_chars(get_unum_len_without_sign(num, parser), parser,
				parser->space_number, parser->dot_number);
	else if (parser->dot_number)
		len += add_leading_chars(get_unum_len_without_sign(num, parser), parser,
				0, parser->dot_number);
	str = ft_uitoa(num);
	if (parser->is_point && num == 0)
		*str = '\0';
	len += write(1, str, ft_strlen(str));
	len += handle_leading_charts_end_int(parser,
			get_unum_len_without_sign(num, parser));
	free(str);
	return (len);
}
