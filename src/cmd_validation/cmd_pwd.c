/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:10:03 by asyed             #+#    #+#             */
/*   Updated: 2018/05/03 18:31:03 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int	cmd_pwd(const char *buf)
{
	return (strncmp(buf, "PWD", 3));
}

int	exec_pwd(char *buf, t_clients *client, int fd)
{
	char	buffer[1024];

	printf("Got in here!\n");
	memcpy(buffer, "257 \0", 5);
	if (strlen(client->info.cwd) >= 1018)
	{
		write(fd, "552\r\n", 5);
		return (EXIT_FAILURE);
	}
	strcat(buffer, client->info.cwd);
	strcat(buffer, "\r\n");
	write(fd, buffer, strlen(buffer));
	// printf("wrote buffer \"%s\" vs %s\n", buffer, client->cwd);
	return (EXIT_SUCCESS);
}
