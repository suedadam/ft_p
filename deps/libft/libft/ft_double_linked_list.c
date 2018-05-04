/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_linked_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:17:15 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/04/15 15:30:36 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblist		*new_dblist(void)
{
	t_dblist			*dblist;

	if (!(dblist = (t_dblist *)ft_memalloc(sizeof(t_dblist))))
		return (NULL);
	dblist->first = NULL;
	dblist->last = NULL;
	dblist->nbr_elements = 0;
	return (dblist);
}

int				dbl_push_end(t_dblist *dblist, void *content, size_t c_size)
{
	t_node			*node;

	if (!dblist || !content ||
		!(node = (t_node *)ft_memalloc(sizeof(t_node))) ||
		!(node->content = ft_memalloc(c_size)))
		return (EXIT_FAILURE);
	node->content = ft_memmove(node->content, content, c_size);
	node->next = node;
	node->previous = node;
	dblist->nbr_elements++;
	if (!dblist->last)
	{
		dblist->last = node;
		dblist->first = node;
	}
	else
	{
		dblist->last->next = node;
		node->previous = dblist->last;
		node->next = dblist->first;
		dblist->last = node;
	}
	return (EXIT_SUCCESS);
}

int				dbl_push_front(t_dblist *dblist, void *content, size_t c_size)
{
	t_node			*node;

	if (!dblist || !content ||
		!(node = (t_node *)ft_memalloc(sizeof(t_node))) ||
		!(node->content = ft_memalloc(c_size)))
		return (EXIT_FAILURE);
	node->content = ft_memmove(node->content, content, c_size);
	node->next = node;
	node->previous = node;
	dblist->nbr_elements++;
	if (!dblist->last)
	{
		dblist->last = node;
		dblist->first = node;
	}
	else
	{
		node->next = dblist->first;
		node->previous = dblist->last;
		dblist->last->next = node;
		dblist->first->previous = node;
		dblist->first = node;
	}
	return (EXIT_SUCCESS);
}

int				isempty_dblist(t_dblist *dblist)
{
	return (!dblist || !dblist->first);
}
