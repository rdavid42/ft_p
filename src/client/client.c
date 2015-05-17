
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

inline static void		bufset(char *buf)
{
	size_t		i;

	i = 0;
	while (i < BUFS)
	{
		buf[i] = '\0';
		i++;
	}
}

int				interpret_ls(int *sock, char *cmd)
{
	int				r;
	char			buf[BUFS];
	int const		cmd_size = slen(cmd);

	if (write(*sock, cmd, cmd_size) == -1)
		close(*sock), error(REQ_ERR);
	else
	{
		while (42)
		{
			bufset(buf);
			r = recv(*sock, buf, BUFS - 1, 0);
			if (r == -1)
				close(*sock), error(REC_ERR);
			else if (!r)
				error(CO_CLOSED);
			if (!buf[0])
				break;
			write(1, buf, slen(buf));
		}
		write(1, "SUCCESS\n", 9);
	}
	return (1);
}

int				interpret_cd(int *sock, char *cmd)
{
	(void)sock;
	(void)cmd;
	printf("cd\n");
	return (1);
}

int				interpret_get(int *sock, char *cmd)
{
	int const		cmd_size = slen(cmd);
	char			buf[BUFS];
	int				r;
	int				fd;
	char			**cmd_args;
	int				bytes;
	int				len;

	cmd_args = ssplit(cmd, ' ');
	if (alen(cmd_args) <= 1)
		return (afree(cmd_args), printf(ARG_ERR1), 0);
	if (alen(cmd_args) > 2)
		return (afree(cmd_args), printf(ARG_ERR2), 0);
	if ((fd = open(cmd_args[1], O_RDONLY, 0644)) != -1)
		return (afree(cmd_args), printf(FILE_EXIST), 0);
	if ((fd = open(cmd_args[1], O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
		return (afree(cmd_args), printf(OPEN_ERR), 0);
	if (write(*sock, cmd, cmd_size) == -1)
		afree(cmd_args), close(*sock), error(REQ_ERR);
	else
	{
		bytes = 0;
		while (42)
		{
			bufset(buf);
			r = recv(*sock, buf, BUFS - 1, 0);
			if (r == -1)
				close(*sock), error(REC_ERR);
			else if (!r)
				error(CO_CLOSED);
			if (!buf[0])
				break;
			len = slen(buf);
			bytes += len;
			write(fd, buf, len);
			if (len < BUFS - 1)
				break;
		}
		close(fd);
		if (!bytes)
			printf("ERROR: retrieved empty file!\n");
		else
			printf("SUCCESS: received %d bytes from server\n", bytes);
		afree(cmd_args);
	}
	return (1);
}

int				interpret_put(int *sock, char *cmd)
{
	(void)sock;
	(void)cmd;
	printf("put\n");
	return (1);
}

int				interpret_pwd(int *sock, char *cmd)
{
	(void)sock;
	(void)cmd;
	printf("pwd\n");
	return (1);
}

int				interpret_quit(int *sock, char *cmd)
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
		if (!scmp(cmds[i].name, cmd, cmds[i].len)
			&& (cmd[cmds[i].len] == ' ' || !cmd[cmds[i].len]))
		{
			cmds[i].interpret(&sock, cmd);
			return;
		}
	}
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
		bufset(buf);
		if ((r = read(0, buf, BUFS - 1) == -1))
			return (0);
		cmd = clean_line(buf);
		interpret_command(sock, cmd);
		free(cmd);
		cmd = NULL;
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