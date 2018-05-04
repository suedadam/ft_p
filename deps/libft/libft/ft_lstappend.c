/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 18:08:15 by satkins           #+#    #+#             */
/*   Updated: 2018/03/12 16:58:13 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **head, t_list *newl)
{
	t_list	*tmp;

	tmp = *head;
	if (!(*head))
		*head = newl;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newl;
	}
}
