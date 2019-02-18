//
//  xcom_data.cpp
//  xcom-var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#include "xcom_data.h"
#include "xcom_var.h"
#include "xcom_data_func.h"
namespace xcom {
    
    static int datacount = 0;
    xcom_data::xcom_data():_core(nullptr)
    {
        printf("xcom_data [%d] create  : %p \n", ++datacount, this);
    }
    
    xcom_data::~xcom_data()
    {
        printf("xcom_data [%d] release : %p core = %p\n", --datacount, this, _core);
        reset();
    }
    
    // 重置
    void xcom_data::reset()
    {
        if (_core && isowed)
        {
            delete _core;
            _core = nullptr;
        }
    }
    // 复制
    void xcom_data::reset(const xcom_data &data)
    {
        reset();
        if (data._core) {
            _core = new xcom_var(*data._core);
            isowed = true;
        }
    }
    // move
    void xcom_data::reset(xcom_data &&data)
    {
        reset();
        if (data._core)
        {
            xcom_var var = *data._core;
            _core = new xcom_var(std::move(var));
            isowed = true;
        }
    }
    
    xcom_data::xcom_data(xcom_var *var, bool isvp):xcom_data()
    {
        if (var != nullptr) {
            _core = var;
            isowed = false;
            printf("var = %p,  _core = %p , vp = %p ,  %s  \n", var,  _core, _core->vptr_val().get() ,_core->to_json());
        }
    }
    
    xcom_data::xcom_data(const xcom_var &var, bool isPrivateTag):xcom_data()
    {
        if (var.is_valid()) {
            _core = new xcom_var(std::move(var));
            isowed = true;
        }
    }
    
    
    xcom_data::xcom_data(const xcom_data &data):xcom_data()
    {
        if (data._core)
        {
            _core = new xcom_var(*data._core);
            isowed = true;
        }
    }
    
//    xcom_data::xcom_data(const xcom_var_func &func):xcom_data() {
//        _core = new xcom_var(func);
//        isowed = true;
//    }
    
    xcom_data::xcom_data(xcom_data &&data):xcom_data()
    {
        if (data._core)
        {
            xcom_var var = *data._core;
            _core = new xcom_var(std::move(var));
//            data._core = nullptr;
        }
    }
   
