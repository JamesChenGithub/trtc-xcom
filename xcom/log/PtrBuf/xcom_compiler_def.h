//
//  xcom_compiler_def.h
//  PtrBuf
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//


#ifndef XCOM_COMPILER_DEF_H
#define XCOM_COMPILER_DEF_H

#if defined(__GNUC__)
#define XCOM_WEAK_FUNC      __attribute__((weak))
#elif defined(_MSC_VER) && !defined(_LIB)
#define XCOM_WEAK_FUNC      /*__declspec(selectany)*/
#else
#define XCOM_WEAK_FUNC
#endif

#if defined(__GNUC__)
#define XCOM_EXPORT_FUNC __attribute__ ((visibility ("default")))
#elif defined(_MSC_VER)
#define XCOM_EXPORT_FUNC __declspec(dllexport)
#else
#error "export"
#endif

#ifndef VARIABLE_IS_NOT_USED
#ifdef __GNUC__
#define VARIABLE_IS_NOT_USED __attribute__ ((unused))
#else
#define VARIABLE_IS_NOT_USED
#endif
#endif

#endif /* XCOM_COMPILER_DEF_H */
