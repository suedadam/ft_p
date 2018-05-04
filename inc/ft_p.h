/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 13:33:18 by asyed             #+#    #+#             */
/*   Updated: 2018/05/03 18:28:23 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>
#include "libft.h"

typedef struct	s_dataworker
{
	int			comm; //IPC.
}				t_dataworker;

typedef struct	s_clientinfo
{
	char	cwd[1024];
}				t_clientinfo;

/*
** FD = worker FD.
*/

typedef struct	s_clients
{
	t_clientinfo	info;
	t_dataworker	worker;
}				t_clients;

typedef struct	s_commands
{
	int	(*cmp)(const char *buf);
	int	(*exec)(char *buf, t_clients *client, int fd);
}				t_commands;

int			cmd_username(const char *buf);
int			exec_username(char *buf, t_clients *client, int fd);
int			cmd_password(const char *buf);
int			exec_password(char *buf, t_clients *client, int fd);
int			cmd_syst(const char *buf);
int			exec_syst(char *buf, t_clients *client, int fd);
int			cmd_feat(const char *buf);
int			exec_feat(char *buf, t_clients *client, int fd);
int			cmd_pwd(const char *buf);
int			exec_pwd(char *buf, t_clients *client, int fd);
int			cmd_type(const char *buf);
int			exec_type(char *buf, t_clients *client, int fd);
int			init_control(int socket_fd, int worker_id);
int 		init_dataworkers(fd_set *p_fds, int socket_fd);
t_clients	*init_client(void);
int			init_ipc(struct sockaddr_in *addr, int *fds);

extern t_clients **g_clients;

#endif