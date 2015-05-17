/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 18:40:58 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 20:08:23 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include "shared.h"
#include "server.h"

int				get(int *cs, char *cmd)
{
	char		**cmd_args;
	char		*file;
	int			len;
	int			i;
	int			t;

	cmd_args = ssplit(cmd, ' ');
	if (!(file = read_file(cmd_args[1], &len)))
		len = -1;
	if (send(*cs, (void *)&len, sizeof(len), 0) == -1)
		return (afree(cmd_args), 0);
	if (len >= 0)
	{
		i = 0;
		while (i < len)
		{
			t = len - i < GET_BUFS ? len - i : GET_BUFS;
			if (send(*cs, file + i, t, 0) == -1)
				return (afree(cmd_args), 0);
			i += GET_BUFS;
		}
		printf("Sent %d bytes to client %d\n", len, *cs);
	}
	afree(cmd_args);
	return (1);
}
