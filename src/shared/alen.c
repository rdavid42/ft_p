
int				alen(char **array)
{
	int			i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}