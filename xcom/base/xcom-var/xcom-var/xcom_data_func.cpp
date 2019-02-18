//
//  xcom_data_func.cpp
//  xcom-var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#include "xcom_data_func.h"
#include "xcom_var.h"
#include "xcom_data.h"
namespace xcom {
    xcom_data_func::xcom_data_func()
    {
        func = nullptr;
        funcpar = nullptr;
    }
    xcom_data_func::xcom_data_func(const xcom_data_func &vf)
    {
        func = vf.func;
        funcpar = new xcom_data(vf.funcpar);
    }
    xcom_data_func::xcom_data_func(xcom_data_func &&vf)
    {
        func = vf.func;
        funcpar = std::move(vf.funcpar);
        
        vf.func = nullptr;
        vf.funcpar = nullptr;
    }
    xcom_data_func::xcom_data_func(const xcom_callback callback)
    {
        func = callback;
        funcpar = nullptr;
    }
    xcom_data_func::xcom_data_func(const xcom_callback callback, const xcom_data &par)
    {
        func = callback;
        funcpar = new xcom_data(par);
    }
    xcom_data_func::xcom_data_func(const xcom_callback callback, xcom_data &&par)
    {
        func = callback;
        funcpar = new xcom_data(std::move(par));
    }
    xcom_data_func::~xcom_data_func()
    {
        func = nullptr;
        
        if (funcpar) {
            delete funcpar;
            funcpar = nullptr;
        }
    }
    
    xcom_data_func &xcom_data_func::operator =(const xcom_data_func &vf)
    {
        func = vf.func;
        funcpar = vf.funcpar;
        return *this;
    }
    xcom_data_func &xcom_data_func::operator =(xcom_data_func &&vf)
    {
        func = vf.func;
        funcpar = std::move(vf.funcpar);
        
        vf.func = nullptr;
        vf.funcpar = nullptr;
        return *this;
    }
    
    xcom_data_func::operator xcom_data() const
    {
        if (func) {
            if (funcpar) {
                return func(*funcpar);
            } else {
                xcom_data tmp;
                xcom_data data = func(tmp);
                return data;
            }
            
        }
        return xcom_data();
    }
    
    xcom_data xcom_data_func::call()
    {
        if (func) {
            if (funcpar) {
                return func(*funcpar);
            } else {
                xcom_data tmp;
                xcom_data data = func(tmp);
                return data;
            }
            
        }
        return xcom_data();
    }
    
    
    const char *xcom_data_func::to_var_json() const
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
    
    const char *xcom_data_func::to_json() const
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
