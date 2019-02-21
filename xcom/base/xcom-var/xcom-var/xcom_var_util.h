//
//  xcom_var_util.h
//  xcom-var
//
//  Created by AlexiChen on 2019/2/20.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#ifndef xcom_var_util_h
#define xcom_var_util_h

#include "xcom_var.h"

namespace xcom {
    template<class T, class U>
    auto xcom_add(T a, U b)->decltype(a+b)
    {
        return a+b;
    }
    
    template<class T, class U>
    auto xcom_dec(T a, U b)->decltype(a-b)
    {
        return a-b;
    }
    
    template<class T, class U>
    auto xcom_mul(T a, U b)->decltype(a*b)
    {
        return a*b;
    }
    
    template<class T, class U>
    auto xcom_div(T a, U b)->decltype(a/b)
    {
        return a/b;
    }
    

    //数值型 + - * /
#define xcom_num_base_opera(a, b, func) \
do{\
switch (a.type) {\
case xcom_vtype_bool:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(func(a.bool_val(), b.bool_val())); \
case xcom_vtype_int8:  return xcom_var(func(a.bool_val(), b.int8_val())); \
case xcom_vtype_uint8: return xcom_var(func(a.bool_val(), b.uint8_val())); \
case xcom_vtype_int16: return xcom_var(func(a.bool_val(), b.int16_val())); \
case xcom_vtype_uint16:return xcom_var(func(a.bool_val(), b.uint16_val())); \
case xcom_vtype_int32: return xcom_var(func(a.bool_val(), b.int32_val())); \
case xcom_vtype_uint32:return xcom_var(func(a.bool_val(), b.uint32_val())); \
case xcom_vtype_int64: return xcom_var(func(a.bool_val(), b.int64_val())); \
case xcom_vtype_uint64:return xcom_var(func(a.bool_val(), b.uint64_val())); \
case xcom_vtype_float: return xcom_var(func(a.bool_val(), b.float_val())); \
case xcom_vtype_double:return xcom_var(func(a.bool_val(), b.double_val())); \
break;\
default:\
break;\
}\
case xcom_vtype_int8:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(func(a.int8_val(), b.bool_val())); \
case xcom_vtype_int8:  return xcom_var(func(a.int8_val(), b.int8_val())); \
case xcom_vtype_uint8: return xcom_var(func(a.int8_val(), b.uint8_val())); \
case xcom_vtype_int16: return xcom_var(func(a.int8_val(), b.int16_val())); \
case xcom_vtype_uint16:return xcom_var(func(a.int8_val(), b.uint16_val())); \
case xcom_vtype_int32: return xcom_var(func(a.int8_val(), b.int32_val())); \
case xcom_vtype_uint32:return xcom_var(func(a.int8_val(), b.uint32_val())); \
case xcom_vtype_int64: return xcom_var(func(a.int8_val(), b.int64_val())); \
case xcom_vtype_uint64:return xcom_var(func(a.int8_val(), b.uint64_val())); \
case xcom_vtype_float: return xcom_var(func(a.int8_val(), b.float_val())); \
case xcom_vtype_double:return xcom_var(func(a.int8_val(), b.double_val())); \
break;\
default:\
break;\
}\
case xcom_vtype_uint8:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(func(a.uint8_val(), b.bool_val())); \
case xcom_vtype_int8:  return xcom_var(func(a.uint8_val(), b.int8_val())); \
case xcom_vtype_uint8: return xcom_var(func(a.uint8_val(), b.uint8_val())); \
case xcom_vtype_int16: return xcom_var(func(a.uint8_val(), b.int16_val())); \
case xcom_vtype_uint16:return xcom_var(func(a.uint8_val(), b.uint16_val())); \
case xcom_vtype_int32: return xcom_var(func(a.uint8_val(), b.int32_val())); \
case xcom_vtype_uint32:return xcom_var(func(a.uint8_val(), b.uint32_val())); \
case xcom_vtype_int64: return xcom_var(func(a.uint8_val(), b.int64_val())); \
case xcom_vtype_uint64:return xcom_var(func(a.uint8_val(), b.uint64_val())); \
case xcom_vtype_float: return xcom_var(func(a.uint8_val(), b.float_val())); \
case xcom_vtype_double:return xcom_var(func(a.uint8_val(), b.double_val())); \
break;\
default:\
break;\
}\
case xcom_vtype_int16:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(func(a.int16_val(), b.bool_val())); \
case xcom_vtype_int8:  return xcom_var(func(a.int16_val(), b.int8_val())); \
case xcom_vtype_uint8: return xcom_var(func(a.int16_val(), b.uint8_val())); \
case xcom_vtype_int16: return xcom_var(func(a.int16_val(), b.int16_val())); \
case xcom_vtype_uint16:return xcom_var(func(a.int16_val(), b.uint16_val())); \
case xcom_vtype_int32: return xcom_var(func(a.int16_val(), b.int32_val())); \
case xcom_vtype_uint32:return xcom_var(func(a.int16_val(), b.uint32_val())); \
case xcom_vtype_int64: return xcom_var(func(a.int16_val(), b.int64_val())); \
case xcom_vtype_uint64:return xcom_var(func(a.int16_val(), b.uint64_val())); \
case xcom_vtype_float: return xcom_var(func(a.int16_val(), b.float_val())); \
case xcom_vtype_double:return xcom_var(func(a.int16_val(), b.double_val())); \
break;\
default:\
break;\
}\
case xcom_vtype_uint16:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(func(a.uint16_val(), b.bool_val())); \
case xcom_vtype_int8:  return xcom_var(func(a.uint16_val(), b.int8_val())); \
case xcom_vtype_uint8: return xcom_var(func(a.uint16_val(), b.uint8_val())); \
case xcom_vtype_int16: return xcom_var(func(a.uint16_val(), b.int16_val())); \
case xcom_vtype_uint16:return xcom_var(func(a.uint16_val(), b.uint16_val())); \
case xcom_vtype_int32: return xcom_var(func(a.uint16_val(), b.int32_val())); \
case xcom_vtype_uint32:return xcom_var(func(a.uint16_val(), b.uint32_val())); \
case xcom_vtype_int64: return xcom_var(func(a.uint16_val(), b.int64_val())); \
case xcom_vtype_uint64:return xcom_var(func(a.uint16_val(), b.uint64_val())); \
case xcom_vtype_float: return xcom_var(func(a.uint16_val(), b.float_val())); \
case xcom_vtype_double:return xcom_var(func(a.uint16_val(), b.double_val())); \
break;\
default:\
break;\
}\
case xcom_vtype_int32:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(func(a.int32_val(), b.bool_val())); \
case xcom_vtype_int8:  return xcom_var(func(a.int32_val(), b.int8_val())); \
case xcom_vtype_uint8: return xcom_var(func(a.int32_val(), b.uint8_val())); \
case xcom_vtype_int16: return xcom_var(func(a.int32_val(), b.int16_val())); \
case xcom_vtype_uint16:return xcom_var(func(a.int32_val(), b.uint16_val())); \
case xcom_vtype_int32: return xcom_var(func(a.int32_val(), b.int32_val())); \
case xcom_vtype_uint32:return xcom_var(func(a.int32_val(), b.uint32_val())); \
case xcom_vtype_int64: return xcom_var(func(a.int32_val(), b.int64_val())); \
case xcom_vtype_uint64:return xcom_var(func(a.int32_val(), b.uint64_val())); \
case xcom_vtype_float: return xcom_var(func(a.int32_val(), b.float_val())); \
case xcom_vtype_double:return xcom_var(func(a.int32_val(), b.double_val())); \
break;\
default:\
break;\
}\
case xcom_vtype_uint32:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(func(a.uint32_val(), b.bool_val())); \
case xcom_vtype_int8:  return xcom_var(func(a.uint32_val(), b.int8_val())); \
case xcom_vtype_uint8: return xcom_var(func(a.uint32_val(), b.uint8_val())); \
case xcom_vtype_int16: return xcom_var(func(a.uint32_val(), b.int16_val())); \
case xcom_vtype_uint16:return xcom_var(func(a.uint32_val(), b.uint16_val())); \
case xcom_vtype_int32: return xcom_var(func(a.uint32_val(), b.int32_val())); \
case xcom_vtype_uint32:return xcom_var(func(a.uint32_val(), b.uint32_val())); \
case xcom_vtype_int64: return xcom_var(func(a.uint32_val(), b.int64_val())); \
case xcom_vtype_uint64:return xcom_var(func(a.uint32_val(), b.uint64_val())); \
case xcom_vtype_float: return xcom_var(func(a.uint32_val(), b.float_val())); \
case xcom_vtype_double:return xcom_var(func(a.uint32_val(), b.double_val())); \
break;\
default:\
break;\
}\
case xcom_vtype_int64:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(func(a.int64_val(), b.bool_val())); \
case xcom_vtype_int8:  return xcom_var(func(a.int64_val(), b.int8_val())); \
case xcom_vtype_uint8: return xcom_var(func(a.int64_val(), b.uint8_val())); \
case xcom_vtype_int16: return xcom_var(func(a.int64_val(), b.int16_val())); \
case xcom_vtype_uint16:return xcom_var(func(a.int64_val(), b.uint16_val())); \
case xcom_vtype_int32: return xcom_var(func(a.int64_val(), b.int32_val())); \
case xcom_vtype_uint32:return xcom_var(func(a.int64_val(), b.uint32_val())); \
case xcom_vtype_int64: return xcom_var(func(a.int64_val(), b.int64_val())); \
case xcom_vtype_uint64:return xcom_var(func(a.int64_val(), b.uint64_val())); \
case xcom_vtype_float: return xcom_var(func(a.int64_val(), b.float_val())); \
case xcom_vtype_double:return xcom_var(func(a.int64_val(), b.double_val())); \
break;\
default:\
break;\
}\
case xcom_vtype_uint64:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(func(a.uint64_val(), b.bool_val())); \
case xcom_vtype_int8:  return xcom_var(func(a.uint64_val(), b.int8_val())); \
case xcom_vtype_uint8: return xcom_var(func(a.uint64_val(), b.uint8_val())); \
case xcom_vtype_int16: return xcom_var(func(a.uint64_val(), b.int16_val())); \
case xcom_vtype_uint16:return xcom_var(func(a.uint64_val(), b.uint16_val())); \
case xcom_vtype_int32: return xcom_var(func(a.uint64_val(), b.int32_val())); \
case xcom_vtype_uint32:return xcom_var(func(a.uint64_val(), b.uint32_val())); \
case xcom_vtype_int64: return xcom_var(func(a.uint64_val(), b.int64_val())); \
case xcom_vtype_uint64:return xcom_var(func(a.uint64_val(), b.uint64_val())); \
case xcom_vtype_float: return xcom_var(func(a.uint64_val(), b.float_val())); \
case xcom_vtype_double:return xcom_var(func(a.uint64_val(), b.double_val())); \
break;\
default:\
break;\
}\
case xcom_vtype_float:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(func(a.float_val(), b.bool_val())); \
case xcom_vtype_int8:  return xcom_var(func(a.float_val(), b.int8_val())); \
case xcom_vtype_uint8: return xcom_var(func(a.float_val(), b.uint8_val())); \
case xcom_vtype_int16: return xcom_var(func(a.float_val(), b.int16_val())); \
case xcom_vtype_uint16:return xcom_var(func(a.float_val(), b.uint16_val())); \
case xcom_vtype_int32: return xcom_var(func(a.float_val(), b.int32_val())); \
case xcom_vtype_uint32:return xcom_var(func(a.float_val(), b.uint32_val())); \
case xcom_vtype_int64: return xcom_var(func(a.float_val(), b.int64_val())); \
case xcom_vtype_uint64:return xcom_var(func(a.float_val(), b.uint64_val())); \
case xcom_vtype_float: return xcom_var(func(a.float_val(), b.float_val())); \
case xcom_vtype_double:return xcom_var(func(a.float_val(), b.double_val())); \
break;\
default:\
break;\
}\
case xcom_vtype_double:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(func(a.double_val(), b.bool_val())); \
case xcom_vtype_int8:  return xcom_var(func(a.double_val(), b.int8_val())); \
case xcom_vtype_uint8: return xcom_var(func(a.double_val(), b.uint8_val())); \
case xcom_vtype_int16: return xcom_var(func(a.double_val(), b.int16_val())); \
case xcom_vtype_uint16:return xcom_var(func(a.double_val(), b.uint16_val())); \
case xcom_vtype_int32: return xcom_var(func(a.double_val(), b.int32_val())); \
case xcom_vtype_uint32:return xcom_var(func(a.double_val(), b.uint32_val())); \
case xcom_vtype_int64: return xcom_var(func(a.double_val(), b.int64_val())); \
case xcom_vtype_uint64:return xcom_var(func(a.double_val(), b.uint64_val())); \
case xcom_vtype_float: return xcom_var(func(a.double_val(), b.float_val())); \
case xcom_vtype_double:return xcom_var(func(a.double_val(), b.double_val())); \
break;\
default:\
break;\
}\
break;\
default:\
break;\
}\
}while(0)
    
    //数值型 模操作(mod)
