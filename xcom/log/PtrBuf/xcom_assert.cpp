//
//  xcom_assert.cpp
//  PtrBuf
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//



#ifdef NO_ASSERT
#else
#include "xcom_assert.h"
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#include "xcom_log_delc.h"
#include "xcom_compiler_def.h"

#ifdef ANDROID
#include "callstack.h"
#endif

#ifndef XCOM_LOG_TAG
#define XCOM_LOG_TAG ""
#endif

#if defined(__APPLE__) && (defined(NDEBUG))
void __assert_rtn(const char *, const char *, int, const char *) __dead2;
#endif

#ifdef WIN32
#define __assert(__Expression, __FILE, __LINE) (void)((_assert(__Expression, __FILE, __LINE), 0) )
#define snprintf _snprintf
#endif

#ifdef DEBUG
static int sg_enable_assert = 1;
#else
static int sg_enable_assert = 0;
#endif

void xcom_enable_assert() {
    sg_enable_assert = 1;
}

void xcom_disable_assert() {
    sg_enable_assert = 0;
}

int xcom_is_assert_enable() {
    return sg_enable_assert;
}

XCOM_EXPORT_FUNC void xcom_assert(const char *pfile, int line, const char *pfunc, const char *pexpression) {
    xcom_log_item info = {xcom_log_level_fatal};
    char assertlog[4096] = {'\0'};
    int offset = 0;
    
    offset += snprintf(assertlog, sizeof(assertlog), "[ASSERT(%s)]", pexpression);
    
#ifdef ANDROID
    android_callstack(assertlog+offset, sizeof(assertlog)-offset);
#endif
    
    info.level = xcom_log_level_fatal;
    info.tag = XCOM_LOG_TAG;
    info.file_name = pfile;
    info.func_name = pfunc;
    info.line = line;
    gettimeofday(&info.timeval, NULL);
    info.pid = xcom_log_get_pid();
    info.tid = xcom_log_get_tid();
    info.maintid = xcom_log_get_main_tid();
    
    xcom_log_write(&info, assertlog);
    
    if (xcom_is_assert_enable()) {
#if defined(ANDROID) //&& (defined(DEBUG))
        raise(SIGTRAP);
        __assert2(pfile, line, pfunc, pexpression);
#endif
        
#if defined(__APPLE__) //&& (defined(DEBUG))
        __assert_rtn(pfunc, pfile, line, pexpression);
#endif
    }
}

void xcom_assertv2(const char *pfile, int line, const char *pfunc, const char *pexpression, const char *format, va_list list) {
    char assertlog[4096] = {'\0'};
    xcom_log_item info = {xcom_log_level_fatal};
    int offset = 0;
    
    offset += snprintf(assertlog, sizeof(assertlog), "[ASSERT(%s)]", pexpression);
    offset += vsnprintf(assertlog + offset, sizeof(assertlog) - offset, format, list);
    
#ifdef ANDROID
    android_callstack(assertlog+offset, sizeof(assertlog)-offset);
#endif
    
    info.level = xcom_log_level_fatal;
    info.tag = XCOM_LOG_TAG;
    info.file_name = pfile;
    info.func_name = pfunc;
    info.line = line;
    gettimeofday(&info.timeval, NULL);
    info.pid = xcom_log_get_pid();
    info.tid = xcom_log_get_tid();
    info.maintid = xcom_log_get_main_tid();
    
    xcom_log_write(&info, assertlog);
    
    if (xcom_is_assert_enable()) {
#if defined(ANDROID) //&& (defined(DEBUG))
        raise(SIGTRAP);
        __assert2(pfile, line, pfunc, pexpression);
#endif
        
#if defined(__APPLE__) //&& (defined(DEBUG))
        __assert_rtn(pfunc, pfile, line, pexpression);
#endif
        
#if defined(WIN32) //&& (defined(DEBUG))
        __assert(pexpression, pfile, line);
#endif
    }
}

void
xcom_assert2(const char *pfile, int line, const char *pfunc, const char *pexpression, const char *format, ...) {
    va_list valist;
    va_start(valist, format);
    xcom_assertv2(pfile, line, pfunc, pexpression, format, valist);
    va_end(valist);
}

#endif
