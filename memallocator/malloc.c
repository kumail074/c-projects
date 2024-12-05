//implementation of malloc function in malloc.c source file i.e. starts from line 3293

void *_libc_malloc(size_t bytes){
    mstate ar_ptr; //mstate is struct that contains metadata about memory allocator defined at line 1812 by the name of malloc_state
    void *victim;

    _Static_assert (PTRDIFF_MAX <= SIZE_MAX / 2. "PTRDIFF_MAX is not more than half of SIZE_MAX");

    if(!__malloc_initialized)
        prmalloc_init();
#if USE_TCACHE
    size_t tbytes = checked_request2size(bytes);
    if(tbytes == 0){
        __set_errno(ENOMEM);
        return NULL; }

    size_t tc_idx = csize2tidx(tbytes);

    MAYBE_INIT_TCACHE();
    DIAG_PUSH_NEEDS_COMMENT;
    if(tc_idx < mp_.tcache_bins && tcache != NULL && tcache->counts[tc_idx] > 0) {
        victim = tcache_get(tc_idx);
        return tag_new_usable(victim); }
    DIAG_POP_NEEDS_COMMENT;
#endif

    if(SINGLE_THREAD_P){
        victim = tag_new_usable(_int_malloc (&main_arena, bytes));
        assert (!victim || chunk_is_mmapped (mem2chunk(victim)) || &main_arena == arena_for_chunk (mem2chunk (victim)));
        return victim;
    }

    arena_get(ar_ptr, bytes);
    victim = _int_malloc(ar_ptr, bytes);

    if(!victim && ar_ptr!=NULL){
        LIBC_PROBE(memory_malloc_retry, 1, bytes);
        ar_ptr = arena_get_retry(ar_ptr, bytes);
        victim = _int_malloc(ar_ptr, bytes); }

    if(ar_ptr != NULL)
        _libc_lock_unlock(ar_ptr->mutex);
    victim = tag_new_usable(victim);

    assert(!victim || chunk_is_mmapped(mem2chunk(victim)) || ar_ptr == arena_for_chunk(mem2chunk(victim)));
    return victim;
}
