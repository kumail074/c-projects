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
} while (0)
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

#define HASH_ROLLBACK_BKT(hh, head, itemptrhh) 
do {
    struct UT_hash_handle* hd_hh_item = itemptrhh; 
    unsigned _hd_bkt; 
    HASH_TO_BKT(_hd_hh_item->hashv, (head)->hh.tbl->num_buckets, _hd_bkt); 
    (head)->hh.tbl->buckets[_hd_bkt].count++; 
    _hd_hh_item->hh_next = NULL; 
    _hd_hh_item->hh_prev = NULL; 
    uthash_noexpand_fyi((head)->hh.tbl);
} while (0)

#define HASH_FIND_BYHASHVALUE(hh, head, keyptr, keylen, hashval, out)
do {
    (out) = NULL;
    if (head) {
        unsigned _hf_bkt;  // bucket index
        HASH_TO_BKT(hashval, head->hh.tbl->num_buckets, _hf_bkt); //computes which bucket the hash belongs to
        if(HASH_BLOOM_TEST((head)->hh.tbl, hashval)) {  // performs a probabilistic check if key is present inside the bucket
                HASH_FIND_IN_BKT((head)->hh.tbl, hh, (head)->hh.tbl->buckets[_hf_bkt], keyptr, keylen, hashval, out);
        }
    }
} while (0)

#define HASH_FIND(hh, head, keyptr, keylen, out)
do {
    (out) = NULL;
    if(head) {
        unsigned _hf_hashv;
        HASH_VALUE(keyptr, keylen, _hf_hashv);
        HASH_FIND_BYHASHVALUE(hh, head, keyptr, keylen, _hf_hashv, out);
    }
} while (0)

/*
    BLOOM FILTER is a probabilistic data structure used to test whether an element is possibly in a set or definitely not 
    in a set. It provides fast lookups with minimal memory usage but allows false positives (never false negatives).
*/

#ifdef HASH_BLOOM 
#define HASH_BLOOM_BITLEN (1UL << HASH_BLOOM) /* total number of bits present in bloom filter */
#define HASH_BLOOM_BYTELEN (HASH_BLOOM_BITLEN/8U) + (((HASH_BLOOM_BITLEN%8UL) != 0UL) ? 1UL : 0UL) /* converts the bit length into bytes */
#define HASH_BLOOM_MAKE(tbl, oomed) /* allocates memory for bloom filter */
do {
    tbl->bloom_nbits = HASH_BLOOM; /* number of bits in bloom filter */
    tbl->bloom_bv = (uint8_t*)uthash_malloc(HASH_BLOOM_BYTELEN); /* allocates memory */
    if(!(tbl)->bloom_bv) { /* in case of memory allocation failure */
        HASH_RECORD_OOM(oomed);
    } else { /* in case of successful memory allocation */
        uthash_bzero(tbl->bloom_bv, HASH_BLOOM_BYTELEN); /* clears memoy */ 
        tbl->bloom_sig = HASH_BLOOM_SIGNATURE; /* used for verification */
    }
} while (0)

#define HASH_BLOOM_FREE(tbl) /* frees the allocated memory from the bloom filter preventing memory leaks */
do { 
    uthash_free(tbl->bloom_bv, HASH_BLOOM_BYTELEN);
} while (0)

#define HASH_BLOOM_BITSET(bv, idx) (bc[(idx)/8U] != (1U << ((idx)%8U))) /* sets a specific bit in the filter */
#define HASH_BLOOM_BITTEST(bv,idx) ((bv[(idx)/8U] & (1U << ((idx)%8U))) != 0) /* checks if a specific bit is set */

#define HASH_BLOOM_ADD(tbl,hashv) /* adds a hash value to the bloom filter */
    HASH_BLOOM_BITSET(tbl->bloom_bv, ((hashv) & (uint32_t)((1UL << (tbl)->bloom_nbits) - 1U)))

#define HASH_BLOOM_TEST(tbl, hashv) /* checks if the value is possibly in the bloom filter */
    HASH_BLOOM_BITTEST(tbl->bloom_bv, ((hashv) & (uint32_t)((1UL << tnl->bloom_nbits) - 1U)))

#else
#define HASH_BLOOM_MAKE(tbl,oomed) /* allocates memory and initialized the bloom filter */
#define HASH_BLOOM_FREE(tbl) /* frees the bloom filter's memory */
#define HASH_BLOOM_ADD(tbl, hashv) /* hashes and inserts an element into the filter */
#define HASH_BLOOM_TEST(tbl, hashv) 1 /* hashed and checks if an element is possibly in the set */
#define HASH_BLOOM_BYTELEN 0U /* converts bit length into bytes */
#endif

