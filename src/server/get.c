/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 18:40:58 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 16:18:23 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include "shared.h"
#include "server.h"

int				get(char *root, int *cs, char *cmd, int *id)
{
	char		**cmd_args;
	char		*file;
	int			len;
	int			i;
	int			t;

	(void)root, cmd_args = ssplit(cmd, ' ');
	if (!(file = read_file(cmd_args[1], &len)))
		len = -1;
	if (send(*cs, (void *)&len, sizeof(uint32_t), 0) == -1)
		return (afree(cmd_args), 0);
	if (len >= 0)
	{
		i = 0;
		while (i < len)
		{
			t = len - i < GET_BUFS ? len - i : GET_BUFS;
			if (send(*cs, file + i, t, 0) == -1)
				return (free(file), afree(cmd_args), 0);
			i += GET_BUFS;
		}
		free(file), printf("Sent %d bytes to client %d\n", len, *id);
	}
	afree(cmd_args);
	return (1);
}
