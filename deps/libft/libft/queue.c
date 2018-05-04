/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 01:11:16 by ztisnes           #+#    #+#             */
/*   Updated: 2018/04/15 15:35:39 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_queue				*new_queue(void)
{
	t_queue			*node;

	if (!(node = (t_queue *)ft_memalloc(sizeof(t_queue))))
		return (NULL);
	node->first = NULL;
	node->last = NULL;
	return (node);
}

int					ft_enqueue(t_queue *queue, void *content, size_t c_size)
{
	t_node			*node;

	if (!queue || !content ||
		!(node = (t_node *)ft_memalloc(sizeof(t_node))) ||
		!(node->content = ft_memalloc(c_size)))
		return (EXIT_FAILURE);
	node->content = ft_memmove(node->content, content, c_size);
	node->next = NULL;
	if (!queue->last)
	{
		queue->last = node;
		queue->first = node;
	}
	else
	{
		queue->last->next = node;
		node->previous = queue->last;
		queue->last = node;
	}
	return (EXIT_SUCCESS);
}

void				*ft_dequeue(t_queue *queue)
{
	t_node			*tmp;
	void			*content;

	if (!queue)
		return (NULL);
	tmp = queue->first;
	if (tmp)
	{
		queue->first = tmp->next;
		if (!queue->first)
			queue->last = NULL;
		else
			queue->first->previous = NULL;
		content = tmp->content;
		free(tmp);
		return (content);
	}
	return (NULL);
}

void				*peek_queue(t_queue *queue)
{
	if (!queue || queue->first == NULL)
		return (NULL);
	return (queue->first->content);
}

int					isempty_queue(t_queue *queue)
{
	return (!queue || !queue->first);
}
