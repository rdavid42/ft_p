/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 19:44:06 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/18 13:24:30 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include "shared.h"
#include "server.h"

inline static char		*get_cwd(void)
{
	char				buf[1024];

	return (getcwd(buf, 1024));
}

static void				sc(int *cs, int r)
{
	send(*cs, (void *)&r, sizeof(int), 0);
}

static void				go_dir(int *cs, char *root,
								char const *cur, char *dir)
{
	char				*t[2];

	t[0] = sjoin(cur, "/");
	t[1] = sjoin(t[0], dir);
	free(t[0]);
	if (!chdir(t[1]))
	{
		if (!scmp(root, get_cwd(), slen(root)))
			sc(cs, 0);
		else
		{
			if (chdir(root) == -1)
				free(t[1]), sc(cs, -2), error(ROOT_DIR_DENIED);
			else
				sc(cs, -1);
		}
	}
	else
		sc(cs, -3), err_msg("No such directory !\n");
	free(t[1]);
}

int						cd(char *root, int *cs, char *cmd)
{
	char				**arg;
	char const			*cur = get_cwd();

	arg = ssplit(cmd, ' ');
	if (scmp(root, cur, slen(root)) != 0)
		return (afree(arg), sc(cs, -2), error(CWD_DENIED), 0);
	go_dir(cs, root, cur, arg[1]);
	return (afree(arg), 1);
}
