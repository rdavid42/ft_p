/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 19:03:08 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 19:03:51 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/socket.h>
#include "shared.h"
#include "client.h"

int					check_args(char *cmd)
{
	char			**cmd_args;
	int				len;

	cmd_args = ssplit(cmd, ' ');
	len = alen(cmd_args);
	if (len < 2)
		return (afree(cmd_args), err_msg(ARG_ERR1), 0);
	if (len >= 3)
		return (afree(cmd_args), err_msg(ARG_ERR2), 0);
	return (afree(cmd_args), 1);
}

int					cd(int *sock, char *cmd)
{
	int const		cmd_size = slen(cmd);
	int				r;
	int				ret;

	if (!check_args(cmd))
		return (0);
	if (write(*sock, cmd, cmd_size) == -1)
		return (close(*sock), error(REC_ERR));
	else
	{
		r = recv(*sock, (void *)&ret, sizeof(int), 0);
		if (r == -1)
			close(*sock), error(REC_ERR);
		else if (!r)
			error(CO_CLOSED);
		if (ret == 0)
			return ((void)!write(1, "SUCCESS\n", 9), 1);
		else if (ret == -1)
			return (err_msg(PERM_DENIED), 0);
		else if (ret == -2)
			return (error(CO_CLOSED), 0);
		else if (ret == -3)
			return (err_msg(NO_SUCH_DIR), 0);
	}
	return (1);
}
