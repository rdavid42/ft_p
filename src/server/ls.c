/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryd <ryd@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 18:40:30 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 23:50:49 by ryd              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include "shared.h"
#include "server.h"

int				ls(int *cs, char *cmd)
{
	pid_t					pid;
	pid_t					tpid;

	pid = fork();
	if (pid == -1)
		error("Fork error !\n");
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
		printf("Sent ls results to client %d\n", *cs);
	}
	return (1);
}
