void sd_write(int count)
{
    int i, start, end;
    int time = START_TIME - MAX_TS_COUNT*10;
    uint8_t *ts_buf = NULL;
    int size = 0;
    int speed = 0;

    read_file_to_buf("./test.ts", (char **)&ts_buf, &size);
    start = gettime_ms();
    for (i=0; i<count; i++) {
        if (qntsm_save_ts(ts_buf, size, time+i*INTERVAL, time+(i+1)*INTERVAL) < 0) {
            LOGI("finished");
            return;
        }
        end = gettime_ms();
        speed = i/((end-start > 1000?end-start:1000)/1000);
        if (speed == 0)
            speed = 1;
        printf("\r%d/%d %d%% %ds %dts/s need:%d s", i, MAX_TS_COUNT, i*100/MAX_TS_COUNT, (end-start)/1000, speed, (MAX_TS_COUNT - i)/speed);
        fflush(stdout);
    }
    LOGI("gen segment db cost:%d ms", end-start);
}
