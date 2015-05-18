/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 19:04:19 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/18 18:31:36 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include "client.h"
#include "shared.h"

static int		send_packets(int *len, int *sock, char *file, char **cmd_args)
{
	int			i;
	int			t;

	i = 0;
	while (i < *len)
	{
		t = *len - i < GET_BUFS ? *len - i : GET_BUFS;
		if (send(*sock, file + i, t, 0) == -1)
		{
			printf("ERROR: failed to send packet <%d>\n", (i / 512) + 1);
			return (afree(cmd_args), 0);
		}
		i += GET_BUFS;
	}
	return (1);
}

static int		check_errors(char **cmd_args)
{
	if (alen(cmd_args) > 2)
		return (err_msg(ARG_ERR2), 0);
	if (alen(cmd_args) < 2)
		return (err_msg(ARG_ERR1), 0);
	if (open(cmd_args[1], O_RDONLY) == -1)
		return (err_msg(FILE_NOT_FOUND), 0);
	return (1);
}

static int		receive_server_response(int *sock, char **cmd_args)
{
	int			r;
	int			ret;

	ret = 0;
	r = recv(*sock, (void *)&ret, sizeof(uint32_t), 0);
	if (r == -1)
		afree(cmd_args), close(*sock), error(REC_ERR);
	else if (!r)
		afree(cmd_args), close(*sock), error(CO_CLOSED);
	if (ret == -1)
		return (err_msg(FILE_EXIST), 0);
	if (ret == 1)
		return (1);
	return (1);
}

int				put(int *sock, char *cmd)
{
	char		**cmd_args;
	char		*file;
	int			len;

	cmd_args = ssplit(cmd, ' ');
	if (!check_errors(cmd_args))
		return (afree(cmd_args), 0);
	if (write(*sock, cmd, slen(cmd)) == -1)
		afree(cmd_args), close(*sock), error(REQ_ERR);
	if (!receive_server_response(sock, cmd_args))
		return (afree(cmd_args), 0);
	if (!(file = read_file(cmd_args[1], &len)))
		len = -1;
	if (send(*sock, (void *)&len, sizeof(uint32_t), 0) == -1)
		return (afree(cmd_args), 0);
	if (len >= 0)
	{
		if (!send_packets(&len, sock, file, cmd_args))
			return (0);
	}
	if (receive_server_response(sock, cmd_args))
		return (printf("SUCCESS: Sent %d bytes to server!\n", len), 0);
	afree(cmd_args);
	return (1);
}
