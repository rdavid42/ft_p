/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 11:01:14 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 11:31:37 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

int					quit(int *cs, char *cmd)
{
	char			r;

	r = 1;
	send(*cs, (void *)&r, sizeof(char), 0);
	close(*cs);
	exit(0);
	(void)cmd;
	return (1);
}