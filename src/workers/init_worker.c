/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_worker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 10:16:48 by asyed             #+#    #+#             */
/*   Updated: 2018/05/04 00:09:08 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_worker.h"
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define MAX(x,y) ((x >= y) ? x : y);

int	cmd_ignore(char *buf, t_clients *client, int fd)
{
	printf("Ignoring command: %s [%d]\n", buf, fd);
	return (EXIT_SUCCESS);
}

int	cmd_unknown(int fd)
{
	printf("Unknown command\n");
	write(fd, "502\r\n", 5);
	return (EXIT_SUCCESS);
}

t_commands	g_commands[] = {
	{&cmd_username, &exec_username},
	{&cmd_password, &exec_password},
	{&cmd_syst, &exec_syst},
	{&cmd_feat, &exec_feat},
	{&cmd_pwd, &exec_pwd},
	{&cmd_type, &exec_type},
	// {&cmd_auth, &cmd_unknown},
	{NULL, NULL},
};

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

int		handle_client(int c_fd, t_clients *client_info)
{
	int		i;
	int		res;
	char	buf[1025];

	while (1)
	{
		if ((res = read(c_fd, buf, 1024)) == -1 || !res)
		{
			close(c_fd);
			return (EXIT_FAILURE);
		}
		buf[res] = '\0';
		i = 0;
		while (g_commands[i].cmp)
		{
			if (g_commands[i].cmp(buf) == EXIT_SUCCESS)
				return (g_commands[i].exec(buf, client_info, c_fd));
			i++;
		}
		if (!g_commands[i].cmp)
		{
			printf("Command - \"%s\"\n", buf);
			return (cmd_unknown(i));
		}
	}
}

int		init_slave(int comm)
{
	t_clients			client_info;
	int					c_fd;

	while (1)
	{
		if ((c_fd = recv_fd(comm, &client_info)) == EXIT_FAILURE)
		{
			printf("Error: %s\n", strerror(errno));
			continue ;
		}
		write(c_fd, "220 Service ready \r\n", strlen("220 Service ready \r\n"));
		handle_client(c_fd, &client_info);
		printf("sending_fd\n");
		int size;
		if ((size = send_fd(c_fd, comm, &client_info)) != EXIT_FAILURE)
			printf("Sent okay!! %d\n", size);
		printf("sent fd %d\n", c_fd);
		close(c_fd);
		ft_bzero(&client_info, sizeof(t_clients)); //Reset it!
	}
	return (EXIT_FAILURE);
}

int		init_dworker(int i, fd_set *p_fds, t_pqueue *workers)
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
	ft_enpqueue(workers, &(comm[0]), sizeof(int), &num_larger);
	return (EXIT_SUCCESS);
}


int 	init_dataworkers(fd_set *p_fds, int socket_fd, t_pqueue *workers)
{
	int				i;
	int				tmp;

	i = 0;
	// while (i < 30)
	// {
		if (init_dworker(i, p_fds, workers) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		// if (tmp >= (max - 1))
			// max = tmp + 1;
		// i++;
	// }
	return (EXIT_SUCCESS);
}