/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 13:46:33 by asyed             #+#    #+#             */
/*   Updated: 2018/04/30 15:33:13 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <string.h>
#include <errno.h>

int	handle_clients(int max, fd_set *fds, fd_set *copy)
{
	int		i;
	int		res;
	char	buf[1025];

	i = 0;
	while (i < max)
	{
		if (FD_ISSET(i, fds))
		{
			if ((res = read(i, buf, 1024)) == -1 || !res)
			{
				printf("Deleted FD. buf = \"%s\"\n", buf);
				close(i);
				FD_CLR(i, copy);
			}
			else if (!strcmp(buf, "peace"))
			{
				printf("As you wish.\n");
				close(i);
				FD_CLR(i, copy);
			}
			else
			{
				buf[res] = '\0';
				printf("(%d) Data = \"%s\"\n", i, buf);
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_worker(int socket_fd)
{
	pid_t	pid;
	fd_set	p_fds;
	fd_set	copy;
	int		new;

	if ((pid = fork()) == -1)
		return (EXIT_FAILURE);
	if (!pid)
	{
		FD_ZERO(&p_fds);
		FD_SET(socket_fd, &p_fds);
		FD_ZERO(&copy);
		FD_COPY(&p_fds, &copy);
		pid = socket_fd + 1; //Change use to be the MAX FD.
		while (select(pid, &p_fds, NULL, NULL, NULL) != -1)
		{
			if (FD_ISSET(socket_fd, &p_fds))
			{
				if ((new = accept(socket_fd, NULL, NULL)) != -1)
				{
					FD_SET(new, &copy);
					if (new > (pid - 1))
						pid = new + 1;
					printf("New connection!\n");
				}
				else
					printf("Error accepting %s\n", strerror(errno));
			}
			FD_CLR(socket_fd, &p_fds);
			handle_clients(pid, &p_fds, &copy);
			FD_ZERO(&p_fds);
			FD_COPY(&copy, &p_fds);
		}
		printf("Select error: \"%s\"\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
