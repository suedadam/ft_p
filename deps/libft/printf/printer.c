/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:12:19 by satkins           #+#    #+#             */
/*   Updated: 2018/03/12 16:44:18 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

static size_t	print_pres(char *str, t_flag arg_flag)
{
	size_t		len;

	len = ft_strlen(str);
	if (arg_flag.precision_set && arg_flag.precision < (int)len)
		len = arg_flag.precision;
	ft_putnstr_fd(str, len, g_fd);
	return (len);
}

static size_t	print_width(char *str, t_flag arg_flag)
{
	size_t		len;
	int			print_len;

	len = ft_strlen(str);
	print_len = 0;
	if (arg_flag.precision_set && arg_flag.precision < (int)len)
	{
		if (arg_flag.width_set)
			print_len = arg_flag.width - arg_flag.precision;
	}
	else if (arg_flag.width_set)
		print_len = arg_flag.width - len;
	len = 0;
	while (--print_len >= 0)
	{
		if (arg_flag.pad_zero)
			ft_putchar_fd('0', g_fd);
		else
			ft_putchar_fd(' ', g_fd);
		len++;
	}
	return (len);
}

size_t			str_format(char *str, t_flag arg_flag)
{
	size_t		len;

	if (arg_flag.left_allign)
	{
		len = print_pres(str, arg_flag);
		len += print_width(str, arg_flag);
	}
	else
	{
		len = print_width(str, arg_flag);
		len += print_pres(str, arg_flag);
	}
	return (len);
}

size_t			str_print(va_list *ap, t_flag arg_flag)
{
	char		*str;

	str = va_arg(*ap, char*);
	if (str == NULL)
		str = "(null)";
	return (str_format(str, arg_flag));
}
