
#include <stdlib.h>
#include <unistd.h>
#include "shared.h"

int				error(char const *msg)
{
	(void)write(2, msg, slen(msg));
	exit(-1);
}
