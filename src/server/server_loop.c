/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 18:53:52 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 20:38:20 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"
#include "shared.h"

inline static char			*get_root(void)
{
	char					buf[1024];

	return (getcwd(buf, 1024));
}

int							server_loop(int sock)
{
	int						cs;
	pid_t					pid;
	struct sockaddr_in		csin;
	unsigned int			cslen;
	char					*root;

	root = get_root();
	printf("%s\n", root);
	while (42)
	{
		if ((cs = accept(sock, (struct sockaddr *)&csin, &cslen)) == -1)
			return (0);
		pid = fork();
		if (pid == -1)
			error("Fork error !\n");
		if (pid == 0)
		{
			close(sock);
			handle_client(root, cs);
			exit(0);
		}
	}
}
