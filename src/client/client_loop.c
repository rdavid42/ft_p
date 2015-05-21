/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 19:07:08 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/20 19:07:40 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "client.h"
#include "shared.h"

inline static char		*get_root(void)
{
	char				buf[1024];

	return (getcwd(buf, 1024));
}

inline static void		bufset(char *buf, size_t bufs)
{
	size_t		i;

	i = 0;
	while (i < bufs)
	{
		buf[i] = '\0';
		i++;
	}
}

int						client_loop(int sock)
{
	char				*cmd;
	char				buf[BUFS];
	int					r;
	char				*root;

	root = get_root();
	catch_signals();
	while (42)
	{
		if (!check_root_directory(root))
			return (0);
		if (write(1, "% ", 2) == -1)
			return (0);
		bufset(buf, BUFS);
		if ((r = read(0, buf, BUFS - 1) == -1))
			return (0);
		if (!check_root_directory(root))
			return (0);
		cmd = clean_line(buf);
		interpret_command(sock, cmd);
		free(cmd);
		cmd = NULL;
	}
	return (1);
}
