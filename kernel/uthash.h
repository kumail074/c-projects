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

/*initial number of buckets*/
#define HASH_INITIAL_NUM_BUCKETS 32U
#define HASH_INITIAL_NUM_BUCKETS_LOG2 5U
#define HASH_BKT_CAPACITY_THRESH 10U

/*  calculate the element whose hash handle address is hhp
    hhp is pointer to UT_hash_handle inside user-defined struct

    note:
        it reverses the process of extracting UT_hash_handle from a struct
        
        uthash often stores only the hh pointer but sometimes need to recover
        the original structure
        
        this calculation retrieves the base address of the structure that 
        contains hh

*/
#define ELMT_FROM_HH(tbl, hhp) ((void*)(((char*)(hhp)) - ((tbl)->hho)))
/* 

    (char*)(hhp)
        this allows byte-wise pointer arithmetic
    
    ((char*)(hhp)) - (tbl->hho)
        tbl->hho is hash handle offset, which tells us how far hh is
        from the start of the struct
        subtracting hho moves the pointer back to the beginning of struct 
        that contains hhTh

    ((void*)(((char*)(hhp)) - (tbl->hho))
        used to get a generic pointer to the struct containing hh
*/

/*  calculate the hash handle from element address elp 
    
    elp is pointer to the element in hash table
    
    tbl->hho is hash handle offset which is the byte offset where the
    UT_hash_handle is stored inside the structure

*/
#define HH_FROM_ELMT(tbl,elp) ((UT_hash_handle*)(void*)(((char*)(elp)) + ((tbl)->hho)))
/*
    ((UT_hash_handle*)(void*)(((char*)(elp)) + ((tbl)->hho)))

    by adding hho to elp, we move the pointer where UT_hash_handle is located.
        (char*)(elp) + (tbl->hho)
    
    converts into void*, usually done for safety or to follow generic pointer conventions.
        (void*)[(char*)(elp) - (tbl->hho)]
    
    finally, point is casted into a UT_hash_handle*, making it point to the UT_hash_handle
    structure inside the elp.
        ((UT_hash_handle*)(void*)(((char*)(elp)) + ((tbl)->hho)))
*/


#define HASH_ROLLBACK_BKT(hh, head, itemptrhh) 
/*  restores the bucket count and resets the UT_hash_handle pointers when an item is 
    removed from the hash table.
    it corrects the bucket count in case of a failed insertion or rollback operation.
*/

do {
    struct UT_hash_handle* hd_hh_item = itemptrhh; //local pointer
    unsigned _hd_bkt; //to store the computed bucket index
    HASH_TO_BKT(_hd_hh_item->hashv, (head)->hh.tbl->num_buckets, _hd_bkt); //computes which bucket an item belongs to
    (head)->hh.tbl->buckets[_hd_bkt].count++; //increments the count of items in the computed bucket
    _hd_hh_item->hh_next = NULL; //removes link to next element
    _hd_hh_item->hh_prev = NULL; //removes link to previous element
} while (0)

#define HASH_VALUE(keyptr, keylen, hashv)
do {
    HASH_FUNCTION(keyptr, keylen, hashv);
} while (0)

#define HASH_FIND_BYHASHVALUE(hh, head, keyptr, keylen, hashval, out)
do {
    out = NULL;
    if (head) {
        unsigned _hf_bkt;
        HASH_TO_BKT(hashval, head->hh.tbl->num_buckets, _hf_bkt);
        
    }
}

#endif