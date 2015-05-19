/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryd <ryd@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 18:17:12 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 07:07:18 by ryd              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <sys/socket.h>
#include <unistd.h>
#include "shared.h"

int					pwd(char *root, int *cs, char *cmd)
{
	char			buf[1024];
	char			*cur = getcwd(buf, 1024);
	int const		rlen = slen(root);
	int const		clen = slen(cur);
	int				ret;

	(void)cmd;
	if (!scmp(cur, root, slen(root)))
	{
		ret = clen - rlen;
		send(*cs, (void *)&ret, sizeof(uint32_t), 0);
		send(*cs, cur + rlen, ret, 0);
	}
	return (1);
}