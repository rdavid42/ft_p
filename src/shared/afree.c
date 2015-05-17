
#include <stdlib.h>

void			afree(char **array)
{
	int			i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}