#ifndef STRING_ARCH_POSIX_H_INCLUDED
#define STRING_ARCH_POSIX_H_INCLUDED


#include <generic/string.h>


static inline void *memcpy(void *dest, const void *src, size_t n)
{
	return generic_memcpy(dest, src, n);
}

static inline void *memset(void *s, int c, size_t n)
{
	return generic_memset(s, c, n);
}

static inline size_t strlen(const char *str)
{
	return generic_strlen(str);
}

static inline int strcmp(const char *str1, const char *str2)
{
	return generic_strcmp(str1, str2);
}

static inline int strncmp(const char *str1, const char *str2, size_t n)
{
	return generic_strncmp(str1, str2, n);
}
#endif /*STRING_ARCH_POSIX_H_INCLUDED*/
