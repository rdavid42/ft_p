/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 18:50:07 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/21 13:48:54 by rdavid           ###   ########.fr       */
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

int							interpret_command(char *root, int *cs,
											char *cmd, int *id)
{
	int						i;
	static t_cmd const		cmds[CMDS] = {

	{ 2, "ls", ls }, { 2, "cd", cd }, { 3, "get", get },
	{ 3, "put", put }, { 3, "pwd", pwd }, { 4, "quit", quit } };
	i = -1;
	while (++i < CMDS)
	{
		if (!scmp(cmds[i].name, cmd, cmds[i].len)
			&& (cmd[cmds[i].len] == ' ' || !cmd[cmds[i].len]))
		{
			cmds[i].interpret(root, cs, cmd, id);
			return (1);
		}
	}
	return (1);
}

int							handle_client(char *root, int cs, int id)
{
	int						r;
	char					buf[BUFS];

	printf("Connexion to client %d established!\n", id);
	while (42)
	{
		bufset(buf);
		r = recv(cs, buf, BUFS - 1, 0);
		if (r == -1)
			close(cs), error("Read error !\n");
		else if (!r)
			return (close(cs), printf("Connexion to client %d closed!\n", id));
		buf[r] = '\0';
		interpret_command(root, &cs, buf, &id);
	}
	close(cs);
	return (1);
}
