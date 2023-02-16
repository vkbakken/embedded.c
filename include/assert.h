#ifndef ASSERT_H_INCLUDED
#define ASSERT_H_INCLUDED


#ifdef CONFIG_ASSERT
# define assert(condition)                                              \
	do {                                                            \
		if (ASSERT_ENABLED && unlikely(!(condition))) {         \
			cpu_irq_disable();                              \
			dbg_printf_level(DEBUG_ASSERT,                  \
				"%s:%d: Assertion \"%s\" failed!\n",    \
				__FILE__, __LINE__, #condition);        \
			abort();                                        \
		}                                                       \
	} while (0)
#else
# define assert(condition)
#endif


#define unhandled_case(value)                                           \
	do {                                                            \
		if (ASSERT_ENABLED) {                                   \
			dbg_printf_level(DEBUG_ASSERT,                  \
				"%s:%d: Unhandled case value %d\n",     \
				__FILE__, __LINE__, (value));           \
			abort();                                        \
		}                                                       \
	} while (0)

//ERROR_FUNC(build_assert_failed, "Build assertion failed");


#define build_assert(condition)                                         \
	do {                                                            \
		if (!(condition))                                       \
			build_assert_failed();                          \
	} while (0)

#endif /*ASSERT_H_INCLUDED*/
