/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_feat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:10:03 by asyed             #+#    #+#             */
/*   Updated: 2018/05/01 17:50:56 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int	cmd_feat(const char *buf)
{
	return (strncmp(buf, "FEAT", 4));
}

int	exec_feat(char *buf, t_clients *client, int fd)
{
	write(fd, "211 \r\n", 6);
	return (EXIT_SUCCESS);
}
