//
//  xcom_var_type.cpp
//  xcom_var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#include "xcom_var_type.h"


namespace xcom {
#ifdef __cplusplus
    extern "C" {
#endif
        
        const char *xcom_var_type_string(xcom_var_type type)
        {
            switch(type)
            {
                case xcom_vtype_null: return "NULL";
                case xcom_vtype_bool: return "bool";
                case xcom_vtype_int8: return "int8";
                case xcom_vtype_uint8: return "uint8";
                case xcom_vtype_int16: return "int16";
                case xcom_vtype_uint16: return "uint16";
                case xcom_vtype_int32: return "int32";
                case xcom_vtype_uint32: return "uint32";
                case xcom_vtype_int64: return "int64";
                case xcom_vtype_uint64: return "uint64";
                case xcom_vtype_float: return "float";
                case xcom_vtype_double: return "double";
                case xcom_vtype_string: return "string";
                case xcom_vtype_ref:  return "ref";
                case xcom_vtype_bytes: return "byte";
                case xcom_vtype_map: return "map";
                case xcom_vtype_array: return "array";
                case xcom_vtype_dict: return "dict";
                case xcom_vtype_func: return "func";
                case xcom_vtype_vptr : return "vptr";
            }
            return " ";
        }
        
        
        xcom_var_buf::xcom_var_buf() {
            this->buf = nullptr;
            this->buf = 0;
        }
        
        xcom_var_buf::xcom_var_buf(const void *buf, uint32_t len) {
            this->buf = nullptr;
            this->buf = 0;
            
            if(buf && len > 0)
            {
                void *abuf = malloc(len);
                if (abuf)
                {
                    memcpy(abuf, buf, len);
                    this->buf = abuf;
                    this->len = len;
                }
            }
        }
        
        xcom_var_buf::~xcom_var_buf()
        {
            if (this->buf)
            {
                free(buf);
                this->buf = nullptr;
                this->len = 0;
            }
        }
#ifdef __cplusplus
    }
#endif
}
