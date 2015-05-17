/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 18:50:07 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 20:39:26 by rdavid           ###   ########.fr       */
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

int							interpret_command(char *root, int *cs, char *cmd)
{
	if (!scmp(cmd, "ls", 2))
		ls(cs, cmd);
	else if (!scmp(cmd, "get", 3))
		get(cs, cmd);
	else if (!scmp(cmd, "cd", 2))
		cd(root, cs, cmd);
	return (1);
}

int							handle_client(char *root, int cs)
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
		interpret_command(root, &cs, buf);
	}
	close(cs);
	return (1);
}
