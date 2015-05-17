/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 18:50:07 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 18:51:43 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include "server.h"
#include "shared.h"

inline static void			bufset(char *buf)
{
	int			i;

	i = -1;
	while (++i < BUFS)
		buf[i] = '\0';
}

int							handle_client(int cs)
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
