#ifndef STRING_ARCH_CORTEXM_H_INCLUDED
#define STRING_ARCH_CORTEXM_H_INCLUDED


#include <generic/string.h>


extern void *memcpy(void *dest, const void *src, size_t n);
extern void *memset(void *s, int c, size_t n);

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
#endif /*STRING_ARCH_CORTEXM_H_INCLUDED*/
