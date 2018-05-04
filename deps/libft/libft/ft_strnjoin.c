/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 21:27:56 by satkins           #+#    #+#             */
/*   Updated: 2017/11/02 21:27:58 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnjoin(char const *s1, char const *s2, int i)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (i == 1 || i == 3)
	{
		free((void *)s1);
		s1 = NULL;
	}
	if (i == 2 || i == 3)
	{
		free((void *)s2);
		s2 = NULL;
	}
	return ((char *)ret);
}
