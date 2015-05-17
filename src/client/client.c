/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 17:49:30 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 18:18:21 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include "client.h"
#include "shared.h"

int				create_client(char *addr, int port)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;
	int					sock;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if (!scmp(addr, "localhost", 9))
		sin.sin_addr.s_addr = inet_addr(LOCALHOST_ADDR);
	else
		sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		error(CO_FAILED);
	return (sock);
}

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

int				cd(int *sock, char *cmd)
{
	(void)sock;
	(void)cmd;
	return (1);
}

int				put(int *sock, char *cmd)
{
	(void)sock;
	(void)cmd;
	printf("put\n");
	return (1);
}

int				pwd(int *sock, char *cmd)
{
	(void)sock;
	(void)cmd;
	printf("pwd\n");
	return (1);
}

int				quit(int *sock, char *cmd)
{
	(void)cmd;
	close(*sock);
	exit(0);
	return (1);
}

void			interpret_command(int sock, char *cmd)
{
	int						i;
	static t_cmd const		cmds[CMDS] =
	{
		{ 2, "ls", ls },
		{ 2, "cd", cd },
		{ 3, "get", get },
		{ 3, "put", put },
		{ 3, "pwd", pwd },
		{ 4, "quit", quit }
	};

	i = -1;
	while (++i < CMDS)
	{
		if (!scmp(cmds[i].name, cmd, cmds[i].len)
			&& (cmd[cmds[i].len] == ' ' || !cmd[cmds[i].len]))
		{
			cmds[i].interpret(&sock, cmd);
			return;
		}
	}
	if (slen(cmd) > 0)
	printf(CMD_NOT_FOUND, cmd);
}

int				loop(int sock)
{
	char		*cmd;
	char		buf[BUFS];
	int			r;

	while (42)
	{
		if (write(1, "% ", 2) == -1)
			return (0);
		bufset(buf, BUFS);
		if ((r = read(0, buf, BUFS - 1) == -1))
			return (0);
		cmd = clean_line(buf);
		interpret_command(sock, cmd);
		free(cmd);
		cmd = NULL;
	}
	return (1);
}

int				main(int ac, char **av)
{
	int						sock;
	int						port;

	if (ac != 3)
		usage(av[0]);
	port = stoi(av[2]);
	sock = create_client(av[1], port);
	if (!loop(sock))
		return (0);
	close(sock);
	return (1);
}