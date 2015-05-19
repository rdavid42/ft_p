/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 19:04:48 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 09:33:26 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include "shared.h"
#include "client.h"

static void		check_recv(int r, int *sock)
{
	if (r == -1)
		close(*sock), error(REC_ERR);
	else if (!r)
		close(*sock), error(CO_CLOSED);
}

int				pwd(int *sock, char *cmd)
{
	int			pwd_size;
	char		*pwd;
	int			r;

	pwd_size = 0;
	if (write(*sock, cmd, slen(cmd)) == -1)
		close(*sock), error(REQ_ERR);
	r = recv(*sock, (void *)&pwd_size, sizeof(uint32_t), 0);
	check_recv(r, sock);
	pwd = (char *)malloc(sizeof(char) * pwd_size + 1);
	r = recv(*sock, pwd, pwd_size, 0);
	check_recv(r, sock);
	(void)!write(1, pwd, pwd_size);
	(void)!write(1, "\n", 1);
	(void)!write(1, "SUCCESS\n", 9);
	free(pwd);
	return (1);
}
