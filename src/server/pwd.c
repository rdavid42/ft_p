/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 18:17:12 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 16:17:11 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <sys/socket.h>
#include <unistd.h>
#include "shared.h"

int					pwd(char *root, int *cs, char *cmd, int *id)
{
	char			buf[1024];
	char const		*cur = getcwd(buf, 1024);
	int const		rlen = slen(root);
	int const		clen = slen(cur);
	int				ret;

	(void)cmd, (void)id;
	if (!scmp(cur, root, slen(root)))
	{
		ret = clen - rlen;
		ret = ret <= 0 ? 1 : ret;
		send(*cs, (void *)&ret, sizeof(uint32_t), 0);
		if (ret > 1)
			send(*cs, cur + rlen, ret, 0);
		else
			send(*cs, "/", 1, 0);
	}
	return (1);
}
