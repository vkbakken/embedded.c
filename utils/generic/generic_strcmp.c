#include <types.h>


int generic_strcmp(const char *str1, const char *str2)
{
	char    c1;
	char    c2;

	while (true) {
		c1 = *str1++;
		c2 = *str2++;

		if (!c1 || !c2 || c1 != c2)
			break;
	}

	return ((int)c1 - (int)c2);
}

int generic_strncmp(const char *str1, const char *str2, size_t n)
{
	char    c1;
	char    c2;

	if (!n)
		return 0;

	do {
		c1 = *str1++;
		c2 = *str2++;

		if (!c1 || !c2 || c1 != c2)
			break;
	} while (--n);

	return ((int)c1 - (int)c2);
}
