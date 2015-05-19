/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lpwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 09:38:43 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 10:23:14 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "shared.h"
#include "client.h"

int				lpwd(int *sock, char *cmd)
{
	pid_t		pid;
	pid_t		tpid;

	(void)sock;
	pid = fork();
	if (pid == -1)
		error(FORK_ERR);
	if (pid == 0)
		execv("/bin/pwd", ssplit(cmd, ' '));
	else
	{
		tpid = wait4(pid, NULL, 0, NULL);
		while (tpid != pid)
			tpid = wait4(pid, NULL, 0, NULL);
	}
	return (1);
}
