/**
* @file dbg.h
* @author rigensen
* @brief 
* @date 四 10/17 15:51:28 2019
*/


extern int g_log_level;

#define LOG_COMMON( module, level_str, level, args...) do { \
   if ( level >= g_log_level ) { \
       printf("| %20s | %5s | %s:%d(%s)# ", module, level_str, __FILE_NAME__, __LINE__, __FUNCTION__); \
       printf(args); \
       printf("\n"); \
   } \
} while(0)

#define LOGI(module, args...) LOG_COMMON( module, "INFO", LOG_LEVEL_INFO, args)
#define LOGD(module, args...) LOG_COMMON( module, "DEBUG", LOG_LEVEL_DEBUG, args)
#define LOGT(module, args...) LOG_COMMON( module, "TRACE", LOG_LEVEL_TRACE, args)
#define LOGW(module, args...) LOG_COMMON( module, "WARN", LOG_LEVEL_WARN, args)

#define LOGE(module, args...) do { \
   if (  LOG_LEVEL_ERROR >= g_log_level ) { \
       printf( RED"| %20s | ERROR | %s:%d(%s)# "NONE, module, __FILE_NAME__, __LINE__, __FUNCTION__); \
       printf(args); \
       printf("\n"); \
   } \
} while(0)


