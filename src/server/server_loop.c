/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 18:53:52 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 12:22:46 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int					accept_client(int *cs, int *sock)
{
	struct sockaddr_in		csin;
	unsigned int			cslen;

	if ((*cs = accept(*sock, (struct sockaddr *)&csin, &cslen)) == -1)
		return (0);
	return (1);
}

static void					s_sigchld(int sig)
{
	if (g_except != 1)
	{
		if (sig == SIGCHLD)
		{
			g_except = 0;
			wait4(0, NULL, 0, NULL);
		}
	}
}

static void					catch_signals(void)
{
	signal(SIGCHLD, s_sigchld);
}

int							server_loop(int sock)
{
	int						cs;
	pid_t					pid;
	char const				*root = get_root();

	g_except = 0;
	catch_signals();
	while (42)
	{
		if (!accept_client(&cs, &sock))
			return (0);
		pid = fork();
		if (pid == -1)
			error("Fork error !\n");
		if (pid == 0)
		{
			close(sock);
			handle_client((char *)root, cs);
			exit(0);
		}
	}
}
