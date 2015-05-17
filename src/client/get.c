/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 17:57:22 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 18:16:22 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
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

static int			check_errors(char **cmd_args, int *fd)
{
	if (alen(cmd_args) <= 1)
		return (afree(cmd_args), printf(ARG_ERR1), 0);
	if (alen(cmd_args) > 2)
		return (afree(cmd_args), printf(ARG_ERR2), 0);
	if ((*fd = open(cmd_args[1], O_RDONLY, 0644)) != -1)
		return (afree(cmd_args), printf(FILE_EXIST), 0);
	if ((*fd = open(cmd_args[1], O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
		return (afree(cmd_args), printf(OPEN_ERR), 0);
	return (1);
}

int					get(int *sock, char *cmd)
{
	int const		cmd_size = slen(cmd);
	int				r;
	int				fd;
	char			**cmd_args;
	int				len;
	int				i;
	char			c[GET_BUFS];

	cmd_args = ssplit(cmd, ' ');
	if (!check_errors(cmd_args, &fd))
		return (0);
	if (write(*sock, cmd, cmd_size) == -1)
		afree(cmd_args), close(fd), close(*sock), error(REQ_ERR);
	else
	{
		r = recv(*sock, (void *)&len, sizeof(len), 0);
		if (r == -1)
			afree(cmd_args), close(fd), close(*sock), error(REC_ERR);
		else if (!r)
			afree(cmd_args), close(fd), close(*sock), error(CO_CLOSED);
		i = 0;
		while (i < len)
		{
			bufset(c, GET_BUFS);
			r = recv(*sock, c, GET_BUFS, 0);
			if (r == -1)
				afree(cmd_args), close(fd), close(*sock), error(REC_ERR);
			else if (!r)
				afree(cmd_args), close(fd), close(*sock), error(CO_CLOSED);
			write(fd, c, len - i < GET_BUFS ? len - i : GET_BUFS);
			i += GET_BUFS;
		}
		close(fd);
		if (!len)
			printf("ERROR: retrieved empty file!\n");
		else
			printf("SUCCESS: received %d bytes from server\n", len);
		afree(cmd_args);
	}
	return (1);
}
