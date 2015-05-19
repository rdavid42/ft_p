/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 17:57:22 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 20:49:43 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include "shared.h"
#include "client.h"

inline static void	bufset(char *buf, size_t bufs)
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
		return (afree(cmd_args), err_msg(ARG_ERR1), 0);
	if (alen(cmd_args) > 2)
		return (afree(cmd_args), err_msg(ARG_ERR2), 0);
	if ((*fd = open(cmd_args[1], O_RDONLY, 0644)) != -1)
		return (afree(cmd_args), err_msg(FILE_EXIST), 0);
	return (1);
}

static int			write_streaming_packets(int *sock, int fd,
											char **cmd_args, int *len)
{
	int				i;
	char			c[GET_BUFS];
	int				r;
	int				t;

	i = 0;
	while (i < *len)
	{
		t = *len - i < GET_BUFS ? *len - i : GET_BUFS;
		bufset(c, GET_BUFS);
		while (r = 0, r != t)
		{
			r = recv(*sock, c, t, 0);
			if (r == -1)
				afree(cmd_args), close(fd), close(*sock), error(REC_ERR);
			else if (!r)
				afree(cmd_args), close(fd), close(*sock), error(CO_CLOSED);
			if (r != t)
				printf("Received %d/%d bytes from packet %d\n", r, t, i / GET_BUFS);
			(void)!write(fd, c, r);
			t -= r;
			// if (!t)
				// printf("Received all bytes from packet %d\n", i / GET_BUFS);
		}
		i += GET_BUFS;
	}
	return (1);
}

static int			receive_file_header(int *sock, char **cmd_args, int *len)
{
	int				r;

	r = recv(*sock, (void *)len, sizeof(uint32_t), 0);
	if (r == -1)
		afree(cmd_args), close(*sock), error(REC_ERR);
	else if (!r)
		afree(cmd_args), close(*sock), error(CO_CLOSED);
	if (*len == -1)
		return (err_msg(FILE_NOT_FOUND), 0);
	if (*len == -2)
		return (err_msg(PERM_DENIED), 0);
	return (1);
}

int					get(int *sock, char *cmd)
{
	int				fd;
	char			**cmd_args;
	int				len;

	cmd_args = ssplit(cmd, ' ');
	if (!check_errors(cmd_args, &fd))
		return (0);
	if (write(*sock, cmd, slen(cmd)) == -1)
		afree(cmd_args), close(fd), close(*sock), error(REQ_ERR);
	else
	{
		if (!receive_file_header(sock, cmd_args, &len))
			return (afree(cmd_args), 0);
		if ((fd = open(cmd_args[1], O_RDWR | O_CREAT, 0644)) == -1)
			return (afree(cmd_args), err_msg(OPEN_ERR), 0);
		write_streaming_packets(sock, fd, cmd_args, &len);
		close(fd);
		printf("SUCCESS: received %d bytes from server\n", len);
		afree(cmd_args);
	}
	return (1);
}
