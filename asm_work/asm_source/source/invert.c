#include "common.h"

int		invert_2(int i)
{
	i = ((i >> 8) & 0xff) | ((i << 8) & 0xff00);
	return (i);
}

int		invert_4(int i)
{
	i = ((i >> 24) & 0xff) | ((i >> 8) & 0xff00)
			| ((i << 8) & 0xff0000) | ((i << 24) & 0xff000000);
	return (i);
}
