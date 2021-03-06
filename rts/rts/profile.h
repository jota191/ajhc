#ifndef RTS_PROFILE_H
#define RTS_PROFILE_H

#include <stdio.h>
#include "rts/cdefs.h"

#ifndef JHC_VALGRIND
#define JHC_VALGRIND 0
#endif

#ifndef JHC_MEM_ANNOTATE
#define JHC_MEM_ANNOTATE 0
#endif

#ifndef _JHC_PROFILE
#define _JHC_PROFILE 0
#endif

#if JHC_VALGRIND
#include <valgrind/valgrind.h>
#include <valgrind/memcheck.h>
#else
#define VALGRIND_MAKE_MEM_UNDEFINED(x,y) \
    do { } while (0)
#define VALGRIND_MAKE_MEM_DEFINED(x,y) \
    do { } while (0)
#define VALGRIND_MAKE_MEM_NOACCESS(x,y) \
    do { } while (0)
#define VALGRIND_PRINTF(...) \
    do { } while (0)
#endif

// void A_UNUSED profile_print_header(FILE *file, char *value_unit);
void A_COLD jhc_print_profile(void);

#if _JHC_PROFILE || _JHC_PROFILE_GCONLY
struct profile_stack;
extern struct profile_stack gc_alloc_time;
extern struct profile_stack gc_gc_time;
void jhc_profile_push(struct profile_stack *ps);
void jhc_profile_pop(struct profile_stack *ps);
#define profile_push(x) jhc_profile_push(x)
#define profile_pop(x)  jhc_profile_pop(x)
#else
#define profile_push(x)          do { } while(0)
#define profile_pop(x)           do { } while(0)
#endif

#if !_JHC_PROFILE
#define alloc_count(x,y)         do { } while(0)
#define print_alloc_size_stats() do { } while(0)
#endif

#ifdef _JHC_USE_OWN_STDIO
/* Implement us! */
int jhc_printf_stderr(const char *fmt, ...);
int jhc_fputs_stderr(const char *s);
int jhc_fflush_stdout(void);
#else
#define jhc_printf_stderr(...) fprintf(stderr,__VA_ARGS__)
#define jhc_fputs_stderr(S)    fputs(S, stderr)
#define jhc_fflush_stdout()    fflush(stdout)
#endif /* _JHC_USE_OWN_STDIO */

#if JHC_STATUS > 1
#define debugf(...) jhc_printf_stderr(__VA_ARGS__)
#else
#define debugf(...) do { } while (0)
#endif

#endif /* RTS_PROFILE_H */
