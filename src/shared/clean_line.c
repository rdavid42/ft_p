
#include <stdio.h>
#include <stdlib.h>

static int		count_chars(char *line)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			count++;
		if (line[i] == ' ' || line[i] == '\t')
		{
			count++;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			i--;
		}
		i++;
	}
	return (count);
}

static void		switch_char(char *old, char *new)
{
	int			i;
	int			j;

	i = 0;
	j = -1;
	while (old[i])
	{
		if (old[i] != ' ' && old[i] != '\t')
			new[++j] = old[i];
		if (old[i] == ' ' || old[i] == '\t')
		{
			new[++j] = ' ';
			while (old[i] == ' ' || old[i] == '\t')
				i++;
			i--;
		}
		i++;
	}
}

char			*clean_line(char *old)
{
	char		*new;
	int			count;

	new = NULL;
	count = count_chars(old);
	if (!(new = (char *)malloc(sizeof(char) * count + 1)))
		return (NULL);
	switch_char(old, new);
	new[count] = '\0';
	return (new);
}
