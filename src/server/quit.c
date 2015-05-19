/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 11:01:14 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 16:44:26 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

int					quit(int *root, int *cs, char *cmd, int *id)
{
	char			r;

	(void)cmd;
	(void)root;
	r = 1;
	send(*cs, (void *)&r, sizeof(char), 0);
	printf("Connexion to client %d closed!\n", *id);
	close(*cs);
	exit(0);
	return (1);
}
