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

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	const char	*src_ptr;
	char		*dst_ptr;

	i = 0;
	dst_ptr = (char *)dst;
	src_ptr = (const char *)src;
	if (dst < src)
		while (i < len)
		{
			dst_ptr[i] = src_ptr[i];
			i++;
		}
	else
		while (len > 0)
		{
			dst_ptr[len - 1] = src_ptr[len - 1];
			len--;
		}
	return (dst);
}
