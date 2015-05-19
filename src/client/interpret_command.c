/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryd <ryd@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 19:05:30 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 07:11:52 by ryd              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "shared.h"
#include "client.h"

void			interpret_command(int sock, char *cmd)
{
	int						i;
	static t_cmd const		cmds[CMDS] = {

	{ 2, "ls", ls },
	{ 2, "cd", cd },
	{ 3, "get", get },
	{ 3, "put", put },
	{ 3, "pwd", pwd },
	{ 4, "quit", quit } };
	i = -1;
	while (++i < CMDS)
	{
		if (!scmp(cmds[i].name, cmd, cmds[i].len)
			&& (cmd[cmds[i].len] == ' ' || !cmd[cmds[i].len]))
		{
			cmds[i].interpret(&sock, cmd);
			return ;
		}
	}
	if (slen(cmd) > 0)
		printf(CMD_NOT_FOUND, cmd);
}
