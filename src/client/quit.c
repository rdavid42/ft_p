/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 19:05:06 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 13:15:42 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include "client.h"
#include "shared.h"

int				quit(int *sock, char *cmd)
{
	char		r;

	(void)cmd;
	if (write(*sock, cmd, slen(cmd)) == -1)
		close(*sock), error(REQ_ERR);
	r = 0;
	if (recv(*sock, (void *)&r, sizeof(char), 0) == -1)
		close(*sock), error(REQ_ERR);
	if (r == 1)
		(void)!write(1, "SUCCESS: connexion closed! :)\n", 30);
	close(*sock);
	exit(0);
	return (1);
}
