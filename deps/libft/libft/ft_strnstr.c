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

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 1;
	if (*little == '\0')
		return ((char *)big);
	while (*big != '\0' && i < len)
	{
		if (ft_strncmp(big, little, n) == 0)
		{
			while (i + n <= len && ft_strncmp(big, little, n) == 0)
			{
				if (little[n] == '\0')
					return ((char *)big);
				n++;
			}
		}
		big++;
		i++;
	}
	return (NULL);
}
