#ifndef MASSTREE_CONFIG_H
#define MASSTREE_CONFIG_H

#define CACHE_LINE_SIZE 64

#define HAVE_OFF_T 1
#define SIZEOF_OFF_T 8
#define HAVE_LONG_LONG 1
#define SIZEOF_LONG_LONG 8
#define HAVE_SIZE_T 1
#define SIZEOF_SIZE_T 8
#define HAVE_OFF_T_IS_LONG_LONG 1
#define HAVE_SIZE_T_IS_UNSIGNED_LONG 1
#define HAVE_SIZE_T_IS_UNSIGNED_LONG_LONG 1

#include "compiler_features.h"

#define HAVE_CLOCK_GETTIME 1
#define HAVE_EXECINFO_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_LIBNUMA 1
#define HAVE_NUMA_H 1
#define HAVE_STD_HASH 1
/* #undef HAVE_SYS_EPOLL_H */
#define HAVE_VSNPRINTF 1

#if CXX_COMPILER_CXX_CONSTEXPR
#define HAVE_CXX_CONSTEXPR 1
#endif

#if CXX_COMPILER_CXX_STATIC_ASSERT
#define HAVE_CXX_STATIC_ASSERT 1
#endif

#if CXX_COMPILER_CXX_ALIAS_TEMPLATES
#define HAVE_CXX_TEMPLATE_ALIAS 1
#endif

#include <sys/mman.h>
#ifdef MADV_HUGEPAGE
#define HAVE_MADV_HUGEPAGE 1
#endif
#ifdef MAP_HUGETLB
#define HAVE_MAP_HUGETLB 1
#endif

#if defined(HAVE_MAP_HUGETLB) && defined(HAVE_MADV_HUGEPAGE)
#define HAVE_SUPERPAGE 1
#endif

#define HAVE_CXX_RVALUE_REFERENCES 1

#define HAVE___SYNC_VAL_COMPARE_AND_SWAP 1
#define HAVE___SYNC_BOOL_COMPARE_AND_SWAP 1
#define HAVE___SYNC_VAL_COMPARE_AND_SWAP_8 1
/* #undef HAVE___SYNC_FETCH_AND_ADD_8 */
/* #undef HAVE___SYNC_FETCH_AND_OR_8 */
#define HAVE___BUILTIN_CLZ 1
#define HAVE___BUILTIN_CLZL 1
#define HAVE___BUILTIN_CLZLL 1
#define HAVE___BUILTIN_CTZ 1
#define HAVE___BUILTIN_CTZL 1
#define HAVE___BUILTIN_CTZLL 1


/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
#  undef WORDS_BIGENDIAN
# endif
#endif

/* Define if WORDS_BIGENDIAN has been set. */
#undef WORDS_BIGENDIAN_SET


/** @brief Assert macro that always runs. */
extern void fail_always_assert(const char* file, int line, const char* assertion, const char* message = 0) __attribute__((noreturn));
#define always_assert(x, ...) do { if (!(x)) fail_always_assert(__FILE__, __LINE__, #x, ## __VA_ARGS__); } while (0)
#define mandatory_assert always_assert

/** @brief Assert macro for invariants.

    masstree_invariant(x) is executed if --enable-invariants or
    --enable-assertions. */
extern void fail_masstree_invariant(const char* file, int line, const char* assertion, const char* message = 0) __attribute__((noreturn));
#if FORCE_ENABLE_ASSERTIONS || (!defined(ENABLE_INVARIANTS) && ENABLE_ASSERTIONS) || ENABLE_INVARIANTS
#define masstree_invariant(x, ...) do { if (!(x)) fail_masstree_invariant(__FILE__, __LINE__, #x, ## __VA_ARGS__); } while (0)
#else
#define masstree_invariant(x, ...) do { } while (0)
#endif

/** @brief Assert macro for preconditions.

    masstree_precondition(x) is executed if --enable-preconditions or
    --enable-assertions. */
extern void fail_masstree_precondition(const char* file, int line, const char* assertion, const char* message = 0) __attribute__((noreturn));
#if FORCE_ENABLE_ASSERTIONS || (!defined(ENABLE_PRECONDITIONS) && ENABLE_ASSERTIONS) || ENABLE_PRECONDITIONS
#define masstree_precondition(x, ...) do { if (!(x)) fail_masstree_precondition(__FILE__, __LINE__, #x, ## __VA_ARGS__); } while (0)
#else
#define masstree_precondition(x, ...) do { } while (0)
#endif

#ifndef invariant
#define invariant masstree_invariant
#endif
#ifndef precondition
#define precondition masstree_precondition
#endif

#define MASSTREE_MAXKEYLEN 255

#endif
