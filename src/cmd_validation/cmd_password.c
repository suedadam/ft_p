/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_password.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:10:03 by asyed             #+#    #+#             */
/*   Updated: 2018/05/01 17:18:23 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int	cmd_password(const char *buf)
{
	int	i;

	i = 0;
	while (buf[i] && buf[i] != ' ')
		i++;
	return (strncmp(buf, "PASS", i));
}

int	exec_password(char *buf, t_clients *client, int fd)
{
	char	**words;

	if (!(words = ft_strsplit(buf, ' ')))
		return (EXIT_FAILURE);
	printf("Password = %s\n", words[1]);
	write(fd, "230 User logged in!\r\n", strlen("230 User logged in!\r\n"));
	return (EXIT_SUCCESS);
}
