
#include <stdlib.h>
#include <unistd.h>
#include "shared.h"

int				error(char const *msg)
{
	if (write(2, msg, slen(msg)) == -1)
		exit(-1);
	exit(-1);
}
