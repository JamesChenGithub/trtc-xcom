//
//  xcom_data_func.h
//  xcom-var
//
//  Created by AlexiChen on 2019/2/15.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#ifndef xcom_data_func_h
#define xcom_data_func_h

#include "xcom_data.h"

namespace xcom
{
#ifdef __cplusplus
    extern "C" {
#endif
        typedef xcom_var (*xcom_var_callback)(xcom_var);
        class xcom_data_func
        {
        public:
            xcom_var_callback       func;
            xcom_var_ptr            funcpar;
            
        public:
            xcom_data_func();
            xcom_data_func(const xcom_var_func &vf);
            xcom_data_func(xcom_var_func &&vf);
            xcom_data_func(xcom_var_callback callback, const xcom_var &par);
            xcom_data_func(xcom_var_callback callback, xcom_var &&par);
            ~xcom_data_func();
            
            xcom_data_func &operator =(const xcom_var_func &vf);
            xcom_data_func &operator =(xcom_var_func &&vf);
            operator xcom_data() const;
            const char *to_var_json() const;
            const char *to_json() const;
        };
        
#ifdef __cplusplus
    }
#endif
}

#endif /* xcom_data_func_h */
