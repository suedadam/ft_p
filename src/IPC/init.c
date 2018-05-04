/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:10:36 by asyed             #+#    #+#             */
/*   Updated: 2018/05/04 00:01:15 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

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

/*
** Fix the weird 5 bytes!
*/

int		recv_fd(int comm, t_clients *client)
{
	struct msghdr	msg;
	char			buf[CMSG_SPACE(sizeof(int))];
	struct iovec	io;
	int ret;

	io.iov_base = client;
	io.iov_len = sizeof(t_clients);
	msg.msg_iov = &io;
	msg.msg_iovlen = 1;
	msg.msg_control = buf;
	msg.msg_controllen = sizeof(buf);
	while ((ret = recvmsg(comm, &msg, 0)) != 1028)
	{
		io.iov_base = client;
		io.iov_len = sizeof(t_clients);
		msg.msg_iov = &io;
		msg.msg_iovlen = 1;
		msg.msg_control = buf;
		msg.msg_controllen = sizeof(buf);
		printf("Read %d bytes \"%s\"\n", ret, (char *)&msg);
	}
	if (ret == -1)
	{
		printf("IT WAS -1! %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	printf("Received: %p %d\n", CMSG_FIRSTHDR(&msg), ret);
	return (*(int *)CMSG_DATA(CMSG_FIRSTHDR(&msg)));
}

int	init_ipc(struct sockaddr_in *addr, int *fds)
{
	int					unix_s;
	struct sockaddr_un	unix_addr;

	if ((unix_s = socket(PF_LOCAL, SOCK_STREAM, 0)) == -1 ||
		(fds[1] = socket(PF_LOCAL, SOCK_STREAM, 0)) == -1)
		return (EXIT_FAILURE);
	unix_addr.sun_family = PF_LOCAL;
	unix_addr.sun_len = sizeof(unix_addr.sun_path) - 1;
	ft_strcpy(unix_addr.sun_path, "/tmp/ftp");
	ft_strncat(unix_addr.sun_path, ft_itoa(addr->sin_addr.s_addr), unix_addr.sun_len - 8);
	unlink(unix_addr.sun_path);
	if (bind(unix_s, (struct sockaddr *)&unix_addr, sizeof(struct sockaddr_un)) == -1)
		return (EXIT_FAILURE);
	if (listen(unix_s, 1) == -1)
		return (EXIT_FAILURE);
	if (connect(fds[1], (struct sockaddr *)&unix_addr, sizeof(struct sockaddr_un)) == -1)
		return (EXIT_FAILURE);
	if ((fds[0] = accept(unix_s, NULL, 0)) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
