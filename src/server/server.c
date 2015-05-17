/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 17:26:07 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 18:16:35 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "server.h"
#include "shared.h"

int				create_server(int port)
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
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		error(BIND_ERR);
	listen(sock, 42);
	return (sock);
}

int				ls(int cs, char *cmd)
{
	pid_t					pid;
	pid_t					tpid;

	pid = fork();
	if (pid == -1)
		error("Fork error !\n");
	if (pid == 0)
	{
		dup2(cs, 0), dup2(cs, 1), dup2(cs, 2);
		execv("/bin/ls", ssplit(cmd, ' '));
	}
	else
	{
		tpid = wait4(pid, NULL, 0, NULL);
		while (tpid != pid)
			tpid = wait4(pid, NULL, 0, NULL);
		write(cs, "\0", 1);
		printf("Sent ls results to client %d\n", cs);
	}
	return (1);
}

int				get(int cs, char *cmd)
{
	char		**cmd_args;
	char		*file;
	int			len;
	int			i;
	int			t;

	cmd_args = ssplit(cmd, ' ');
	if (!(file = read_file(cmd_args[1], &len)))
		return (afree(cmd_args), write(cs, "\0", 1), 0);
	printf("%d bytes\n", len);
	if (send(cs, (void *)&len, sizeof(len), 0) == -1)
		return (afree(cmd_args), 0);
	i = 0;
	while (i < len)
	{
		t = len - i < GET_BUFS ? len - i : GET_BUFS;
		if (send(cs, file + i, t, 0) == -1)
			return (afree(cmd_args), 0);
		i += GET_BUFS;
	}
	printf("Sent %d bytes to client %d\n", len, cs);
	afree(cmd_args);
	return (1);
}

inline static void		bufset(char *buf)
{
	int			i;

	i = -1;
	while (++i < BUFS)
		buf[i] = '\0';
}

int				handle_client(int cs)
{
	int						r;
	char					buf[BUFS];

	printf("Connexion to client %d established!\n", cs);
	while (42)
	{
		bufset(buf);
		r = recv(cs, buf, BUFS - 1, 0);
		if (r == -1)
			close(cs), error("Read error !\n");
		else if (!r)
			return (close(cs), printf("Connexion to client %d closed!\n", cs));
		buf[r] = '\0';
		if (!scmp(buf, "ls", 2))
			ls(cs, buf);
		else if (!scmp(buf, "get", 3))
			get(cs, buf);
	}
	close(cs);
	return (1);
}

int				main(int ac, char **av)
{
	struct sockaddr_in		csin;
	unsigned int			cslen;
	int						sock;
	int						port;
	int						cs;
	pid_t					pid;

	if (ac != 2)
		usage(av[0]);
	port = stoi(av[1]);
	sock = create_server(port);
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
			handle_client(cs);
			exit(0);
		}
	}
	close(sock);
	return (1);
}