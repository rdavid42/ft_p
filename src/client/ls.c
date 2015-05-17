/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 17:51:57 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 19:38:04 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <unistd.h>
#include "shared.h"
#include "client.h"

inline static void		bufset(char *buf, size_t bufs)
{
	size_t		i;

	i = 0;
	while (i < bufs)
	{
		buf[i] = '\0';
		i++;
	}
}

int						ls(int *sock, char *cmd)
{
	int					r;
	char				buf[BUFS];
	int const			cmd_size = slen(cmd);

	if (write(*sock, cmd, cmd_size) == -1)
		close(*sock), error(REQ_ERR);
	else
	{
		while (42)
		{
			bufset(buf, BUFS);
			r = recv(*sock, buf, BUFS - 1, 0);
			if (r == -1)
				close(*sock), error(REC_ERR);
			else if (!r)
				error(CO_CLOSED);
			if (!buf[0])
				break ;
			write(1, buf, slen(buf));
		}
		write(1, "SUCCESS\n", 9);
	}
	return (1);
}
