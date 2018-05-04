/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:04:37 by satkins           #+#    #+#             */
/*   Updated: 2018/03/12 16:31:38 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

size_t				char_print(long long num, t_flag arg_flags)
{
	unsigned char	chr;
	size_t			len;

	chr = (unsigned char)num;
	len = 1;
	if (arg_flags.left_allign)
	{
		ft_putchar_fd(chr, g_fd);
		if (arg_flags.width_set)
			while (--arg_flags.width > 0 && (len++))
				ft_putchar_fd(' ', g_fd);
	}
	else
	{
		if (arg_flags.width_set)
			while (--arg_flags.width > 0 && (len++))
			{
				if (arg_flags.pad_zero)
					ft_putchar_fd('0', g_fd);
				else
					ft_putchar_fd(' ', g_fd);
			}
		ft_putchar_fd(chr, g_fd);
	}
	return (len);
}
