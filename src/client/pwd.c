/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 19:04:48 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/18 19:21:51 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

static int		check_recv(int r, int *sock)
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
	r = recv(*sock, (void *)&pwd_size, sizeof(uint32_t), 0);
	check_recv(r, sock);
	pwd = (char *)malloc(sizeof(char) * pwd_size + 1);
	r = recv(*sock, pwd, pwd_size, 0);
	check_recv(r, sock);
	(void)!write(1, pwd, pwd_size);
	(void)!write(1, "\n", 1);
	return (1);
}
