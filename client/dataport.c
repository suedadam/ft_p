/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:39:09 by asyed             #+#    #+#             */
/*   Updated: 2018/05/02 13:28:49 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int	main(int argc, char *argv[])
{
	int					s_fd;
	struct sockaddr_in	addr;
	char				buf[1025];
	int					res;

	if ((s_fd = socket(AF_INET, SOCK_STREAM, 6)) == -1)
	{
		printf("Error: \"%s\"\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1338);
	inet_pton(AF_INET, "e1z3r8p20.42.us.org", &(addr.sin_addr.s_addr));
	if (connect(s_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1)
	{
		printf("Error: \"%s\"\n", strerror(errno));
		return (EXIT_FAILURE);	
	}
	while ((res = read(STDIN_FILENO, buf, 1024)) > 0)
	{
		buf[res - 1] = '\r';
		buf[res] = '\n';
		// strcpy(buf, "\r\n\0");
		if ((res = write(s_fd, buf, res - 1)) == -1)
			break ;
	}
	// write(s_fd, "Penis\n", strlen("Penis\n"));
	if (!res || res == -1)
	{
		printf("Error! res = %d errno = %s\n", res, strerror(errno));
	}
	close(s_fd);
}