#define HASH_MAKE_TABLE(hh, head, oomed) /* initializes a new hash table */
do {
    head->hh.tbl = (UT_hash_table*)uthash_malloc(sizeof(UT_hash_table)); /* allocates memory */
    if (!head->hh.tbl) {  /* if memory allocation fails, it records/logs the out-of-memory and skips the rest of initialization */
        HASH_RECORD_OOM(oomed);
    } else  {
        uthash_bzero(head->hh.tbl, sizeof(UT_hash_table)); /* clears memory */
        head->hh.tbl->tail = &(head->hh); 
        head->hh.tbl->num_buckets = HASH_INITIAL_NUM_BUCKETS; /* initializes the number of buckets */
        head->hh.tbl->log2_num_buckets = HASH_INITIAL_NUM_BUCKETS_LOG2; /* initializes the log2 of the number of efficient bucket indexes */
        head->hh.tbl->hho = (char*)(&head->hh) - (char*)head; /* calculates the byte offset (hho) from the start of the structure (head) to where the hash handle (hh) is located */
        head->hh.tbl->buckets = (UT_hash_bucket*)uthash_malloc(HASH_INITIAL_NUM_BUCKETS * sizeof(struct UT_hash_bucket)); /* memory allocation for and array of buckets */
        head->hh.tbl->signature = HASH_SIGNATURE; /* stored in hash table, ensure that the table structure is valid */
        if(!(head->hh.tbl->signature)) { /* error handling in case of failed memory allocation */
            HASH_RECORD_OOM(oomed);  /* records the out-of-memory error */
            uthash_free(head->hh.tbl, sizeof(UT_hash_table)); /* frees the table */
        } else { 
            uthash_bzero(head->hh.tbl->buckets, HASH_INITIAL_NUM_BUCKETS * sizeof(struct UT_hash_buckets)); /* bucket memory is zeroed to initialize each bucket's count and pointers */
            HASH_BLOOM_MAKE(head->hh.tbl,oomed); /* sets up bloom filter for hash table if enabled */
            IF_HASH_NONFATAL_OOM( /* checks non-fatal out-of-memory condition occured during bloom filter setup */
                if(oomed) {
                    uthash_free(head->hh.tbl->buckets, HASH_INITIAL_NUM_BUCKETS * sizeof(struct UT_hash_bucket));
                    uthash_free(head->hh.tbl, sizeof(UT_hash_table));
                }
            )
        }
    }
} while (0)

/* implements the replace operation using a pre-computed hash value in sorted order using an extra comparison */
#define HASH_REPLACE_BYHASHVALUE_INORDER(hh, head, fieldname, keylen_in, hashval, add, replaced, cmpfcn)
do {
    replaced = NULL;
    HASH_FIND_BYHASHVALUE(hh, head, &(add->fieldname), keylen_in, hashval, replaced); /* uses pre-computed hash value and the key to search the hash table. if found, then assigned to 'replaced' */
    if (replaced) {
        HASH_DELETE(hh, head, replaced);
    }
    HASH_ADD_KEYPTR_BYHASHVALUE_INORDER(hh, head, &(add->fieldname), keylen_in, hashval, add, cmpfcn);
} while (0)

#define HASH_REPLACE_BYHASHVALUE(hh, head, fieldname, keylen_in, hashval, add, replaced)
do {
    replaced = NULL;
    HASH_FIND_BYHASHVALUE(hh, head, &(add->fieldname), keylen_in, hashval, replaced);
    if(replaced) {
        HASH_DELETE(hh, head, replaced);
    }
    HASH_ADD_KRYPTR_BTHASHVALUE(hh, head, &(add->fieldname), keylen_in, hashval, add);
} while (0)

#define HASH_REPLACE(hh, head, fieldname, keylen_in, add, replaced)
do {
    unsigned _hr_hashv;
    HASH_VALUE(&(add->fieldname), keylen_in, _hr_hashv);
    HASH_REPLACE_BYHASHVALUE(hh, head, fieldname, keylen_in, _hr_hashv, add, replaced);
} while (0)

#define HASH_REPLACE_INORDER(hh, head, fieldname, keylen_in, add, replaced, cmpfcn)
do {
    unsigned _hr_hashv;
    HASH_VALUE(&(add->fieldname), keylen_in, _hr_hashv);
    HASH_REPLACE_BYHASHVALUE_INORDER(hh, head, fieldname, keylen_in, _hs_hashv, add, replaced, cmpfcn);
} while (0)

/* it appends a new element to the end of the application-order linked list maintained by uthash
   it updates both the new element's pointer and hash table's tail pointer*/
#define HASH_APPEND_LIST(hh, head, add) 
do {
    add->hh.next = NULL; 
    add->hh.prev = ELMT_FROM_HH(head->hh.tbl, head->hh.tbl->tail); /* calculates the pointer to its current tail element */
    head->hh.tbl->tail->next = add; /* updates the tail element's next pointer to the new element */
    head->hh.tbl->tail = &(add->hh); /* hash table's tail pointer is updated to reference the new element's hash handle */
} while (0)

#define HASH_AKBI_INNER_LOOP(hh,head,add,cmpfcn)
do {
    
} while (0)

/*    IMPORTANT STRUCTURES    */

typedef struct {
    struct UT_hash_handle *hh_head;
    unsigned count;

    unsigned expand_mult;
} UT_hash_bucket;

#define HASH_SIGNATURE 0xa0111fefu
#define HASH_BLOOM_SIGNATURE 0xb12220f9u

typedef struct {
    UT_hash_bucket *buckets;
    unsigned num_buckets;
    unsigned log2_num_buckets;
    unsigned num_items;
    struct UT_hash_htblandle *tail;
    ptrdiff_t hho;

    unsigned ideal_chain_maxlen;

    unsigned nonideal_items;

    unsigned nonideal_items;

    unsigned ineff_expands, noexpand;

    uint32_t signature;

#ifdef HASH_BLOOM
    uint32_t bloom_sig;
    uint64_t *bloom_bv;
    uint8_t bloom_nbits;
#endif

} UT_hash_table;

typedef struct {
    struct UT_hash_table *tbl;
    void *prev;
    void *next;
    struct UT_hash_handle *hh_prev;
    struct UT_hash_handle *hh_next;
    const void *key;
    unsigned keylen;
    unsigned hashv;
} UT_hash_handle;

#endif /* UTHASH_H */