struct malloc_state{
    _libc_lock_define (, mutex);
    int flags;

    int have_fastchunks;
    mfastbinptr fastbinsY[NFASTBINS];
    mchunkptr top;
    mchunkptr last_remainder;
    mchunkptr bins[NBINS * 2 - 2];
    unsigned int binmap[BINMAPSIZE];
    struct malloc_state *next;
    struct malloc_state *next_free;
    INTERNAL_SIZE_T attached_threads;
    INTERNAL_SIZE_T system_mem;
    INTERNAL_SIZE_T max_system_mem;
};
