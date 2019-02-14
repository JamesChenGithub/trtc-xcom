//
//  xcom_var_func.hpp
//  xcom-var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#ifndef xcom_var_func_h
#define xcom_var_func_h

#include "xcom_var_def.h"
namespace xcom
{
#ifdef __cplusplus
    extern "C" {
#endif
        typedef struct xcom_var_func
        {
        public:
            xcom_var_callback       func;
            xcom_var_ptr            funcpar;
            
        public:
            xcom_var_func();
            xcom_var_func(const xcom_var_func &vf);
            xcom_var_func(xcom_var_func &&vf);
            xcom_var_func(xcom_var_callback callback, const xcom_var &par);
            xcom_var_func(xcom_var_callback callback, xcom_var &&par);
            ~xcom_var_func();
            
            xcom_var_func &operator =(const xcom_var_func &vf);
            xcom_var_func &operator =(xcom_var_func &&vf);
            operator xcom_var() const;
            const char *to_var_json() const;
            const char *to_json() const;
        }xcom_var_func;
        
#ifdef __cplusplus
    }
#endif
}

#endif /* xcom_var_func_h */
