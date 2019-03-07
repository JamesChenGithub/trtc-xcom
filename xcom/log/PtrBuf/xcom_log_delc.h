//
//  xcom_log_delc.h
//  PtrBuf
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#ifndef xcom_log_delc_h
#define xcom_log_delc_h

#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef enum {
        xcom_log_level_all = 0,
        xcom_log_level_verbose = 0,
        xcom_log_level_debug,       // Detailed information on the flow through the system.
        xcom_log_level_info,        // Interesting runtime events (startup/shutdown), should be conservative and keep to a minimum.
        xcom_log_level_warn,        // Other runtime situations that are undesirable or unexpected, but not necessarily "wrong".
        xcom_log_level_err,         // Other runtime errors or unexpected conditions.
        xcom_log_level_fatal,       // Severe errors that cause premature termination.
        xcom_log_level_none,        // Special level used to disable all log messages.
    } xcom_log_level;
    
    typedef struct xcom_log_item_t {
        xcom_log_level level;       
        const char *tag;
        const char *file_name;
        const char *func_name;
        int line;
        
        struct timeval timeval;
        intmax_t pid;
        intmax_t tid;
        intmax_t maintid;
    } xcom_log_item;
    
    
    // get the cur process id
    extern intmax_t xcom_log_get_pid(void);
    // get the cur thread id
    extern intmax_t xcom_log_get_tid(void);
    // get the cur main thread id
    extern intmax_t xcom_log_get_main_tid(void);

    // delc the append log func
    typedef void (*xcom_log_append_log_func)(const xcom_log_item *info, const char *log);

    extern const char *xcom_log_dump(const void *dumpbuffer, size_t len);
    
    // get the log level
    xcom_log_level xcom_log_get_log_level(void);
    // set the log level
    void xcom_log_set_log_level(xcom_log_level level);
    // is enable for log level
    int xcom_log_is_enabled_for_level(xcom_log_level level);
    // send the append log func
    xcom_log_append_log_func xcom_log_set_append_log_func(xcom_log_append_log_func appender);
    
    // xcom assert log
#ifdef __GNUC__
    __attribute__((__format__(printf, 3, 4)))
#endif
    void xcom_log_assert_p(const xcom_log_item *info, const char *expression, const char *format, ...);
    
    void xcom_log_assert(const xcom_log_item *info, const char *expression, const char *log);
    
    // write log to cache
#ifdef __GNUC__
    __attribute__((__format__(printf, 2, 0)))
#endif
    void xcom_log_vprint(const xcom_log_item *info, const char *format, va_list list);
    
#ifdef __GNUC__
    __attribute__((__format__(printf, 2, 3)))
#endif
    void xcom_log_print(const xcom_log_item *info, const char *format, ...);
    
    void xcom_log_write(const xcom_log_item *info, const char *log);
    
#ifdef __cplusplus
}
#endif

#endif /* xcom_log_delc_h */
