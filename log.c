void log_out(int level,
        void (*param_cb)(FILE ***fp, char **env, int *console_enable),
        const char *file,
        const char *function, 
        int line,
        const char *fmt,
        ...)
{
    char buf[1024] = {0};
    va_list arg;
    time_t t = time(NULL);
    struct tm *tm_now = localtime(&t);
    FILE **fp = NULL;
    char *logfile = NULL;
    char *env = NULL;
    int console_enable = 0;

    if (g_ts_mgr.log_level > level)
        return;

    if (param_cb)
        param_cb(&fp, &env, &console_enable);
    logfile = getenv(env);
    if (logfile && fp && !*fp) {
        *fp = fopen(logfile, "a");
        if (!fp) {
            printf("open log file:%s error", logfile);
        }
    }
    strftime(buf, sizeof(buf), "[%Y-%m-%d %H:%M:%S]", tm_now);
    sprintf(buf+strlen(buf), " %s:%d(%s)$ ", file, line, function);
    va_start(arg, fmt);
    vsprintf(buf+strlen(buf), fmt, arg);
    va_end(arg);
    strcat(buf, "\n");
    if (*fp) {
        fwrite(buf, strlen(buf), 1, *fp);
        fflush(*fp);
    }
    if (console_enable) {
        if (level == LOG_ERR)
            printf("\e[0;31m%s\e[0m", buf);
        else
            printf("%s", buf);
    }
}
