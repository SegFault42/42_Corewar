#include "common.h"

int	invert_2(int i)
{
	i = ((i >> 8) & 0xff) | ((i << 8) & 0xff00);
	return (i);
}

int	invert_4(int i)
{
	i = ((i >> 24) & 0xff) | ((i >> 8) & 0xff00) | ((i << 8) & 0xff0000) | ((i << 24) & 0xff000000);
	return (i);
}

long	invert_8(long i)
{
	/*long	mask_low;
	long	mask_high;

	mask_low =;
	mask_high =;*/
	i = ((i >> 56) & 0xff) | ((i >> 40) & 0xff00) 
		| ((i >> 24) & 0xff0000) | ((i >> 8) & 0xff000000) 
		| ((i << 8) & 0xff00000000) | ((i << 24) & 0xff0000000000) 
		| ((i << 40) & 0xff000000000000) | ((i << 56) & 0xff00000000000000);
	return (i);
}

