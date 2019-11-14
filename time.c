int64_t gettime_ms()
{
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);

    return ((int64_t)(tp.tv_sec * 1000000000ll + tp.tv_nsec))/1000000;
}

#define DBG_TIME_START()  { int64_t start = 0,end = 0;start = gettime_ms();
#define DBG_TIME_COST()   end = gettime_ms();LOGI("cost:%"PRId64"", end-start); }
