//
//  xcom_log_delc.c
//  PtrBuf
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#include "xcom_log_delc.h"
#include <stdio.h>

#include "xcom_compiler_def.h"
#include <unistd.h>
// 实现
XCOM_WEAK_FUNC xcom_log_level __xcom_log_get_log_level(void);
XCOM_WEAK_FUNC void __xcom_log_set_log_level(xcom_log_level _level);
XCOM_WEAK_FUNC int  __xcom_log_is_enabled_for_level(xcom_log_level _level);
XCOM_WEAK_FUNC xcom_log_append_log_func __xcom_log_set_append_log_func(xcom_log_append_log_func appender);
XCOM_WEAK_FUNC void __xcom_log_write(const xcom_log_item* _info, const char* _log);
XCOM_WEAK_FUNC void __xcom_log_vprint(const xcom_log_item* _info, const char* _format, va_list _list);

XCOM_WEAK_FUNC void __xcom_log_assert_p(const xcom_log_item* _info, const char* _expression, const char* _format, va_list _list);
XCOM_WEAK_FUNC void __xcom_log_assert(const xcom_log_item* _info, const char* _expression, const char* _log);

#ifndef WIN32
XCOM_WEAK_FUNC const char* txf_logger_dump(const void *_dumpbuffer, size_t _len) { return "";}
#endif

//=================================================
// c func impl

#ifndef USING_XLOG_WEAK_FUNC
static xcom_log_level gs_level = xcom_log_level_none;
static xcom_log_append_log_func gs_appender = NULL;

xcom_log_level   __xcom_log_get_log_level() {return gs_level;}
void        __xcom_log_set_log_level(xcom_log_level _level){ gs_level = _level;}
int         __xcom_log_is_enabled_for_level(xcom_log_level _level) {return gs_level <= _level;}

xcom_log_append_log_func __xcom_log_set_append_log_func(xcom_log_append_log_func _appender)  {
    xcom_log_append_log_func old_appender = gs_appender;
    gs_appender = _appender;
    return old_appender;
}

void __xcom_log_write(const xcom_log_item *ainfo, const char *alog) {
    
    if (!gs_appender) {
        return;
    }
    
    if (ainfo && -1 == ainfo->pid && -1 == ainfo->tid && -1 == ainfo->maintid)
    {
        xcom_log_item* info = (xcom_log_item*)ainfo;
        info->pid = xcom_log_get_pid();
        info->tid = xcom_log_get_tid();
        info->maintid = xcom_log_get_main_tid();
    }
    
    if (NULL == alog) {
        if (ainfo) {
            xcom_log_item *info = (xcom_log_item *)ainfo;
            info->level = xcom_log_level_fatal;
        }
        gs_appender(ainfo, "NULL == _log");
    } else {
        gs_appender(ainfo, alog);
    }
}

void __xcom_log_vprint(const xcom_log_item *ainfo, const char *aformat, va_list alist) {
    if (NULL == aformat) {
        xcom_log_item* info = (xcom_log_item *)ainfo;
        info->level = xcom_log_level_fatal;
        __xcom_log_write(ainfo, "NULL == _format");
    } else {
        char temp[4096] = {'\0'};
        vsnprintf(temp, 4096, aformat, alist);
        __xcom_log_write(ainfo, temp);
    }
}

extern void xcom_assertv2(const char *_pfile, int _line, const char *_pfunc, const char *_pexpression, const char *_format, va_list _list);

void __xcom_log_assert_p(const xcom_log_item *ainfo, const char *aexpression, const char *aformat, va_list alist) {
    xcom_assertv2(ainfo->file_name, ainfo->line, ainfo->func_name, aexpression, aformat, alist);
}

extern void xcom_assert2(const char *_pfile, int _line, const char *_pfunc, const char *_pexpression, const char *_format, ...);

void __xcom_log_assert(const xcom_log_item *ainfo, const char *aexpression, const char *alog) {
    xcom_assert2(ainfo->file_name, ainfo->line, ainfo->func_name, aexpression, alog);
}
#endif

//=================================================
// header func impl

xcom_log_level xcom_log_get_log_level()
{
    if (NULL == &__xcom_log_get_log_level) {
        return xcom_log_level_none;
    }
    
    return __xcom_log_get_log_level();
}

void xcom_log_set_log_level(xcom_log_level level){
    if (NULL != &__xcom_log_set_log_level) {
        __xcom_log_set_log_level(level);
    }
}

int xcom_log_is_enabled_for_level(xcom_log_level level) {
    if (NULL == &__xcom_log_is_enabled_for_level) {
        return 0;
    }
    return __xcom_log_is_enabled_for_level(level);
    
}

xcom_log_append_log_func xcom_log_set_append_log_func(xcom_log_append_log_func appender) {
    if (NULL == &__xcom_log_set_append_log_func) {
        return NULL;
    }
    return __xcom_log_set_append_log_func(appender);
}

void xcom_log_write(const xcom_log_item *info, const char *log) {
    if (NULL != &__xcom_log_write) {
        __xcom_log_write(info, log);
    }
}

void xcom_log_vprint(const xcom_log_item *info, const char *format, va_list list) {
    if (NULL != &__xcom_log_vprint) {
        xcom_log_vprint(info, format, list);
    }
}

void xcom_log_print(const xcom_log_item *info, const char *format, ...) {
    if (NULL == &__xcom_log_vprint) {
        return;
    }
    
    va_list valist;
    va_start(valist, format);
    __xcom_log_vprint(info, format, valist);
    va_end(valist);
}


void xcom_log_assert_p(const xcom_log_item *info, const char *expression, const char *format, ...) {
    if (NULL == &__xcom_log_assert_p) {
        return;
    }
    
    va_list valist;
    va_start(valist, format);
    __xcom_log_assert_p(info, expression, format, valist);
    va_end(valist);
}

void xcom_log_assert(const xcom_log_item *info, const char *expression, const char *log) {
    if (NULL != &__xcom_log_assert) {
        __xcom_log_assert(info, expression, log);
    }
}


//====================================
// 只作默认实现

intmax_t xcom_log_get_pid()
{
//    static intmax_t pid = getpid();
//    return pid;
    return 0;
}

intmax_t xcom_log_get_tid()
{
    return 0;
}

intmax_t xcom_log_get_main_tid()
{
    return 0;
}




