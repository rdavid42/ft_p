/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 14:42:51 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 17:53:47 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "shared.h"

inline static int		sep(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int				count_chars(char *line)
{
	int			i;
	int			size;

	i = 0;
	size = 0;
	while (line[i])
	{
		if (!sep(line[i]))
			size++;
		else
		{
			if (!i)
				i++;
			else
				size++;
			while (sep(line[i]))
				i++;
			i--;
		}
		i++;
	}
	return (size);
}

static void				switch_char(char *old, char *new, int const size)
{
	int					i;
	int					j;

	i = 0;
	j = -1;
	while (old[i])
	{
		if (!sep(old[i]))
			new[++j] = old[i];
		else
		{
			if (!i)
				i++;
			else
				new[++j] = ' ';
			while (sep(old[i]))
				i++;
			i--;
		}
		i++;
	}
	if (new[size - 1] == ' ')
		new[size - 1] = '\0';
}

char					*clean_line(char *old)
{
	char				*new;
	int					size;

	new = NULL;
	size = 0;
	size = count_chars(old);
	if (!(new = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	switch_char(old, new, size);
	new[size] = '\0';
	return (new);
}
