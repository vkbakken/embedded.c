#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED


#include <stream.h>
#include <types.h>


enum debug_level {
	DEBUG_NONE	= 0,	//!< No debugging messages
	DEBUG_PANIC,		//!< System panic (fatal exceptions, etc.)
	DEBUG_ASSERT,		//!< Assertion failures
	DEBUG_ERROR,		//!< Major errors which may be recoverable
	DEBUG_WARNING,		//!< Things that might cause problems
	DEBUG_INFO,		//!< Informational messages
	DEBUG_VERBOSE,		//!< Verbose debugging messages
};


#ifndef CONFIG_DEBUG
# define dbg_init()		do { } while (0)
# undef DEBUG_LEVEL
# define DEBUG_LEVEL		DEBUG_NONE
#else
void dbg_backend_init(struct stream *s);
void dbg_init(void);
# ifndef DEBUG_LEVEL
#  ifdef CONFIG_DEBUG_LEVEL
#   define DEBUG_LEVEL		CONFIG_DEBUG_LEVEL
#  else
#   define DEBUG_LEVEL		DEBUG_INFO
#  endif
# endif
#endif


extern int dbg_vprintf(const char *format, va_list ap);
extern int dbg_printf(const char *format, ...) __printf_format(1, 2);
extern int dbg_putstr(const char *str);
extern int dbg_putchar(int c);



static inline int dbg_priv_retzero(void)
{
	return 0;
}


#define dbg_priv_check_level(level)					\
	(DEBUG_LEVEL != DEBUG_NONE && (level) <= DEBUG_LEVEL)


#define dbg_vprintf_level(level, format, ap)                    \
	do {                                                    \
		if (dbg_priv_check_level(level))                \
			dbg_vprintf(format, ap);                \
	} while (0)


#define dbg_printf_level(level, ...)                            \
	do {                                                    \
		if (dbg_priv_check_level(level))                \
			dbg_printf(__VA_ARGS__);                \
	} while (0)


#define dbg_putstr_level(level, str)				\
	(dbg_priv_check_level(level)				\
		? dbg_putstr(str)				\
		: dbg_priv_retzero())

#define dbg_putchar_level(level, c)				\
	(dbg_priv_check_level(level)				\
		? dbg_putchar(c)				\
		: dbg_priv_retzero())

#define dbg_panic(...)						\
	dbg_printf_level(DEBUG_PANIC, __VA_ARGS__)

#define dbg_error(...)						\
	dbg_printf_level(DEBUG_ERROR, __VA_ARGS__)

#define dbg_warning(...)					\
	dbg_printf_level(DEBUG_WARNING, __VA_ARGS__)

#define dbg_info(...)						\
	dbg_printf_level(DEBUG_INFO, __VA_ARGS__)

#define dbg_verbose(...)					\
	dbg_printf_level(DEBUG_VERBOSE, __VA_ARGS__)
#endif /*DEBUG_H_INCLUDED*/
