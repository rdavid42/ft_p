
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

void			usage(char *s)
{
	printf("Usage: %s <addr> <port>\n", s);
	exit(-1);
}

int				slen(char const *s)
{
	int			i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int				error(char const *msg)
{
	(void)write(2, msg, slen(msg));
	exit(-1);
}

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

int				loop(int sock)
{
	char		buf[1024];
	int			r;

	while (42)
	{
		write(1, "% ", 2);
		r = read(0, buf, 1023);
		if (r == -1)
			return (0);
		buf[r] = '\0';
		if (send(sock, buf, slen(buf), 0) == -1)
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
		}
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