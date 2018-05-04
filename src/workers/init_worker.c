/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_worker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 10:16:48 by asyed             #+#    #+#             */
/*   Updated: 2018/05/03 18:31:24 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_worker.h"
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define MAX(x,y) ((x >= y) ? x : y);

int		init_port(struct sockaddr_in *addr, int *s_fd)
{
	static uint32_t	port = 49152;

	if ((*s_fd = socket(AF_INET, SOCK_STREAM, 6)) == -1)
		return (EXIT_FAILURE);
	addr->sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &(addr->sin_addr.s_addr));
	while (port < 65536)
	{
		addr->sin_port = htons(port);
		port++;
		if (bind(*s_fd, (struct sockaddr *)addr, sizeof(struct sockaddr_in)) == -1)
		{
			if (errno == EADDRINUSE)
				continue ;
		}
		printf("Listening on port %d\n", port - 1);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int		recv_fd(int comm, t_clients *client)
{
	struct msghdr	msg;
	char			buf[CMSG_SPACE(sizeof(int))];
	struct iovec	io;

	io.iov_base = client;
	io.iov_len = sizeof(t_clients);
	msg.msg_iov = &io;
	msg.msg_iovlen = 1;
	msg.msg_control = buf;
	msg.msg_controllen = sizeof(buf);
	if (recvmsg(comm, &msg, 0) == -1)
	{
		printf("Error: \"%s\"\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	return (*(int *)CMSG_DATA(CMSG_FIRSTHDR(&msg)));
}

int		init_slave(int comm)
{
	t_clients			client_info;
	int					c_fd;		
	char				buf[1025];
	int					res;

	if ((c_fd = recv_fd(comm, &client_info)) == EXIT_FAILURE)
		printf("Error: %s\n", strerror(errno));
	printf("Client FD = %d cwd = %s\n", c_fd, client_info.info.cwd);
	while ((res = read(c_fd, buf, 1024)) > 0)
	{
		buf[res] = '\0';
		printf("Buf - \"%s\"\n", buf);
	}
	return (EXIT_FAILURE);
}

int		init_dworker(int i, fd_set *p_fds, int *max)
{
	int					comm[2];
	struct sockaddr_in	addr;	
	pid_t				pid;
	int					s_fd;	

	if (init_port(&addr, &s_fd) == EXIT_FAILURE ||
		init_ipc(&addr, comm))
	{
		printf("Error: \"%s\"\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (!(g_clients[comm[0]] = init_client()))
	{
		//Close all. Free all.
		return (EXIT_FAILURE);
	}
	g_clients[comm[0]]->worker.comm = comm[1];
	if ((pid = fork()) == -1)
		return (EXIT_FAILURE);
	if (!pid)
		exit(init_slave(comm[1]));
	FD_SET(comm[0], p_fds);
	*max = MAX(comm[0], *max);
	return (EXIT_SUCCESS);
}


int 	init_dataworkers(fd_set *p_fds, int socket_fd)
{
	int				i;
	int				max;
	int				tmp;

	i = 0;
	max = socket_fd;
	// while (i < 30)
	// {
		if (init_dworker(i, p_fds, &max) == -1)
			return (-1);
		max++;
		// if (tmp >= (max - 1))
			// max = tmp + 1;
		// i++;
	// }
	return (max);
}