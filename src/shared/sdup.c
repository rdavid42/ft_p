/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdup.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/19 13:43:51 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 15:57:32 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shared.h"

char			*sdup(const char *s1)
{
	char		*s2;
	size_t		i;

	i = 0;
	if ((s2 = (char *)malloc(sizeof(*s2) * slen(s1) + 1)))
	{
		while (s1[i] != '\0')
		{
			s2[i] = s1[i];
			i++;
		}
		s2[i] = '\0';
		return (s2);
	}
	return (NULL);
}
