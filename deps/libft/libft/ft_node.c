/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 18:19:33 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/04/14 18:21:19 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node		*new_node(void)
{
	t_node		*node;

	if (!(node = ft_memalloc(sizeof(t_node))))
		return (NULL);
	node->content = NULL;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}
