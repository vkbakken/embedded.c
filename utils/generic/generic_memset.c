#include <types.h>


void *generic_memset(void *s, int c, size_t n)
{
	char *p = s;

	while (n--)
		*p++ = c;

	return s;
}
