int64_t gettime_ms()
{
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);

    return ((int64_t)(tp.tv_sec * 1000000000ll + tp.tv_nsec))/1000000;
}
