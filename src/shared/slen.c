/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slen.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 15:06:25 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/18 15:35:03 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int				slen(char const *s)
{
	int			i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
