
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
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
	sin.sin_port = htons(port); // host to network short
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		error("Connect error !\n");
	return (sock);
}

void			interpret_ls(int *sock)
{
	printf("ls\n");
}

void			interpret_cd(int *sock)
{
	printf("cd\n");
}

void			interpret_get(int *sock)
{
	printf("get\n");
}

void			interpret_put(int *sock)
{
	printf("put\n");
}

void			interpret_pwd(int *sock)
{
	printf("pwd\n");
}

void			interpret_quit(int *sock)
{
	exit(0);
}

void			interpret_command(int sock, char *cmd)
{
	int						i;
	static t_cmd const		cmds[CMDS] =
	{
		{ 2, "ls", interpret_ls },
		{ 2, "cd", interpret_cd },
		{ 3, "get", interpret_get },
		{ 3, "put", interpret_put },
		{ 3, "pwd", interpret_pwd },
		{ 4, "quit", interpret_quit }
	};

	i = -1;
	while (++i < CMDS)
	{
		if (!scmp(cmds[i].name, cmd, cmds[i].len))
		{
			cmds[i].func(&sock);
			break;
		}
	}
}

void			bufset(char *buf, int const size)
{
	int			i;

	i = -1;
	while (++i < size)
		buf[i] = '\0';
}

int				loop(int sock)
{
	char		*cmd;
	char		buf[1024];
	int			r;

	while (42)
	{
		if (write(1, "% ", 2) == -1)
			return (0);
		bufset(buf, 1024);
		if ((r = read(0, buf, 1024) == -1))
			return (0);
		cmd = clean_line(buf);
		interpret_command(sock, cmd);
		free(cmd);
		/*if (send(sock, buf, slen(buf), 0) == -1)
		{
			close(sock);
			error("Failed to send message !\n");
		}
		else
		{
			printf("Message being sent...\n");
			r = recv(sock, buf, 1023, 0);
			if (r == -1)
			{
				printf("Recv error !\n");
				break;
			}
			else if (r == 0)
			{
				printf("Connexion closed !\n");
				break;
			}
		}*/
	}
	return (1);
}

int				main(int ac, char **av)
{
	int						sock;
	int						port;

	if (ac != 3)
		usage(av[0]);
	port = atoi(av[2]);
	sock = create_client(av[1], port);
	if (!loop(sock))
		return (0);
	close(sock);
	return (1);
}