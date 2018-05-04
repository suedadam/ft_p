/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 13:46:33 by asyed             #+#    #+#             */
/*   Updated: 2018/05/04 00:30:56 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

t_clients	**g_clients;

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

int to_worker(int socket, t_pqueue *workers)
{
	int	new;
	int *worker;

	if ((new = accept(socket, NULL, NULL)) == -1)
	{
		printf("Failed to accept: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	worker = ft_depqueue(workers);
	if (send_fd(new, *worker, init_client()) == EXIT_FAILURE)
	{
		printf("Failed to send: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	close(new);
	free(worker);
	return (EXIT_SUCCESS);
}

int	from_worker(int fd, int *max, t_pqueue *workers, fd_set *copy)
{
	int			new;
	t_clients	client_info;

	if ((new = recv_fd(fd, &client_info)) == EXIT_FAILURE)
	{
		printf("Failed to receive FD: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (!(g_clients[new] = ft_memalloc(sizeof(t_clients))))
	{
		printf("Failed to ft_memalloc(%s)\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	ft_memcpy(g_clients[new], &client_info, sizeof(t_clients));
	FD_SET(new, copy);
	if (new > *max - 1)
		*max = new + 1;
	ft_enpqueue(workers, &fd, sizeof(int), num_larger);
	return (EXIT_SUCCESS);
}

int handle_control(fd_set *fds, int *max, int socket_fd, t_pqueue *workers, fd_set *copy)
{
	int	i;

	if (FD_ISSET(socket_fd, fds))
	{
		to_worker(socket_fd, workers);
		FD_CLR(socket_fd, fds);
	}
	i = 0;
	while (i < *max)
	{
		if (FD_ISSET(i, fds))
		{
			if (g_clients[i]->worker.comm)
				from_worker(i, max, workers, copy);
			else
				printf("Client responded!\n");
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_control(int socket_fd, int worker_id)
{
	int			max;
	fd_set		p_fds;
	fd_set		copy;
	t_pqueue	*workers;

	if (!(g_clients = ft_memalloc(__DARWIN_FD_SETSIZE * sizeof(void *))))
		return (EXIT_FAILURE);
	if (!(workers = init_pqueue()))
		return (EXIT_FAILURE);
	FD_ZERO(&p_fds);
	FD_SET(socket_fd, &p_fds);
	init_dataworkers(&p_fds, socket_fd, workers);
	max = *(int *)peek_pqueue(workers) + 1;
	FD_ZERO(&copy);
	FD_COPY(&p_fds, &copy);
	while (select(max, &p_fds, NULL, NULL, NULL) != -1)
	{
		if (handle_control(&p_fds, &max, socket_fd, workers, &copy) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		FD_ZERO(&p_fds);
		FD_COPY(&copy, &p_fds);
	}
	printf("Select error: \"%s\"\n", strerror(errno));
	return (EXIT_SUCCESS);
}
