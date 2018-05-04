/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pqueue.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:13:22 by satkins           #+#    #+#             */
/*   Updated: 2018/04/19 00:40:49 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_pqueue			*init_pqueue(void)
{
	t_pqueue		*node;

	node = (t_pqueue *)ft_memalloc(sizeof(t_pqueue));
	node->first = NULL;
	return (node);
}

void				ft_enpqueue(t_pqueue *queue, void *content, size_t c_size,
	int (*comparer)(void *, void *))
{
	t_node			*node;
	t_node			*tmp;

	node = (t_node *)ft_memalloc(sizeof(t_node));
	node->content = ft_memalloc(c_size);
	node->content = ft_memmove(node->content, content, c_size);
	node->next = NULL;
	if (!queue->first)
		queue->first = node;
	else
	{
		tmp = queue->first;
		if (!comparer(tmp->content, node->content))
		{
			queue->first = node;
			node->next = tmp;
		}
		else
		{
			while (tmp->next && comparer(tmp->next->content, node->content))
				tmp = tmp->next;
			node->next = tmp->next;
			tmp->next = node;
		}
	}
}

void				*ft_depqueue(t_pqueue *queue)
{
	t_node			*tmp;
	void			*content;

	tmp = queue->first;
	if (tmp)
	{
		queue->first = tmp->next;
		content = tmp->content;
		free(tmp);
		return (content);
	}
	return (NULL);
}

void				*peek_pqueue(t_pqueue *queue)
{
	if (!queue || queue->first == NULL)
		return (NULL);
	return (queue->first->content);
}

void				del_pqueue(t_pqueue *queue, void (*deconstruct)(void *ptr))
{
	t_node			*node;
	t_node			*hold;

	node = queue->first;
	while (node)
	{
		deconstruct(node->content);
		free(node->content);
		hold = node->next;
		free(node);
		node = hold;
	}
	free(queue);
}