    xcom_data& xcom_data::operator = (const xcom_data &data)
    {
        if (data._core && _core) {
            *_core = *data._core;
        } else {
            this->reset(data);
        }
        
        return *this;
        
    }
    xcom_data& xcom_data::operator = (xcom_data &&data)
    {
        if (data._core && _core) {
            *_core = std::move(*data._core);
        } else {
            this->reset(std::move(data));
        }
        
        return *this;
    }
    
#define XCOM_DATA_IMPL(T, VT, VAL) \
    xcom_data::xcom_data(T value):xcom_data() { _core = new xcom_var(value); isowed = true;} \
    xcom_data::operator T() const {return _core ? _core->obj.VT##_val : VAL; } \
    T xcom_data::VT##_val() const {return _core ? _core->obj.VT##_val : VAL; } \
    xcom_data& xcom_data::operator = (T value) { \
        if (_core)  {*_core = value;}\
        else  {_core = new xcom_var(value); isowed = true;}\
        return *this;\
    }\
    bool xcom_data::operator == (const T value) const { return _core && _core->type != xcom_vtype_##VT  ? _core->obj.VT##_val == value : false ;}
    

//    xcom_data::xcom_data(bool value):_core(nullptr), isowed(true) {
//        _core = new xcom_var(value);
//        isowed = true;
//    }
//    xcom_data::operator bool() const{
//        return _core ? _core->obj.bool_val : false;
//    }
//    bool xcom_data::bool_val() const {
//        return _core ? _core->obj.bool_val : false;
//    }
//    xcom_data& xcom_data::operator = (bool value) {
//        if (_core)
//        {
//            xcom_var_ptr ptr = _core->vptr_val();
//            *_core = value;
//        }
//        else
//        {
//            _core = new xcom_var(value);
//            isowed = true;
//        }
//        return *this;
//    }
//    bool xcom_data::operator == (const bool value) const {
//        return _core && _core->type != xcom_vtype_bool  ?  _core->obj.bool_val == value : false;
//    }

    
    XCOM_DATA_IMPL(bool, bool, false)
    XCOM_DATA_IMPL(int8_t, int8, 0)
    XCOM_DATA_IMPL(uint8_t, uint8, 0)
    XCOM_DATA_IMPL(int16_t, int16, 0)
    XCOM_DATA_IMPL(uint16_t, uint16, 0)
    XCOM_DATA_IMPL(int32_t, int32, 0)
    XCOM_DATA_IMPL(uint32_t, uint32, 0)
    XCOM_DATA_IMPL(int64_t, int64, 0)
    XCOM_DATA_IMPL(uint64_t, uint64, 0)
    XCOM_DATA_IMPL(float, float, 0.0)
    XCOM_DATA_IMPL(double, double, 0.0)
    XCOM_DATA_IMPL(void *, ref, NULL)
    
    xcom_data::xcom_data(const char *value):xcom_data() {
        _core = new xcom_var(value);
        isowed = true;
    }
    xcom_data::operator const char *() const
    {
        return _core ? _core->string_val().c_str() : nullptr;
    }
    xcom_data::operator xcom_var()
    {
        if (_core == nullptr){
            _core = new xcom_var;
            isowed = true;
        }
        return *_core;
    }
    const char * xcom_data::string_val() const
    {
        return _core ? _core->string_val().c_str() : nullptr;
    }
    xcom_data &xcom_data::operator = (const char *value)
    {
        if (_core)  {
            *_core = value;
        }
        else {
            _core = new xcom_var(value);
            isowed = true;
        }
        return *this;
    }
    bool xcom_data::operator == (const char* value) const
    {
        return _core && _core->type != xcom_vtype_string ?  *_core == value : false;
    }
    
    
    const char *xcom_data::to_var_json() const
    {
        if (_core == nullptr)
        {
            return nullptr;
        }
        const char *str = _core->to_var_json();
        return str;
        
    }
    
    const char *xcom_data::to_json() const
    {
        if (_core == nullptr)
        {
            return nullptr;
        }
        const char *str = _core->to_json();
        return str;
    }
    bool xcom_data::empty() const
    {
        return _core ? _core->empty() : true;
    }
    uint32_t xcom_data::size() const
    {
        return _core ? _core->size() : 0;
    }
    
    void xcom_data::insert(const char *key, const xcom_data &xvalue, bool is_dic_insert)
    {
        if (!key || !*key)
            return;
        
        if (xvalue._core == nullptr) {
            return;
        } else {
            
            if (xvalue._core->is_valid()) {
                if (_core == nullptr) {
                    _core = new xcom_var();
                    isowed = true;
                }
                
                _core->insert(key, *(xvalue._core), is_dic_insert);
            }
        }
    }
    xcom_data xcom_data::operator[](const char *key)
    {
        if (!key || !*key)
            return xcom_data();
        
        if (_core == nullptr) {
            _core = new xcom_var();
            isowed = true;
        }
        xcom_var_ptr ptr = (*_core)[key];
        printf("get ptr : %p : %s\n", ptr.get(), ptr->to_var_json());
        return xcom_data(ptr.get(), false);
    }
    bool xcom_data::contains(const char *key)
    {
        if (!key || !*key)
            return false;
        return _core ? _core->contains(key) : false;
    }
    bool xcom_data::erase(const char *key)
    {
        if (!key || !*key)
            return false;
        return _core ? _core->erase(key) : false;
    }
    
    void xcom_data::set_buf(const void *buf, uint32_t len)
    {
        if (buf == nullptr || len < 0)
        {
            return;
        }
        
        if (_core == nullptr)
        {
            _core = new xcom_var();
            isowed = true;
        }
        return _core->set_buffer(buf, len);
    }
    
    void xcom_data::set_callback(const xcom_data_callback funcAddr, xcom_data &data)
    {
        if (funcAddr == nullptr)
        {
            return;
        }
        
        if (_core)  {
            if (data._core) {
                
                xcom::xcom_data_func func(funcAddr, data);
                *_core = func;
            }
            else {
                xcom::xcom_data_func func(funcAddr);
                *_core = func;
            }
        }
        else {
            
            if (data._core) {
                xcom::xcom_data_func func(funcAddr, data);
                _core = new xcom_var(func);
            }
            else {
                xcom::xcom_data_func func(funcAddr);
                _core = new xcom_var(func);
            }
            printf("set_callback : core = %p\n", _core);
            isowed = true;
        }
    }
    
    void xcom_data::set_callback(const xcom_data_callback funcAddr, xcom_data &&data)
    {
        if (funcAddr == nullptr)
        {
            return;
        }
        
        if (_core)  {
            if (data._core) {
                
                xcom::xcom_data_func func(funcAddr, std::move(data));
                *_core = func;
            }
            else {
                xcom::xcom_data_func func(funcAddr);
                *_core = func;
            }
        }
        else {
            
            if (data._core) {
                xcom::xcom_data_func func(funcAddr, std::move(data));
                _core = new xcom_var(func);
            }
            else {
                xcom::xcom_data_func func(funcAddr);
                _core = new xcom_var(func);
            }
            printf("set_callback : core = %p\n", _core);
            isowed = true;
        }
    }
    
    xcom_data xcom_data::callback()
    {
        if (_core) {
            xcom_data_func *cb = _core->func_val();
            if (cb) {
                return cb->call();
            }
        }
        return xcom_data();
    }
    
    xcom_data xcom_data::operator[](int32_t index)
    {
        if (_core == nullptr)
        {
            _core = new xcom_var();
            isowed = true;
        }
        xcom_var_ptr ptr = (*_core)[index];
        return xcom_data(ptr.get(), false);
    }
    
    void xcom_data::append(xcom_data data)
    {
        if (data._core == nullptr) {
            return;
        }
        if (_core == nullptr)
        {
            _core = new xcom_var();
            isowed = true;
        }
        return _core->append(*data._core);
    }
    
    bool xcom_data::erase(int32_t index)
    {
        if (_core == nullptr)
        {
            _core = new xcom_var();
            isowed = true;
        }
        return _core->erase(index);
    }
    
}
