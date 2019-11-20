void sd_write_full()
{
    int i, start, end;
    int time = START_TIME - MAX_TS_COUNT*10;
    char *ts_buf = NULL;
    int size = 0;

    read_file_to_buf("./test.ts", &ts_buf, &size);
    start = gettime_ms();
    for (i=0; i<MAX_TS_COUNT; i++) {
        qntsm_save_ts(ts_buf, size, time+i*10, time+(i+1)*10);
        printf("\r%d/%d %d%%", i, MAX_TS_COUNT, i/MAX_TS_COUNT);
        fflush(stdout);
    }
    end = gettime_ms();
    LOGI("gen segment db cost:%d ms", end-start);
}
