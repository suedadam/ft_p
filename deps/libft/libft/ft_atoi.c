/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 22:58:39 by satkins           #+#    #+#             */
/*   Updated: 2016/07/19 23:00:46 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*pass_white_space(const char *str)
{
	while (*str != '\0' && (*str == ' ' ||
		*str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	return (str);
}

int					ft_atoi(const char *str)
{
	const char		*ptr;
	int				ret_val;
	int				negative;

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
	ret_val *= negative;
	if (negative == -1 && ret_val > 0)
		return (0);
	if (negative == 1 && ret_val < 0)
		return (-1);
	return (ret_val);
}
