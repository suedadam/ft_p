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

static void	ft_print_index_fd(int nb, int *nbr, int index, int fd)
{
	if (nb > 0)
	{
		while (nb > 0)
		{
			nbr[index] = (nb % 10);
			nb = nb / 10;
			index++;
		}
	}
	else
	{
		ft_putchar_fd('-', fd);
		while (nb < 0)
		{
			nbr[index] = (nb % 10) * -1;
			nb = nb / 10;
			index++;
		}
	}
	index--;
	while (index >= 0)
	{
		ft_putchar_fd(nbr[index] + '0', fd);
		index--;
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	int		nbr[10];

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
	}
	else
		ft_print_index_fd(n, nbr, 0, fd);
}
