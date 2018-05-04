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

char				*ft_strtrim(char const *s)
{
	unsigned int	i;
	unsigned int	start;
	unsigned int	end;
	char			*ret;

	i = 0;
	ret = NULL;
	end = 0;
	start = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	start = i;
	if (ft_strlen(s) > 0)
		i = ft_strlen(s) - 1;
	else
		return ("");
	while (i > start && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i--;
	end = i;
	if (!(ret = (char *)ft_memalloc(sizeof(char) * (end - start) + 1)))
		return (NULL);
	ret = ft_strsub(s, start, (size_t)end - start + 1);
	return (ret);
}
