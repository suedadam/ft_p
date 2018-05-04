/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_username.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:10:03 by asyed             #+#    #+#             */
/*   Updated: 2018/05/01 17:13:31 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int	cmd_username(const char *buf)
{
	int	i;

	i = 0;
	while (buf[i] && buf[i] != ' ')
		i++;
	return (strncmp(buf, "USER", i));
}

int	exec_username(char *buf, t_clients *client, int fd)
{
	char	**words;

	if (!(words = ft_strsplit(buf, ' ')))
		return (EXIT_FAILURE);
	printf("Username = \"%s\"\n", words[1]);
	if (!ft_strcmp(words[1], "anonymous\r\n"))
	{
		write(fd, "331 Anonymous access is allowed, send identity (e-mail name) as password\r\n", strlen("331 Anonymous access is allowed, send identity (e-mail name) as password\r\n"));
	}
	else
	{
		write(fd, "430\r\n", 5);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
	// int	i;

	// i = 0;
	// while (buf[i] && buf[i] != ' ')
	// 	i++;
	// return (strncmp(buf, "USER", i));
}