#define xcom_num_mode_opera(a, b) \
do{\
switch (a.type) {\
case xcom_vtype_bool:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(a.bool_val()%b.bool_val()); \
case xcom_vtype_int8:  return xcom_var(a.bool_val()%b.int8_val()); \
case xcom_vtype_uint8: return xcom_var(a.bool_val()%b.uint8_val()); \
case xcom_vtype_int16: return xcom_var(a.bool_val()%b.int16_val()); \
case xcom_vtype_uint16:return xcom_var(a.bool_val()%b.uint16_val()); \
case xcom_vtype_int32: return xcom_var(a.bool_val()%b.int32_val()); \
case xcom_vtype_uint32:return xcom_var(a.bool_val()%b.uint32_val()); \
case xcom_vtype_int64: return xcom_var(a.bool_val()%b.int64_val()); \
case xcom_vtype_uint64:return xcom_var(a.bool_val()%b.uint64_val()); \
break;\
default:\
break;\
}\
case xcom_vtype_int8:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(a.int8_val()%b.bool_val()); \
case xcom_vtype_int8:  return xcom_var(a.int8_val()%b.int8_val()); \
case xcom_vtype_uint8: return xcom_var(a.int8_val()%b.uint8_val()); \
case xcom_vtype_int16: return xcom_var(a.int8_val()%b.int16_val()); \
case xcom_vtype_uint16:return xcom_var(a.int8_val()%b.uint16_val()); \
case xcom_vtype_int32: return xcom_var(a.int8_val()%b.int32_val()); \
case xcom_vtype_uint32:return xcom_var(a.int8_val()%b.uint32_val()); \
case xcom_vtype_int64: return xcom_var(a.int8_val()%b.int64_val()); \
case xcom_vtype_uint64:return xcom_var(a.int8_val()%b.uint64_val()); \
break;\
default:\
break;\
}\
case xcom_vtype_uint8:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(a.uint8_val()%b.bool_val()); \
case xcom_vtype_int8:  return xcom_var(a.uint8_val()%b.int8_val()); \
case xcom_vtype_uint8: return xcom_var(a.uint8_val()%b.uint8_val()); \
case xcom_vtype_int16: return xcom_var(a.uint8_val()%b.int16_val()); \
case xcom_vtype_uint16:return xcom_var(a.uint8_val()%b.uint16_val()); \
case xcom_vtype_int32: return xcom_var(a.uint8_val()%b.int32_val()); \
case xcom_vtype_uint32:return xcom_var(a.uint8_val()%b.uint32_val()); \
case xcom_vtype_int64: return xcom_var(a.uint8_val()%b.int64_val()); \
case xcom_vtype_uint64:return xcom_var(a.uint8_val()%b.uint64_val()); \
break;\
default:\
break;\
}\
case xcom_vtype_int16:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(a.int16_val()%b.bool_val()); \
case xcom_vtype_int8:  return xcom_var(a.int16_val()%b.int8_val()); \
case xcom_vtype_uint8: return xcom_var(a.int16_val()%b.uint8_val()); \
case xcom_vtype_int16: return xcom_var(a.int16_val()%b.int16_val()); \
case xcom_vtype_uint16:return xcom_var(a.int16_val()%b.uint16_val()); \
case xcom_vtype_int32: return xcom_var(a.int16_val()%b.int32_val()); \
case xcom_vtype_uint32:return xcom_var(a.int16_val()%b.uint32_val()); \
case xcom_vtype_int64: return xcom_var(a.int16_val()%b.int64_val()); \
case xcom_vtype_uint64:return xcom_var(a.int16_val()%b.uint64_val()); \
break;\
default:\
break;\
}\
case xcom_vtype_uint16:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(a.uint16_val()%b.bool_val()); \
case xcom_vtype_int8:  return xcom_var(a.uint16_val()%b.int8_val()); \
case xcom_vtype_uint8: return xcom_var(a.uint16_val()%b.uint8_val()); \
case xcom_vtype_int16: return xcom_var(a.uint16_val()%b.int16_val()); \
case xcom_vtype_uint16:return xcom_var(a.uint16_val()%b.uint16_val()); \
case xcom_vtype_int32: return xcom_var(a.uint16_val()%b.int32_val()); \
case xcom_vtype_uint32:return xcom_var(a.uint16_val()%b.uint32_val()); \
case xcom_vtype_int64: return xcom_var(a.uint16_val()%b.int64_val()); \
case xcom_vtype_uint64:return xcom_var(a.uint16_val()%b.uint64_val()); \
break;\
default:\
break;\
}\
case xcom_vtype_int32:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(a.int32_val()%b.bool_val()); \
case xcom_vtype_int8:  return xcom_var(a.int32_val()%b.int8_val()); \
case xcom_vtype_uint8: return xcom_var(a.int32_val()%b.uint8_val()); \
case xcom_vtype_int16: return xcom_var(a.int32_val()%b.int16_val()); \
case xcom_vtype_uint16:return xcom_var(a.int32_val()%b.uint16_val()); \
case xcom_vtype_int32: return xcom_var(a.int32_val()%b.int32_val()); \
case xcom_vtype_uint32:return xcom_var(a.int32_val()%b.uint32_val()); \
case xcom_vtype_int64: return xcom_var(a.int32_val()%b.int64_val()); \
case xcom_vtype_uint64:return xcom_var(a.int32_val()%b.uint64_val()); \
break;\
default:\
break;\
}\
case xcom_vtype_uint32:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(a.uint32_val()%b.bool_val()); \
case xcom_vtype_int8:  return xcom_var(a.uint32_val()%b.int8_val()); \
case xcom_vtype_uint8: return xcom_var(a.uint32_val()%b.uint8_val()); \
case xcom_vtype_int16: return xcom_var(a.uint32_val()%b.int16_val()); \
case xcom_vtype_uint16:return xcom_var(a.uint32_val()%b.uint16_val()); \
case xcom_vtype_int32: return xcom_var(a.uint32_val()%b.int32_val()); \
case xcom_vtype_uint32:return xcom_var(a.uint32_val()%b.uint32_val()); \
case xcom_vtype_int64: return xcom_var(a.uint32_val()%b.int64_val()); \
case xcom_vtype_uint64:return xcom_var(a.uint32_val()%b.uint64_val()); \
break;\
default:\
break;\
}\
case xcom_vtype_int64:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(a.int64_val()%b.bool_val()); \
case xcom_vtype_int8:  return xcom_var(a.int64_val()%b.int8_val()); \
case xcom_vtype_uint8: return xcom_var(a.int64_val()%b.uint8_val()); \
case xcom_vtype_int16: return xcom_var(a.int64_val()%b.int16_val()); \
case xcom_vtype_uint16:return xcom_var(a.int64_val()%b.uint16_val()); \
case xcom_vtype_int32: return xcom_var(a.int64_val()%b.int32_val()); \
case xcom_vtype_uint32:return xcom_var(a.int64_val()%b.uint32_val()); \
case xcom_vtype_int64: return xcom_var(a.int64_val()%b.int64_val()); \
case xcom_vtype_uint64:return xcom_var(a.int64_val()%b.uint64_val()); \
break;\
default:\
break;\
}\
case xcom_vtype_uint64:\
switch (b.type) { \
case xcom_vtype_bool:  return xcom_var(a.uint64_val()%b.bool_val()); \
case xcom_vtype_int8:  return xcom_var(a.uint64_val()%b.int8_val()); \
case xcom_vtype_uint8: return xcom_var(a.uint64_val()%b.uint8_val()); \
case xcom_vtype_int16: return xcom_var(a.uint64_val()%b.int16_val()); \
case xcom_vtype_uint16:return xcom_var(a.uint64_val()%b.uint16_val()); \
case xcom_vtype_int32: return xcom_var(a.uint64_val()%b.int32_val()); \
case xcom_vtype_uint32:return xcom_var(a.uint64_val()%b.uint32_val()); \
case xcom_vtype_int64: return xcom_var(a.uint64_val()%b.int64_val()); \
case xcom_vtype_uint64:return xcom_var(a.uint64_val()%b.uint64_val()); \
break;\
default:\
break;\
}\
default:\
break;\
}\
}while(0)
    
}

#endif /* xcom_var_util_h */
