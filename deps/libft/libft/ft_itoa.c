/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 22:58:39 by satkins           #+#    #+#             */
/*   Updated: 2018/05/03 18:48:14 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_getnumlength(int n)
{
	int	length;

	length = 0;
	if (n < 0)
	{
		length++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		length++;
	}
	return (length);
}

static	void	ft_itoa_helper(int n, char *new, int length)
{
	if (n < 0)
	{
		if (n < 0 && (n = -n))
			new[0] = '-';
		while (length > 0)
		{
			new[length--] = (n % 10) + '0';
			n /= 10;
		}
	}
	else
		while (length >= 0)
		{
			new[length--] = (n % 10) + '0';
			n /= 10;
		}
}

char			*ft_itoa(int n)
{
	char	*new;
	int		length;

	length = ft_getnumlength(n);
	new = (char *)malloc(((n ? length : 1) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	if (n)
	{
		if (n == -2147483648)
			return (ft_strcpy(new, "-2147483648"));
		new[length--] = '\0';
		ft_itoa_helper(n, new, length);
	}
	else
		ft_strcpy(new, "0");
	return (new);
}