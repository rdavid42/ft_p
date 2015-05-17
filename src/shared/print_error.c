/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryd <ryd@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 12:04:02 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 23:50:26 by ryd              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shared.h"

int			print_error(char const *msg, int const code)
{
	return ((void)!write(2, msg, slen(msg)), code);
}

void		*print_error_p(char const *msg)
{
	return ((void)!write(2, msg, slen(msg)), NULL);
}
