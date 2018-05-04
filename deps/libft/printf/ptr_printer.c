/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:21:40 by satkins           #+#    #+#             */
/*   Updated: 2018/03/12 16:45:13 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

static size_t	print_prefix_str(char *str, t_flag arg_flag)
{
	size_t		len;
	int			i;

	len = 2;
	ft_putstr_fd("0x", g_fd);
	if (arg_flag.precision_set)
	{
		if (arg_flag.precision != 0)
		{
			while (arg_flag.precision-- > (int)ft_strlen(str))
			{
				ft_putchar_fd('0', g_fd);
				len++;
			}
		}
		else if (str[0] == '0' && str[1] == '\0')
			return (len);
	}
	len += ft_strlen(str);
	i = -1;
	while (++i < arg_flag.width - (int)len)
		arg_flag.pad_zero ? ft_putchar_fd('0', g_fd) : 0;
	ft_putstr_fd(str, g_fd);
	return (len);
}

size_t			ptr_print(va_list *ap, t_flag a)
{
	char		*s;
	size_t		len;
	int			i;

	s = ft_ullitoa_base((unsigned long long int)va_arg(*ap, void *), 16);
	if (a.width_set && (i = -1))
	{
		if (a.left_allign || !(len = 2))
		{
			len = print_prefix_str(s, a);
			while (++i < a.width - (int)len)
				ft_putchar_fd(' ', g_fd);
			return (a.width > (int)len ? a.width : len);
		}
		len += a.precision > (int)ft_strlen(s) ? a.precision : ft_strlen(s);
		len = a.precision_set && !a.precision && *s == '0' && !s[1] ? 2 : len;
		while (++i < a.width - (int)len)
			!a.pad_zero ? ft_putchar_fd(' ', g_fd) : 1;
		len = print_prefix_str(s, a);
		return (a.width > (int)len ? a.width : len);
	}
	return (print_prefix_str(s, a));
}
