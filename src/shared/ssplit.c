/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssplit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 19:47:27 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 18:17:53 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shared.h"

static size_t		wcount(char const *s, char c)
{
	size_t		wcount;
	size_t		i;

	i = 0;
	wcount = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			if (s[i + 1] == c || s[i + 1] == '\0')
				wcount++;
			i++;
		}
	}
	return (wcount);
}

static char			**addwords(char **tab, char const *s, size_t i, char c)
{
	size_t		wstart;
	size_t		t;

	t = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		wstart = i;
		while (s[i] != c && s[i] != '\0')
		{
			if ((s[i + 1] == c || s[i + 1] == '\0'))
			{
				tab[t] = ssub(s, wstart, i + 1 - wstart);
				t++;
			}
			i++;
		}
	}
	return (tab);
}

char				**ssplit(char const *s, char c)
{
	char		**tab;
	size_t		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * wcount(s, c) + 1)))
		return (NULL);
	tab = addwords(tab, s, i, c);
	tab[wcount(s, c)] = NULL;
	return (tab);
}
