#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED


#include <compiler.h>


#define ARRAY_LEN(a)	(sizeof(a) / sizeof((a)[0]))


static inline int isdigit(int c)
{
	return (c >= '0') && (c <= '9');
}


__always_inline static bool is_power_of_two(unsigned long x)
{
	return x && !(x & (x - 1));
}


#define min_u(a, b)                                                     \
	((sizeof(a) == 1) && (sizeof(b) == 1) ? compiler_min_u8(a, b)   \
	: (sizeof(a) <= 2) && (sizeof(b) <= 2) ? compiler_min_u16(a, b) \
	: (sizeof(a) <= 4) && (sizeof(b) <= 4) ? compiler_min_u32(a, b) \
	: compiler_min_u64(a, b))


#define div_ceil(a, b)	(((a) + (b) - 1) / (b))
#endif /*UTIL_H_INCLUDED*/
