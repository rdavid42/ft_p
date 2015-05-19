/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lls.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 09:31:08 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 09:40:28 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "shared.h"
#include "client.h"

int				lls(int *sock, char *cmd)
{
	pid_t		pid;
	pid_t		tpid;

	(void)sock;
	pid = fork();
	if (pid == -1)
		error(FORK_ERR);
	if (pid == 0)
		execv("/bin/ls", ssplit(cmd, ' '));
	else
	{
		tpid = wait4(pid, NULL, 0, NULL);
		while (tpid != pid)
			tpid = wait4(pid, NULL, 0, NULL);
	}
	return (1);
}
