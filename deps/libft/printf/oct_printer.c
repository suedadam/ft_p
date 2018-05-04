/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oct_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:19:16 by satkins           #+#    #+#             */
/*   Updated: 2018/03/12 16:43:42 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

static void	get_zeros(int *zeros, int *spaces, size_t *len, t_flag arg_flag)
{
	*spaces = 0;
	*zeros = 0;
	if (arg_flag.prefix)
		*zeros = 1;
	if (arg_flag.precision_set && arg_flag.precision > (int)*len)
		*zeros = arg_flag.precision - (int)*len;
	if (arg_flag.width_set && arg_flag.width > (int)*len + *zeros)
		*spaces = arg_flag.width - ((int)*len + *zeros);
	*len += *spaces + *zeros;
}

static void	right_print(t_flag arg_flag, int spaces, int zeros, char *str)
{
	if (arg_flag.pad_zero && !arg_flag.precision_set)
	{
		zeros += spaces;
		spaces = 0;
	}
	while (spaces-- > 0)
		ft_putchar_fd(' ', g_fd);
	while (zeros-- > 0)
		ft_putchar_fd('0', g_fd);
	ft_putstr_fd(str, g_fd);
}

size_t		oct_print(unsigned long long int num, t_flag arg_flag)
{
	size_t	len;
	char	*str;
	int		zeros;
	int		spaces;

	if (num == 0 && (arg_flag.precision_set || arg_flag.prefix))
		str = "\0";
	else
		str = ft_ullitoa_base(num, 8);
	len = ft_strlen(str);
	get_zeros(&zeros, &spaces, &len, arg_flag);
	if (arg_flag.left_allign)
	{
		while (zeros-- > 0)
			ft_putchar_fd('0', g_fd);
		ft_putstr_fd(str, g_fd);
		while (spaces-- > 0)
			ft_putchar_fd(' ', g_fd);
	}
	else
		right_print(arg_flag, spaces, zeros, str);
	return (len);
}
