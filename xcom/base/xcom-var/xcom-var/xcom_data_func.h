//
//  xcom_var_func.h
//  xcom-var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#ifndef xcom_data_func_h
#define xcom_data_func_h

#include "xcom_var_def.h"

namespace xcom
{
#ifdef __cplusplus
    extern "C" {
#endif
        
        class xcom_data_func
        {
        public:
            xcom_callback func;
            xcom_data     *funcpar;
            
        public:
            xcom_data_func();
            xcom_data_func(const xcom_data_func &vf);
            xcom_data_func(xcom_data_func &&vf);
            xcom_data_func(const xcom_callback callback);
            xcom_data_func(const xcom_callback callback, const xcom_data &par);
            xcom_data_func(const xcom_callback callback, xcom_data &&par);
            ~xcom_data_func();
            
            xcom_data_func &operator =(const xcom_data_func &vf);
            xcom_data_func &operator =(xcom_data_func &&vf);
            
            operator xcom_data() const;
            xcom_data call();
            
            
            const char *to_var_json() const;
            const char *to_json() const;
        };
        
#ifdef __cplusplus
    }
#endif
}

#endif /* xcom_data_func_h */
