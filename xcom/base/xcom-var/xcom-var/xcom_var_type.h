//
//  xcom_var_type.hpp
//  xcom_var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#ifndef var_type_h
#define var_type_h



#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

#ifdef __cplusplus
namespace xcom
{
    extern "C" {
#endif
        
        typedef enum xcom_var_type {
            xcom_vtype_null      = 0,        // null or undefined
            xcom_vtype_bool      = 'b',      // bool
            xcom_vtype_int8      = 'Y',      // int8
            xcom_vtype_uint8     = 'y',      // uint8
            xcom_vtype_int16     = 'n',      // int16
            xcom_vtype_uint16    = 'N',      // uint16
            xcom_vtype_int32     = 'i',      // int32
            xcom_vtype_uint32    = 'I',      // uint32
            xcom_vtype_int64     = 'x',      // int64
            xcom_vtype_uint64    = 'X',      // uint64
            xcom_vtype_float     = 'f',      // float
            xcom_vtype_double    = 'D',      // double
            xcom_vtype_string    = 'c',      // string
            xcom_vtype_ref       = '&',      // outside ptr ref: manage by outside
            xcom_vtype_bytes     = 'm',      // buffer
            xcom_vtype_array     = '[',      // array
            xcom_vtype_dict      = '{',      // dictionary
            xcom_vtype_func      = 'F',      // var_callback : var (*var_callback)(const var &);
            xcom_vtype_vptr      = 'v',      // used by xcom_vtype_array/xcom_vtype_dict
        } xcom_var_type;
        
        const char *xcom_var_type_string(xcom_var_type type);
        
        typedef struct xcom_var_buf
        {
        public:
            void        *buf;
            uint32_t    len;
            
        public:
            xcom_var_buf();
            xcom_var_buf(const void *buf, uint32_t len);
            ~xcom_var_buf();
            const char *to_var_json() const
            {
                char buf[128];
                sprintf(buf, "{\"buf\" : \"%p\", \"len\" : \"%u\"}", buf, len);
                std::string json = buf;
                return json.c_str();
            }
            
        }xcom_var_buf;
        
#ifdef __cplusplus
    }
}
#endif

#endif /* var_type_hpp */
