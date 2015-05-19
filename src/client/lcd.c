/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 09:39:33 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 17:35:06 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "shared.h"

inline static char		*get_cwd(void)
{
	char				buf[1024];

	return (getcwd(buf, 1024));
}

static int				check_errors(char **cmd_args)
{
	if (alen(cmd_args) < 2)
		return (err_msg("Not enough arguments!\n"), 0);
	if (alen(cmd_args) > 2)
		return (err_msg("Too many arguments!\n"), 0);
	return (1);
}

static void				go_dir(char **cmd_args)
{
	char				*t[2];

	t[0] = sjoin(get_cwd(), "/");
	t[1] = sjoin(t[0], cmd_args[1]);
	free(t[0]);
	if (chdir(t[1]) != 0)
		err_msg("No such directory !\n");
	free(t[1]);
}

int						lcd(int *sock, char *cmd)
{
	char				**cmd_args;

	(void)sock;
	cmd_args = ssplit(cmd, ' ');
	if (!check_errors(cmd_args))
		return (0);
	go_dir(cmd_args);
	afree(cmd_args);
	return (1);
}
