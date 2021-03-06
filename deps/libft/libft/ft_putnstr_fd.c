/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:24:47 by satkins           #+#    #+#             */
/*   Updated: 2018/03/12 16:25:08 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr_fd(char *str, int len, int fd)
{
	int	i;

	i = 0;
	while (*str != '\0' && i < len)
	{
		write(fd, str, 1);
		str++;
		i++;
	}
}
