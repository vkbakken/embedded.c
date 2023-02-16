#include <types.h>


size_t generic_strlen(const char *str)
{
	size_t	len = 0;

	while (*str++)
		len++;

	return len;
}
