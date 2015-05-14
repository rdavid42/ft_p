
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
	dprintf(2, "Usage: %s <msg> <addr> <port>\n", s);
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
	{
		printf("Connect Error !\n");
		exit(-1);
	}
	return (sock);
}

int				main(int ac, char **av)
{
	int						sock;
	int						port;

	if (ac != 4)
		usage(av[0]);
	port = atoi(av[3]);
	sock = create_client(av[2], port);
	if (write(sock, av[1], strlen(av[1])) == -1)
		return (0);
	close(sock);
	return (1);
}