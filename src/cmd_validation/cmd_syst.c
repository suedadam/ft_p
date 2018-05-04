/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_syst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:10:03 by asyed             #+#    #+#             */
/*   Updated: 2018/05/01 17:25:34 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int	cmd_syst(const char *buf)
{
	// int	i;

	// i = 0;
	// while (buf[i] && buf[i] != ' ')
	// 	i++;
	return (strncmp(buf, "SYST", 4));
}

int	exec_syst(char *buf, t_clients *client, int fd)
{
	// char	**words;

	// if (!(words = ft_strsplit(buf, ' ')))
	// 	return (EXIT_FAILURE);
	// printf("Password = %s\n", words[1]);
	// write(fd, "230 User logged in!\r\n", strlen("230 User logged in!\r\n"));
	write(fd, "215 MACOS Adam's Server\r\n", strlen("215 MACOS Adam's Server\r\n"));
	return (EXIT_SUCCESS);
}
