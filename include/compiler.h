#ifndef COMPILER_H_INCLUDED
#define COMPILER_H_INCLUDED


#include <stdint.h>
#include <stdbool.h>
#include <compiler/gcc.h>


#ifndef ERROR_FUNC
# define ERROR_FUNC(name, msg)                                  \
	extern int name(void)
#endif


static inline int8_t compiler_min_s8(int8_t a, int8_t b)
{
	return (a < b) ? a : b;
}

static inline int16_t compiler_min_s16(int16_t a, int16_t b)
{
	return (a < b) ? a : b;
}

static inline int32_t compiler_min_s32(int32_t a, int32_t b)
{
	return (a < b) ? a : b;
}

static inline int64_t compiler_min_s64(int64_t a, int64_t b)
{
	return (a < b) ? a : b;
}

static inline uint8_t compiler_min_u8(uint8_t a, uint8_t b)
{
	return (a < b) ? a : b;
}

static inline uint16_t compiler_min_u16(uint16_t a, uint16_t b)
{
	return (a < b) ? a : b;
}

static inline uint32_t compiler_min_u32(uint32_t a, uint32_t b)
{
	return (a < b) ? a : b;
}

static inline uint64_t compiler_min_u64(uint64_t a, uint64_t b)
{
	return (a < b) ? a : b;
}

static inline int8_t compiler_max_s8(int8_t a, int8_t b)
{
	return (a > b) ? a : b;
}

static inline int16_t compiler_max_s16(int16_t a, int16_t b)
{
	return (a > b) ? a : b;
}

static inline int32_t compiler_max_s32(int32_t a, int32_t b)
{
	return (a > b) ? a : b;
}

static inline int64_t compiler_max_s64(int64_t a, int64_t b)
{
	return (a > b) ? a : b;
}

static inline uint8_t compiler_max_u8(uint8_t a, uint8_t b)
{
	return (a > b) ? a : b;
}

static inline uint16_t compiler_max_u16(uint16_t a, uint16_t b)
{
	return (a > b) ? a : b;
}

static inline uint32_t compiler_max_u32(uint32_t a, uint32_t b)
{
	return (a > b) ? a : b;
}

static inline uint64_t compiler_max_u64(uint64_t a, uint64_t b)
{
	return (a > b) ? a : b;
}
#endif /*COMPILER_H_INCLUDED*/
