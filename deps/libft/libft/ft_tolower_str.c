/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:50:36 by satkins           #+#    #+#             */
/*   Updated: 2017/11/14 15:50:44 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tolower_str(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i] != '\0')
		str[i] = ft_tolower(str[i]);
}
