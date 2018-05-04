/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 13:46:33 by asyed             #+#    #+#             */
/*   Updated: 2018/05/03 18:28:18 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

t_clients	**g_clients;

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

// int	dworker_finished(int i)
// {
// 	int fds[2];

// 	pipe(fds);
// 	close(fds[1]);

// }

int	handle_clients(int max, fd_set *fds, fd_set *copy, int worker_id)
{
	int		i;
	int		res;
	char	buf[1025];

	i = 0;
	while (i < max)
	{
		// if (g_clients[i]->worker && g_clients[i]->worker.used)
		// 	dworker_finished(i);
		if (FD_ISSET(i, fds))
		{
			// if (g_clients[i].worker)
			// {
				
			// }
			if ((res = read(i, buf, 1024)) == -1 || !res)
			{
				printf("[%d] Deleted FD. buf = \"%s\"\n", worker_id, buf);
				close(i);
				FD_CLR(i, copy);
			}
			else if (!strcmp(buf, "peace"))
			{
				printf("[%d] As you wish. -> %d\n", worker_id, i);
				close(i);
				FD_CLR(i, copy);
			}
			else
			{
				buf[res] = '\0';
				res = 0;
				while (g_commands[res].cmp)
				{
					if (g_commands[res].cmp(buf) == EXIT_SUCCESS)
					{
						g_commands[res].exec(buf, g_clients[i], i);
						break ;
					}
					res++;
				}
				if (!g_commands[res].cmp)
					cmd_unknown(i);
					// printf("Unknown command! %s\n", buf);
				printf("[%d] (%d) Data = \"%s\"\n", worker_id, i, buf);
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

t_clients	*init_client(void)
{
	static char	*cwd = NULL;
	t_clients	*new;

	if (!cwd)
	{
		if (!(cwd = getwd(NULL)))
			return (NULL);
	}
	if (!(new = ft_memalloc(sizeof(t_clients))))
		return (NULL);
	ft_strncpy(new->info.cwd, cwd, 1023);
	return (new);
}

int	send_fd(int c_fd, int worker_fd, t_clients *client)
{
	struct msghdr	msg;
	struct cmsghdr	*cmsg;
	char 			buf[CMSG_SPACE(sizeof(int))];
	struct iovec	io;

	ft_bzero(buf, sizeof(buf));
	io.iov_base = client;
	io.iov_len = sizeof(t_clients);
	msg.msg_iov = &io;
	msg.msg_iovlen = 1;
	msg.msg_control = buf;
	msg.msg_controllen = sizeof(buf);
	cmsg = CMSG_FIRSTHDR(&msg);
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	cmsg->cmsg_len = CMSG_LEN(sizeof(int));
	memcpy(CMSG_DATA(cmsg), &c_fd, sizeof(int));
	return (sendmsg(worker_fd, &msg, 0));
}

int	init_control(int socket_fd, int worker_id)
{
	int		max;
	fd_set	p_fds;
	fd_set	copy;
	int		new;
	t_queue	*workers;

	if (!(g_clients = ft_memalloc(__DARWIN_FD_SETSIZE * sizeof(void *))))
		return (EXIT_FAILURE);
	FD_ZERO(&p_fds);
	FD_SET(socket_fd, &p_fds);
	max = socket_fd;
	max = init_dataworkers(&p_fds, socket_fd);
	FD_ZERO(&copy);
	FD_COPY(&p_fds, &copy);
	while (select(max, &p_fds, NULL, NULL, NULL) != -1)
	{
		if (FD_ISSET(socket_fd, &p_fds))
		{
			if ((new = accept(socket_fd, NULL, NULL)) == -1)
				printf("Error accepting! %s\n", strerror(errno));
			else
			{
				if (send_fd(new, max - 1, init_client()) == -1) //For testing. max - 1 is not a safe way to do this lol.
				{
					printf("Error: %s\n", strerror(errno));
					return (EXIT_FAILURE);
				}
				printf("sent!\n");
				close(new);				
			}

		}
		else if (FD_ISSET(max - 1, &p_fds))
		{
			printf("From worker!? :O\n");
			char buf[1024];
			read(max - 1, buf, 1023);
			printf("buf  - \"%s\"\n", buf);
		}
		else
			printf("wtf? O.o\n");
		FD_ZERO(&p_fds);
		FD_COPY(&copy, &p_fds);
		// if (FD_ISSET(socket_fd, &p_fds))
		// {
		// 	if ((new = accept(socket_fd, NULL, NULL)) != -1 &&
		// 		(g_clients[new] = init_client(new)))
		// 	{
		// 		FD_SET(new, &copy);
		// 		if (new > (pid - 1))
		// 			pid = new + 1;
		// 		printf("[%d] New connection!\n", worker_id);
		// 		write(new, "220 Service ready \r\n", strlen("220 Service ready \r\n"));
		// 	}
		// 	else
		// 	{
		// 		close(new);
		// 		printf("Error accepting %s\n", strerror(errno));
		// 	}
		// }
		// FD_CLR(socket_fd, &p_fds);
		// handle_clients(pid, &p_fds, &copy, worker_id);
		// FD_ZERO(&p_fds);
		// FD_COPY(&copy, &p_fds);
	}
	printf("Select error: \"%s\"\n", strerror(errno));
	return (EXIT_SUCCESS);
}
