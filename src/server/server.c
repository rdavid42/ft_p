/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 17:26:07 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 11:39:31 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "server.h"
#include "shared.h"

int				main(int ac, char **av)
{
	int						port;
	int						sock;

	if (ac != 2)
		usage(av[0]);
	port = stoi(av[1]);
	sock = create_server(port);
	server_loop(sock);
	close(sock);
	return (1);
}
