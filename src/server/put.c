/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 13:27:51 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/18 18:30:52 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/socket.h>
#include "server.h"
#include "shared.h"

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

static int			write_streaming_packets(int *cs, int fd,
											char **cmd_args, int *len)
{
	int				i;
	char			c[GET_BUFS];
	int				r;

	i = 0;
	while (i < *len)
	{
		bufset(c, GET_BUFS);
		r = recv(*cs, c, GET_BUFS, 0);
		if (r == -1)
			afree(cmd_args), close(fd), close(*cs), error(REC_ERR);
		else if (!r)
			afree(cmd_args), close(fd), close(*cs), error(CO_CLOSED);
		(void)!write(fd, c, *len - i < GET_BUFS ? *len - i : GET_BUFS);
		i += GET_BUFS;
	}
	printf("Received %d bytes from client %d\n", *len, *cs);
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

static int				check_errors(int *cs, char **cmd_args)
{
	int					ret;
	int					fd;

	if ((fd = open(cmd_args[1], O_RDONLY, 0644)) != -1)
	{
		afree(cmd_args);
		ret = -1;
		send(*cs, (void *)&ret, sizeof(uint32_t), 0);
		return (0);
	}
	close(fd);
	return (1);
}

int						put(int *cs, char *cmd)
{
	int					fd;
	char				**cmd_args;
	int					len;
	int					ret;

	cmd_args = ssplit(cmd, ' ');
	if (!check_errors(cs, cmd_args))
		return (0);
	ret = 0, send(*cs, (void *)&ret, sizeof(uint32_t), 0);
	if (!receive_file_header(cs, cmd_args, &len))
		return (afree(cmd_args), 0);
	if ((fd = open(cmd_args[1], O_RDWR | O_CREAT, 0644)) == -1)
		return (afree(cmd_args), err_msg(OPEN_ERR), 0);
	write_streaming_packets(cs, fd, cmd_args, &len);
	close(fd);
	afree(cmd_args);
	if (ret = 1, send(*cs, (void *)&ret, sizeof(uint32_t), 0) == -1)
		return (0);
	return (1);
}
