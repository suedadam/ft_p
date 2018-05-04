/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:57:20 by ztisnes           #+#    #+#             */
/*   Updated: 2018/04/15 15:35:34 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack				*new_stack(void)
{
	t_stack			*node;

	if (!(node = (t_stack *)ft_memalloc(sizeof(t_stack))))
		return (NULL);
	node->top = NULL;
	return (node);
}

int					ft_stackpush(t_stack *stack, void *content, size_t c_size)
{
	t_node			*node;

	if (!stack || !content ||
		!(node = (t_node *)ft_memalloc(sizeof(t_node))) ||
		!(node->content = ft_memalloc(c_size)))
		return (EXIT_FAILURE);
	node->content = ft_memmove(node->content, content, c_size);
	node->next = stack->top;
	stack->top = node;
	return (EXIT_SUCCESS);
}

void				*ft_stackpop(t_stack *stack)
{
	t_node			*next;
	void			*anything;

	if (!stack || stack->top == NULL)
		return (NULL);
	next = stack->top->next;
	anything = stack->top->content;
	free(stack->top);
	stack->top = next;
	return (anything);
}

void				*ft_stackpeak(t_stack *stack)
{
	if (!stack || stack->top == NULL)
		return (NULL);
	return (stack->top->content);
}

int					isempty_stack(t_stack *stack)
{
	return (!stack || stack->top == NULL);
}
