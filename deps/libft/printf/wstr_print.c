/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstr_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:20:36 by satkins           #+#    #+#             */
/*   Updated: 2018/03/12 16:49:49 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

static size_t	ft_wstrlen(wchar_t *str, int precision_set, int precision)
{
	size_t		len;

	len = 0;
	while (*str != '\0' && (!precision_set || precision != 0))
	{
		if (*str <= 0x7F && (++len))
			precision--;
		else if (*str <= 0x7FF && (!precision_set
			|| precision >= 4) && ((precision -= 4) || !precision))
			len += 2;
		else if (*str <= 0xFFFF && (!precision_set
			|| precision >= 4) && ((precision -= 4) || !precision))
			len += 3;
		else if (*str <= 0x10FFFF && (!precision_set
			|| precision >= 4) && ((precision -= 4) || !precision))
			len += 4;
		else
			return (len);
		str++;
	}
	return (len);
}

static void		ft_putnwstr(wchar_t *str, size_t len)
{
	while (*str != '\0' && len-- > 0)
	{
		if (*str <= 0x7F)
			ft_putchar_fd(*str, g_fd);
		else if (*str <= 0x7FF)
		{
			ft_putchar_fd((*str >> 6) + 0xC0, g_fd);
			ft_putchar_fd((*str & 0x3F) + 0x80, g_fd);
		}
		else if (*str <= 0xFFFF)
		{
			ft_putchar_fd((*str >> 12) + 0xE0, g_fd);
			ft_putchar_fd(((*str >> 6) & 0x3F) + 0x80, g_fd);
			ft_putchar_fd((*str & 0x3F) + 0x80, g_fd);
		}
		else if (*str <= 0x10FFFF)
		{
			ft_putchar_fd((*str >> 18) + 0xF0, g_fd);
			ft_putchar_fd(((*str >> 12) & 0x3F) + 0x80, g_fd);
			ft_putchar_fd(((*str >> 6) & 0x3F) + 0x80, g_fd);
			ft_putchar_fd((*str & 0x3F) + 0x80, g_fd);
		}
		str++;
	}
}

static size_t	print_wpres(wchar_t *str, t_flag arg_flag)
{
	size_t		len;

	len = ft_wstrlen(str, arg_flag.precision_set, arg_flag.precision);
	if (arg_flag.precision_set && arg_flag.precision < (int)len)
		len = arg_flag.precision;
	ft_putnwstr(str, len);
	return (len);
}

static size_t	print_wwidth(wchar_t *str, t_flag arg_flag)
{
	size_t		len;
	int			print_len;

	len = ft_wstrlen(str, arg_flag.precision_set, arg_flag.precision);
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

size_t			wstr_print(va_list *ap, t_flag arg_flag)
{
	wchar_t		*str;
	size_t		len;

	str = va_arg(*ap, wchar_t*);
	if (str == NULL)
		return (str_format("(null)", arg_flag));
	if (arg_flag.left_allign)
	{
		len = print_wpres(str, arg_flag);
		len += print_wwidth(str, arg_flag);
	}
	else
	{
		len = print_wwidth(str, arg_flag);
		len += print_wpres(str, arg_flag);
	}
	return (len);
}
