/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:26:09 by satkins           #+#    #+#             */
/*   Updated: 2018/01/23 15:26:11 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char		*pass_white_space(const char *str)
{
	while (*str != '\0' && (*str == ' ' ||
		*str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	return (str);
}

long long				ft_atoll(const char *str)
{
	const char			*ptr;
	unsigned long long	ret_val;
	int					negative;

	ret_val = 0;
	negative = 1;
	str = pass_white_space(str);
	if (*str != '-' && !ft_isdigit(*str) && *str != '+')
		return (0);
	if (*str == '-')
		negative = -1;
	if (*str == '+' || *str == '-')
		str++;
	ptr = str;
	while (*ptr != '\0' && ft_isdigit(*ptr))
	{
		ret_val = (ret_val * 10) + *ptr - '0';
		ptr++;
	}
	return (negative * (long long)ret_val);
}
