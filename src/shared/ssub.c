
#include <stdlib.h>

char			*ssub(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
