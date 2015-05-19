/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 18:40:30 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 19:26:45 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include "shared.h"
#include "server.h"

int				ls(char *root, int *cs, char *cmd, int *id)
{
	pid_t					pid;
	pid_t					tpid;

	(void)root;
	pid = fork();
	if (pid == -1)
		error("Fork error !\n");
	g_except = 1;
	if (pid == 0)
	{
		dup2(*cs, 0), dup2(*cs, 1), dup2(*cs, 2);
		execv("/bin/ls", ssplit(cmd, ' '));
	}
	else
	{
		tpid = wait4(pid, NULL, 0, NULL);
		while (tpid != pid)
			tpid = wait4(pid, NULL, 0, NULL);
		(void)!write(*cs, "\0", 1);
		printf("Sent ls results to client %d\n", *id);
	}
	return (1);
}
