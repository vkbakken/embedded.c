#ifndef STRING_GENERIC_H_INCLUDED
#define STRING_GENERIC_H_INCLUDED


#include <types.h>
#include <compiler.h>


void *generic_memcpy(void *dest, const void *src, size_t n);
void *generic_memset(void *s, int c, size_t n);
size_t generic_strlen(const char *str);
int generic_strcmp(const char *str1, const char *str2) __nonnull(1, 2);
int generic_strncmp(const char *str1, const char *str2, size_t n) __nonnull(1, 2);
#endif /*STRING_GENERIC_H_INCLUDED*/
