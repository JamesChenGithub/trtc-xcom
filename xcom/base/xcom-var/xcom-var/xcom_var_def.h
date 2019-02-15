//
//  xcom_var_def.h
//  xcom-var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#ifndef xcom_var_def_h
#define xcom_var_def_h

#include <string>

namespace xcom {
#ifdef __cplusplus
    extern "C" {
#endif
        class xcom_var;
        typedef std::shared_ptr<xcom_var> xcom_var_ptr;
        typedef std::vector<std::pair<std::string, xcom_var_ptr>> xcom_var_dict;
        typedef std::vector<xcom_var_ptr> xcom_var_array;
        typedef xcom_var (*xcom_var_callback)(xcom_var);
        
//#define printf //printf
#ifdef __cplusplus
    }
#endif
}

#endif /* xcom_var_def_h */
