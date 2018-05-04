/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:10:36 by asyed             #+#    #+#             */
/*   Updated: 2018/05/03 17:32:47 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

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
