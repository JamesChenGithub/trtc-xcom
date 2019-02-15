//
//  xcom_var_value.h
//  xcom-var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#ifndef xcom_var_value_h
#define xcom_var_value_h

#include <string>
#include <vector>
#include "xcom_var_def.h"
#include "xcom_var_type.h"
#include "xcom_var_func.h"

namespace xcom {
#ifdef __cplusplus
    extern "C" {
#endif
        typedef union xcom_var_value
        {
            bool            bool_val;
            int8_t          int8_val;
            uint8_t         uint8_val;
            int16_t         int16_val;
            uint16_t        uint16_val;
            int32_t         int32_val;
            uint32_t        uint32_val;
            int64_t         int64_val;
            uint64_t        uint64_val;
            float           float_val;
            double          double_val;
            std::string     string_val;
            void            *ref_val;
            // 需要分配内存
            xcom_var_buf    *buf_val;
            xcom_var_map    *map_val;
            xcom_var_array  *array_val;
            xcom_var_dict   *dict_val;
            xcom_var_func   *func_val;
            xcom_var_ptr    vptr_val;
        public:
            xcom_var_value();
            ~xcom_var_value();
            
        }xcom_var_value;
#ifdef __cplusplus
    }
#endif
}

#endif /* xcom_var_value_h */
