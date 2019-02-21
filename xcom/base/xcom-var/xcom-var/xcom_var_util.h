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
    
    
}

#endif /* xcom_var_util_h */
