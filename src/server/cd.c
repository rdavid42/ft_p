/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 19:44:06 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 21:43:23 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/socket.h>
#include "shared.h"

inline static char		*get_cwd(void)
{
	char				buf[1024];

	return (getcwd(buf, 1024));
}

static void				go_up(char *root)
{
	(void)root;
}

int						cd(char *root, int *cs, char *cmd)
{
	char				**cmd_args;
	char const			*curd = get_cwd();
	int					ret;

	cmd_args = ssplit(cmd, ' ');
	if (!scmp(cmd_args[1], "..", 2))
	{
		if (!scmp(root, curd, slen(curd)))
			return (ret = -1, send(*cs, (void *)&ret, sizeof(int), 0), 0);
		else
		{
			go_up(root);
			return (ret = 0, send(*cs, (void *)&ret, sizeof(int), 0), 1);
		}
	}
	else if (!scmp(cmd_args[1], "/", 1))
	{
		if (!chdir(root))
			return (ret = 0, send(*cs, (void *)&ret, sizeof(int), 0), 1);
		else
			return (ret = -1, send(*cs, (void *)&ret, sizeof(int), 0), 0);
	}
	return (1);
}
