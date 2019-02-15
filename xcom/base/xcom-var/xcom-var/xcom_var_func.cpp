//
//  xcom_var_func.cpp
//  xcom-var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#include "xcom_var_func.h"
#include "xcom_var.h"
namespace xcom {
    xcom_var_func::xcom_var_func()
    {
        func = nullptr;
        funcpar = nullptr;
    }
    xcom_var_func::xcom_var_func(const xcom_var_func &vf)
    {
        func = vf.func;
        funcpar = vf.funcpar;
    }
    xcom_var_func::xcom_var_func(xcom_var_func &&vf)
    {
        func = vf.func;
        xcom_var_ptr vptr(new xcom_var(std::move(vf.funcpar)));
        funcpar = vptr;
        
        vf.func = nullptr;
        vf.funcpar = nullptr;
    }
    xcom_var_func::xcom_var_func(const xcom_var_callback callback)
    {
        func = callback;
        funcpar = nullptr;
    }
    xcom_var_func::xcom_var_func(const xcom_var_callback callback, const xcom_var &par)
    {
        func = callback;
        xcom_var_ptr vptr(new xcom_var(par));
        funcpar = vptr;
    }
    xcom_var_func::xcom_var_func(const xcom_var_callback callback, xcom_var &&par)
    {
        func = callback;
        funcpar = std::move(par);
    }
    xcom_var_func::~xcom_var_func()
    {
        func = nullptr;
        funcpar.reset();
        funcpar = nullptr;
    }
    
    xcom_var_func &xcom_var_func::operator =(const xcom_var_func &vf)
    {
        func = vf.func;
        funcpar = vf.funcpar;
        return *this;
    }
    xcom_var_func &xcom_var_func::operator =(xcom_var_func &&vf)
    {
        func = vf.func;
        funcpar = std::move(vf.funcpar);
        
        vf.func = nullptr;
        vf.funcpar = nullptr;
        return *this;
    }
    
    xcom_var_func::operator xcom_var() const
    {
        if (funcpar != nullptr) {
            xcom_var voidvar;
            return func(voidvar);
        }else {
            return func(*funcpar);
        }
        return xcom_var();
    }
    const char *xcom_var_func::to_var_json() const
    {
        char buf[128];
        sprintf(buf, "%p", func);
        std::ostringstream ostr;
        ostr << "{ \"func\" : ";
        ostr << (func == nullptr ? "NULL" : buf);
        ostr << ", \"param\" : \"";
        ostr << (funcpar == nullptr ? "void" : funcpar->to_var_json());
        ostr << "}";
        std::string str = ostr.str();
        return str.c_str();
    }
    
    const char *xcom_var_func::to_json() const
    {
        char buf[128];
        sprintf(buf, "%p", func);
        std::ostringstream ostr;
        ostr << "{ \"func\" : ";
        ostr << (func == nullptr ? "NULL" : buf);
        ostr << ", \"param\" : \"";
        ostr << (funcpar == nullptr ? "void" : funcpar->to_json());
        ostr << "}";
        std::string str = ostr.str();
        return str.c_str();
    }
    
}
