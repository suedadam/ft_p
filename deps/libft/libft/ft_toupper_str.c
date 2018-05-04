/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:01:01 by satkins           #+#    #+#             */
/*   Updated: 2017/11/13 15:01:06 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_toupper_str(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i] != '\0')
		str[i] = ft_toupper(str[i]);
}
