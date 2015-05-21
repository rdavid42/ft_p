/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 17:49:30 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/21 11:12:16 by rdavid           ###   ########.fr       */
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

int				main(int ac, char **av)
{
	int						sock;
	int						port;

	if (ac != 3)
		usage(av[0]);
	port = stoi(av[2]);
	sock = create_client(av[1], port);
	if (!client_loop(sock))
		return (0);
	close(sock);
	return (1);
}
