/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:28:23 by asyed             #+#    #+#             */
/*   Updated: 2018/05/01 18:29:31 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int	cmd_type(const char *buf)
{
	return (strncmp(buf, "TYPE", 4));
}

int	exec_type(char *buf, t_clients *client, int fd)
{
	// char	**words;

	// if (!(words = ft_strsplit(buf, ' ')))
		// return (EXIT_FAILURE);
	// printf("Password = %s\n", words[1]);
	write(fd, "200 \r\n", 6);
	// write(fd, "230 User logged in!\r\n", strlen("230 User logged in!\r\n"));
	return (EXIT_SUCCESS);
}
