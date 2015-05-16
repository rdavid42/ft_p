
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
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
	sin.sin_port = htons(port); // host to network short
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		error("Bind error !\n");
	listen(sock, 42);
	return (sock);
}

void			interpret_ls(int cs, char *cmd)
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
	}
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

	while (42)
	{
		bufset(buf);
		r = recv(cs, buf, BUFS - 1, 0);
		if (r == -1)
			error("Read error !\n");
		else if (!r)
			return (!write(2, "Connection closed !\n", 20));
		buf[r] = '\0';
		if (!scmp(buf, "ls", 2))
			interpret_ls(cs, buf);
/*		printf("%s\n", buf);
		if ((send(cs, buf, slen(buf), 0)) == -1)
		{
			write(2, "Error sending results!\n", 23);
			close(cs);
			return (0);
		}*/
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
	port = atoi(av[1]);
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
		close(cs);
	}
	close(sock);
	return (1);
}