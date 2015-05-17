
#include <unistd.h>
#include "shared.h"

int			print_error(char const *msg, int const code)
{
	return (write(2, msg, slen(msg)), code);
}

void		*print_error_p(char const *msg)
{
	return (write(2, msg, slen(msg)), NULL);
}