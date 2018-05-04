/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitwhitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 22:58:39 by satkins           #+#    #+#             */
/*   Updated: 2018/04/15 15:30:52 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		word_count(const char *s)
{
	int			i;

	i = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && IS_WHITESPACE(*s))
			s++;
		if (*s != '\0')
			i++;
		while (*s != '\0' && !IS_WHITESPACE(*s))
			s++;
	}
	return (i);
}

static size_t	word_len(char const *s)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0' && !IS_WHITESPACE(s[i]))
		i++;
	return (i);
}

static char		*next_word(char const *s)
{
	while (*s != '\0' && IS_WHITESPACE(*s))
		s++;
	return ((char *)s);
}

char			**ft_splitwhitespace(char const *s)
{
	char		**array;
	int			count;
	size_t		curr_len;
	char		*curr;
	int			i;

	i = 0;
	if (!s)
		return (NULL);
	count = word_count(s);
	curr = next_word(s);
	curr_len = 0;
	if (!(array = (char **)ft_memalloc(sizeof(char *) * (1 + count))))
		return (NULL);
	while (i < count)
	{
		curr = next_word(&(curr[curr_len]));
		curr_len = word_len(curr);
		if (!(array[i] = (char *)ft_memalloc(sizeof(char) * (1 + curr_len))))
			return (NULL);
		ft_strncpy(array[i], curr, curr_len);
		i++;
	}
	array[i] = NULL;
	return (array);
}
