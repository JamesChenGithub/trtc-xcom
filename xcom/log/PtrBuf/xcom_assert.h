//
//  xcom_assert.h
//  PtrBuf
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#ifndef xcom_assert_h
#define xcom_assert_h

#ifdef NO_XCOM_ASSERT

#define XCOM_ASSERT(e)
#define XCOM_ASSERT2(e, fmt, ...)
#define XCOM_ASSERTV2(e, fmt, valist)

#define    XCOM_ASSERT_RETURN(e)
#define    XCOM_ASSERT2_RETURN(e, fmt, ...)
#define    XCOM_ASSERTV2_RETURN(e, fmt, valist)

#else

#include <sys/cdefs.h>
#include <stdarg.h>

#if (!__ISO_C_VISIBLE >= 1999)
#error "C Version < C99"
# endif

#define    XCOM_ASSERT(e)                ((e) ? (void)0 : xcom_assert(__FILE__, __LINE__, __func__, #e))
#define    XCOM_ASSERT2(e, fmt, ...)     ((e) ? (void)0 : xcom_assert2(__FILE__, __LINE__, __func__, #e, fmt, ##__VA_ARGS__))
#define    XCOM_ASSERTV2(e, fmt, valist) ((e) ? (void)0 : xcom_assertv2(__FILE__, __LINE__, __func__, #e, fmt, valist))

#define    XCOM_ASSERT_RETURN(e)                do{((e) ? (void)0 : xcom_assert(__FILE__, __LINE__, __func__, #e)); return;}while(0)
#define    XCOM_ASSERT2_RETURN(e, fmt, ...)     do{((e) ? (void)0 : xcom_assert2(__FILE__, __LINE__, __func__, #e, fmt, ##__VA_ARGS__)); return;}while(0)
#define    XCOM_ASSERTV2_RETURN(e, fmt, valist) do{((e) ? (void)0 : xcom_assertv2(__FILE__, __LINE__, __func__, #e, fmt, valist)); return;}while(0)

extern "C" {
    void xcom_enable_assert();
    void xcom_disable_assert();
    int xcom_is_assert_enable();
    
    __attribute__((__nonnull__(1, 3, 4)))
    void xcom_assert(const char *, int, const char *, const char *);
    __attribute__((__nonnull__(1, 3, 4, 5))) __attribute__((__format__(printf, 5, 6)))
    void xcom_assert2(const char *, int, const char *, const char *, const char *, ...);
    __attribute__((__nonnull__(1, 3, 4, 5))) __attribute__((__format__(printf, 5, 0)))
    void xcom_assertv2(const char *, int, const char *, const char *, const char *, va_list);
}

#endif

#endif /* xcom_assert_h */
