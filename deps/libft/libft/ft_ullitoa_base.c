/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ullitoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:34:26 by satkins           #+#    #+#             */
/*   Updated: 2017/11/16 14:34:29 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_ullitoa_base(unsigned long long int num, int base)
{
	static char		buf[32] = "0";
	int				i;
	int				digit;

	i = 30;
	if (num == 0)
		return (ft_strcpy(buf, "0\0"));
	while (num > 0 && i > 0)
	{
		digit = num % base;
		if (digit >= 10)
			buf[i] = 'a' + (digit % 10);
		else
			buf[i] = '0' + digit;
		num /= base;
		i--;
	}
	return (buf + i + 1);
}
