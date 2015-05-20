/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 18:48:13 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/20 14:24:27 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "server.h"
#include "shared.h"

int				create_server(int port)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;
	int					sock;
	int					reuse;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	reuse = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
		error("Setsockopt error!\n");
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		error(BIND_ERR);
	listen(sock, 42);
	return (sock);
}
