/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 13:11:59 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 14:02:25 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "shared.h"

static void				s_ignore(int sig)
{
	(void)sig;
}

static void				s_exit_error(int sig)
{
	(void)sig;
	err_msg("ERROR: an unknown error occured! :(\n");
	exit(0);
}

static void				s_exit_success(int sig)
{
	(void)sig;
	err_msg("Client force closed!\n");
	exit(0);
}

void					catch_signals(void)
{
	signal(SIGINT, s_ignore);
	signal(SIGKILL, s_exit_success);
	signal(SIGQUIT, s_ignore);
	signal(SIGTERM, s_exit_success);
	signal(SIGHUP, s_exit_success);
	signal(SIGSEGV, s_exit_error);
	signal(SIGBUS, s_exit_error);
	signal(SIGFPE, s_exit_error);
	signal(SIGABRT, s_exit_success);
}
