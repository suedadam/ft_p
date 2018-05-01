/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 13:32:43 by asyed             #+#    #+#             */
/*   Updated: 2018/04/30 15:08:01 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <string.h>
#include <errno.h>

static inline int	init_socket(void)
{
	int					s_fd;
	struct sockaddr_in	addr;

	if ((s_fd = socket(AF_INET, SOCK_STREAM, 6)) == -1)
		return (-1);
	// bzero(&addr, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1337);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1)
		return (-1);
	if (listen(s_fd, 1024) == -1)
		return (-1);
	return (s_fd);
}

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
	int	socket_fd;

	if ((socket_fd = init_socket()) == -1)
	{
		printf("Error: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	printf("Initialzied socket correctly!\n");
	if (init_worker(socket_fd) == EXIT_FAILURE)
	{
		printf("Error: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	while(1);
	return (EXIT_SUCCESS);
}