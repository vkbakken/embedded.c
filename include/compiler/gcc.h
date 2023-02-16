#ifndef COMPILER_GCC_H_INCLUDED
#define COMPILER_GCC_H_INCLUDED


#define __noreturn __attribute__((noreturn))
#define __must_check __attribute__((warn_unused_result))
#define __used __attribute__((used))
#define __always_inline inline __attribute__((always_inline))
#define __nonnull(...) __attribute__((nonnull (__VA_ARGS__)))
#define __printf_format(fmt_index, first_arg_index) \
	__attribute__((format(printf, fmt_index, first_arg_index)))

#define compiler_align_data(byte_alignment) \
	__attribute__((aligned(byte_alignment)))

#define likely(exp)             __builtin_expect(!!(exp), 1)
#define unlikely(exp)           __builtin_expect(!!(exp), 0)
#define is_constant(exp)        __builtin_constant_p(exp)

#define barrier()               asm volatile("" ::: "memory")

#if defined(__GNUC__)
# if __NO_INLINE__
#  define ERROR_FUNC(name, msg) \
	  extern int name(void) {}
# else
#  if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
#   define ERROR_FUNC(name, msg) \
	   extern __attribute__((error(msg))) int name(void)
#  endif
# endif
#endif
#endif /*COMPILER_GCC_H_INCLUDED*/