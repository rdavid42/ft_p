/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 18:40:58 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/20 12:44:52 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include "shared.h"
#include "server.h"

static int		send_packets(int *cs, char *file, int *len, int *id)
{
	int			t;
	int			n;
	int			i;

	i = 0;
	while (i < *len)
	{
		t = *len - i < GET_BUFS ? *len - i : GET_BUFS;
		while (n = 0, n != t)
		{
			if ((n = send(*cs, file + i, t, 0)) == -1)
				return (free(file), 0);
			t -= n;
		}
		i += GET_BUFS;
	}
	free(file), printf("Sent %d bytes to client %d\n", *len, *id);
	return (1);
}

int				get(char *root, int *cs, char *cmd, int *id)
{
	char		**cmd_args;
	char		*file;
	int			len;

	(void)root, cmd_args = ssplit(cmd, ' ');
	if (!(file = read_file(cmd_args[1], &len)))
		len = -1;
	if (send(*cs, (void *)&len, sizeof(uint32_t), 0) == -1)
		return (afree(cmd_args), 0);
	if (len >= 0)
	{
		if (!send_packets(cs, file, &len, id))
			return (0);
	}
	afree(cmd_args);
	return (1);
}
