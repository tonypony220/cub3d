#include "cub3d.h"

int		logn(long n, unsigned long base, int unsig, int islong)
{
	if (n < 0 && !unsig)
	{
		return ((n * -1 > (long)(base - 1)) ? 1 + logn(
					n * -1 / base, base, unsig, islong) : 0);
	}
	if (!islong)
	{
		return ((unsigned int)n > (unsigned int)(base - 1)) ? 1 + logn(
					(unsigned int)n / (unsigned int)base,
					base, unsig, islong) : 0;
	}
	return ((unsigned long)n > (base - 1) ? 1 + logn(
				n / base, base, unsig, islong) : 0);
}
