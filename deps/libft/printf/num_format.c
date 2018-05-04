/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 21:40:09 by satkins           #+#    #+#             */
/*   Updated: 2017/11/09 21:40:11 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

unsigned long long int		unsigned_len(va_list *ap, t_flag arg_flag)
{
	unsigned long long int	num;

	if (arg_flag.e_length == hh)
		num = (unsigned char)va_arg(*ap, unsigned long long int);
	else if (arg_flag.e_length == h)
		num = (unsigned short)va_arg(*ap, unsigned long long int);
	else if (arg_flag.e_length == l)
		num = (unsigned long)va_arg(*ap, unsigned long long int);
	else if (arg_flag.e_length == ll)
		num = va_arg(*ap, unsigned long long int);
	else if (arg_flag.e_length == j)
		num = (uintmax_t)va_arg(*ap, unsigned long long int);
	else if (arg_flag.e_length == z)
		num = (size_t)va_arg(*ap, unsigned long long int);
	else
		num = (unsigned int)va_arg(*ap, unsigned long long int);
	return (num);
}

long long int				signed_len(va_list *ap, t_flag arg_flag)
{
	long long int			num;

	if (arg_flag.e_length == hh)
		num = (signed char)va_arg(*ap, long long int);
	else if (arg_flag.e_length == h)
		num = (short)va_arg(*ap, long long int);
	else if (arg_flag.e_length == l)
		num = (long)va_arg(*ap, long long int);
	else if (arg_flag.e_length == ll)
		num = va_arg(*ap, long long int);
	else if (arg_flag.e_length == j)
		num = (intmax_t)va_arg(*ap, long long int);
	else if (arg_flag.e_length == z)
		num = (ssize_t)va_arg(*ap, long long int);
	else
		num = (int)va_arg(*ap, long long int);
	return (num);
}

size_t						signed_print(va_list *ap,
	t_flag arg_flag, char type)
{
	long long				num;
	size_t					len;

	len = 0;
	if (type == 'D')
		arg_flag.e_length = l;
	num = signed_len(ap, arg_flag);
	if (type == 'c' || type == 'C')
		len = char_print(num, arg_flag);
	else if (type == 'C' || type == 'c')
		len = uchar_print(num, arg_flag);
	else if (type == 'i' || type == 'd' || type == 'D')
		len = int_print(num, arg_flag);
	return (len);
}

size_t						unsigned_print(va_list *ap,
	t_flag arg_flag, char type)
{
	unsigned long long		num;
	size_t					len;

	len = 0;
	if (type == 'O' || type == 'U')
		arg_flag.e_length = l;
	num = unsigned_len(ap, arg_flag);
	if (type == 'x')
		len = hex_print(num, arg_flag, 0);
	else if (type == 'X')
		len = hex_print(num, arg_flag, 1);
	else if (type == 'O' || type == 'o')
		len = oct_print(num, arg_flag);
	else if (type == 'U' || type == 'u')
		len = uint_print(num, arg_flag);
	return (len);
}
