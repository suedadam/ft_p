/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:43:36 by satkins           #+#    #+#             */
/*   Updated: 2018/04/15 15:31:01 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del_node(t_node *node, t_node *prev)
{
	if (node)
	{
		if (node->next)
			node->next->previous = node->previous;
		if (prev)
			prev->next = node->next;
		free(node);
	}
}
