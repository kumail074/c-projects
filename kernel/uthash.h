#ifndef UTHASH_H
#define UTHASH_H

#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#if defined(HASH_NO_STDINT) && HASH_NO_STDINT
#else
#include <stdint.h>
#endif

#if !defined(DECLTYPE) && !defined(NO_DECLTYPE)
#if defined(_MSC_VER)
#if _MSC_VER >= 1600 && defined(_cplusplus)
#define DECLTYPE(x) (decltype(x))
#else
#define NO_DECLTYPE
#endif
#elif defined(__MCST__)
#define DECLTYPE(x) (__typeof(x))
#elif defined(__BORLANDC__) || defined(__ICCARM__) || defined(__LCC__) || defined(__WATCOMC__)
#define NO_DECLTYPE
#else
#define DECLTYPE(x) (__typeof(x))
#endif
#endif

#ifdef NO_DECLTYPE
#define DECLTYPE(X)
#define DECLTYPE_ASSIGN(dst,src)
do {
    char **_da_dst = (char**)(&(dst));
    *_da_dst = (char*)(src);
} while(0)
#else
#define DECLTYPE_ASSIGN(dst,src)
do {
    dst = DECLTYPE(dst)(src);
} while(0)
#endif

#ifndef uthash_malloc
#define uthash_malloc(sz) malloc(sz)
#endif

#ifndef uthash_free
#define uthash_free(ptr,sz) free(ptr)
#endif

#ifndef uthash_bzero
#define uthash_bzero(a,n) memset(a,'\0',n)
#endif

#ifndef uthash_strlen
#define uthash_strlen(s) strlen(s)
#endif


#ifndef HASH_FUNCTION
#define HASH_FUNCTION(keyptr, keylen, hashv) HASH_JEN(keyptr, keylen, hashv)
#endif

#ifndef HASH_KEYCMP
#define HASH_KEYCMP(a,b,n) memcmp(a,b,n)
#endif

#ifndef uthash_noexpand_fyi
#define uthash_noexpand_fyi(tbl)
#endif
#ifndef uthash_expand_fyi
#define uthash_expand_fyi(tbl)
#endif

#ifndef HASH_NONFATAL_OOM
#define HASH_NONFATAL_OOM 0
#endif

#if HASH_NONFATAL_OOM
// malloc failures (out-of-memory) can be recovered from

#ifndef uthash_nonfatal_oom
#define uthash_nonfatal_oom(obj) do {} while(0)
#endif

#define HASH_RECORD_OOM(oomed) do { oomed = 1; } while(0)
#define IF_HASH_NONFATAL_OOM(x) x

#else
/* malloc failures (out-of-memory) result in lost memory, hash tables are unusable */
#ifndef uthash_fatal
#define uthash_fatal(msg) exit(-1)
#endif

#define HASH_RECORD_OOM(oomed) uthash_fatal("out of memory")
#define IF_HASH_NONFATAL_OOM(x)

#endif

#endif