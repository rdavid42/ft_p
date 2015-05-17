/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 21:23:03 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 18:17:47 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int				scmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
