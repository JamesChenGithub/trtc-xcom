//
//  xcom_var.h
//  xcom_var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#ifndef xcom_var_h
#define xcom_var_h

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "xcom_var_type.h"
#include "xcom_var_value.h"
#include "xcom_data_func.h"


namespace xcom {
#ifdef __cplusplus
//    extern "C" {
#endif
        class xcom_var
        {
            
        public:
            xcom_var_value  obj;
            xcom_var_type   type = xcom_vtype_null;
            
        public:
            ~xcom_var();
            xcom_var();
            
            // copy and =
            xcom_var(const xcom_var &val) : xcom_var() {
                this->reset(val);
            }
            xcom_var(xcom_var *val) : xcom_var() {
                if (val)
                {
                    this->reset(*val);
                }
            }
            
            xcom_var(xcom_var &&val) : xcom_var() {
                this->reset(std::move(val));
            }
            
            inline xcom_var &operator = (const xcom_var &value) {
                this->reset(value);
                return *this;
            }
            inline xcom_var &operator = (xcom_var &&value) {
                this->reset(std::move(value));
                return *this;
            }
        private:
            // 重置
            void reset();
            // 复制
            void reset(const xcom_var &var);
            // move
            void reset(xcom_var &&var);
            
        public:
            const char *to_var_json() const;
            const char *to_json() const;
            const char *to_string() const;
            
        private:
            const char *to_json(const char *key) const;
        public:
            // basic types
            #define XCOM_VAR_FUNCTION(T, VT, VAL) \
            inline xcom_var(T value):xcom_var() { this->type = xcom_vtype_##VT;  this->obj.VT##_val = value; } \
            inline operator T() {return this->obj.VT##_val; } \
            inline T VT##_val() const {return this->obj.VT##_val; } \
            xcom_var &operator = (T value) { \
                if (this->type == xcom_vtype_vptr) {\
                    xcom_var_ptr ptr = this->vptr_val();\
                    *ptr = value;\
                } else {\
                    this->reset();\
                    this->type = xcom_vtype_##VT;\
                    this->obj.VT##_val = value;\
                }\
                return *this;\
            }\
            inline bool operator == (const T value) const { return this->type != xcom_vtype_##VT  ?  false : this->obj.VT##_val == value; }
            
//                    inline xcom_var(bool value):xcom_var() {
//                        this->type = xcom_vtype_bool;
//                        this->obj.bool_val = value;
//                    }
//                    inline operator bool() {
//                        return this->obj.bool_val;
//                    }
//                    inline bool bool_val() const {
//                        return this->obj.bool_val;
//                    }
//                    inline xcom_var &operator = (bool value) {
//
//                        if (this->type == xcom_vtype_vptr)
//                        {
//                            xcom_var_ptr ptr = this->vptr_val();
//                            //printf("set ptr : %p : %s\n", ptr.get(), ptr->to_var_json());
//                            *ptr = value;
//                        }
//                        else
//                        {
//                            this->reset();
//                            this->type = xcom_vtype_bool;
//                            this->obj.bool_val = value;
//                        }
//                        return *this;
//                    }
//
//                    inline bool operator == (const bool value) const {
//                        return this->type != xcom_vtype_bool  ?  false : this->obj.bool_val == value;
//                    }
            
            
            XCOM_VAR_FUNCTION(bool, bool, false)
            XCOM_VAR_FUNCTION(int8_t, int8, 0)
            XCOM_VAR_FUNCTION(uint8_t, uint8, 0)
            XCOM_VAR_FUNCTION(int16_t, int16, 0)
            XCOM_VAR_FUNCTION(uint16_t, uint16, 0)
            XCOM_VAR_FUNCTION(int32_t, int32, 0)
            XCOM_VAR_FUNCTION(uint32_t, uint32, 0)
            XCOM_VAR_FUNCTION(int64_t, int64, 0)
            XCOM_VAR_FUNCTION(uint64_t, uint64, 0)
            XCOM_VAR_FUNCTION(float, float, 0.0)
            XCOM_VAR_FUNCTION(double, double, 0.0)
            XCOM_VAR_FUNCTION(void *, ref, NULL)
            
//            inline xcom_var(void * value):xcom_var() {
//                this->type = xcom_vtype_ref;
//                this->obj.ref_val = value;
//            }
//            inline operator void *() {
//                return this->obj.ref_val;
//            }
//            inline bool ref_val() const {
//                return this->obj.ref_val;
//            }
//            inline xcom_var &operator = (void * value) {
//                
//                if (this->type == xcom_vtype_vptr)
//                {
//                    xcom_var_ptr ptr = this->vptr_val();
//                    //printf("set ptr : %p : %s\n", ptr.get(), ptr->to_var_json());
//                    *ptr = value;
//                }
//                else
//                {
//                    this->reset();
//                    this->type = xcom_vtype_ref;
//                    this->obj.ref_val = value;
//                }
//                return *this;
//            }
//            
//            inline bool operator == (const void *value) const {
//                return this->type != xcom_vtype_ref  ?  false : this->obj.ref_val == value;
//            }
            
            
            
            // string
            xcom_var(const std::string &str);
            xcom_var(const char *cstr);
            
            operator const char *() const;
            operator std::string() const;
            
            const char *cstr_val() const;
            std::string string_val() const;
            
            xcom_var &operator= (const char *cstr);
            xcom_var &operator= (const std::string &str);
            
            bool operator == (const char *cstr) const;
            bool operator == (const std::string str) const;
            
           
            
            // vptr
            inline xcom_var(xcom_var_ptr value):xcom_var() {
                this->type = xcom_vtype_vptr;
                this->obj.vptr_val = value;
            }
            inline operator xcom_var_ptr() {
                if (this->type == xcom_vtype_vptr) {
                    return this->obj.vptr_val;
                }
                return nullptr;
            }
            inline xcom_var_ptr vptr_val() const {
                if (this->type == xcom_vtype_vptr) {
                    return this->obj.vptr_val;
                }
                return nullptr;
            }
            inline xcom_var &operator = (xcom_var_ptr value) {
                this->reset();
                this->type = xcom_vtype_vptr;
                this->obj.vptr_val = value;
                return *(this->obj.vptr_val.get());
            }
            inline bool operator == (const xcom_var_ptr value) const {
                return this->type != xcom_vtype_vptr  ?  false : this->obj.vptr_val == value;
            }
            
            inline void reset_vptr()
            {
                if (this->type == xcom_vtype_vptr) {
                    this->obj.vptr_val = nullptr;
                }
            }
            
            // func
            
            inline xcom_var(const xcom_data_func &value):xcom_var() {
                this->type = xcom_vtype_func;
                this->obj.func_val = new xcom_data_func(value);
            }
            inline xcom_var(xcom_data_func &&value):xcom_var() {
                this->type = xcom_vtype_func;
                this->obj.func_val = new xcom_data_func(std::move(value));
            }
            
            inline xcom_data_func *func_val() const {
                if (this->type == xcom_vtype_func && this->obj.func_val) {
                    return this->obj.func_val;
                }
                return nullptr;
            }
            
            xcom_var &operator = (const xcom_data_func &value) {
                if (this->type == xcom_vtype_vptr)
                {
                    xcom_var_ptr ptr = this->vptr_val();
                    *ptr = value;
                }
                else
                {
                    this->reset();
                    this->type = xcom_vtype_func;
                    this->obj.func_val = new xcom_data_func(value);
                }
                return *this;
            }
            xcom_var &operator = (xcom_data_func &&value) {
                if (this->type == xcom_vtype_vptr)
                {
                    xcom_var_ptr ptr = this->vptr_val();
                    *ptr = std::move(value);
                }
                else
                {
                    this->reset();
                    this->type = xcom_vtype_func;
                    this->obj.func_val = new xcom_data_func(std::move(value));
                }
                return *this;
            }
        public:
            /* array */
            xcom_var_ptr operator[](int32_t index);
            
            /* 'index' based array methods */
            void append(const xcom_var &data);
            void append(xcom_var &&data);
            bool erase(int32_t index);
        private:
            
            /* 'index' based array methods */
            xcom_var_ptr at(uint32_t index);
            
            void init_varray();
        public:
            // map
            // 必须先插入后，才可以再用[key]方式取值
            // 当前若为dic时，是否（is_dic_insert）继续插入
            void insert(const char *key, const xcom_var &value, bool is_dic_insert = false);
            /* dict */
            xcom_var_ptr operator[](const char *key);
            
            bool contains(const char *key);
            
            bool erase(const char *key);
        private:
            void init_vdict();
            void init_vmap();
            
            /* 'key-value' dictionary methods */
            // for dict
            void put(const char *key);
            
            // for map
            void put(const char *key, const xcom_var &value);
            
            xcom_var_ptr get(const char *key);
            
        public:
            /* buffer */
            void set_buffer(const void *data, uint32_t len);

            
        public:
            inline bool is_number() const { return this->type < xcom_vtype_string; }
            inline bool is_string() const { return this->type == xcom_vtype_string; }
            inline bool is_array() const { return this->type == xcom_vtype_array; }
            inline bool is_dict() const { return this->type == xcom_vtype_dict;}
            inline bool is_valid() const { return this->type != xcom_vtype_null;}
            inline bool is_function() const { return this->type == xcom_vtype_func;}
            bool is_zero() const;
            
            // just array or dict vaild, return empty;
            // other return false
            bool empty() const;
            
            // just array or dict vaild, return size;
            // other return 1
            uint32_t size();
            
        private:
        
        public:
            
            // 友元重载 ： 双目算术运算符    + (加)，-(减)，*(乘)，/(除)，% (取模)
            // 只针对数据类型, 非数据类型返回 xcom_var() 
            friend xcom_var operator+(const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend xcom_var operator-(const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend xcom_var operator*(const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend xcom_var operator/(const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend xcom_var operator%(const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            
            // 关系运算符   != (不等于)，< (小于)，> (大于>，<=(小于等于)，>=(大于等于)
            friend bool operator !=(const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend bool operator ==(const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend bool operator < (const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend bool operator > (const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend bool operator <=(const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend bool operator >=(const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            
            // 逻辑运算符    ||(逻辑或)，&&(逻辑与)，!(逻辑非)
            friend xcom_var operator||(const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend xcom_var operator&&(const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend xcom_var operator!(const xcom_var& a) throw(std::logic_error);
            //  单目运算符    + (正)，-(负)
            xcom_var operator +() const throw(std::logic_error);
            xcom_var operator -() const throw(std::logic_error);
            // 自增自减运算符    ++(自增)，--(自减)
            xcom_var& operator++ () throw(std::logic_error);     // prefix ++
            xcom_var  operator++ (int) throw(std::logic_error);// postfix ++
            
            xcom_var& operator-- () throw(std::logic_error);     // prefix --
            xcom_var  operator-- (int) throw(std::logic_error);  // postfix --
            
            
            // 位运算符:只对整型    | (按位或)，& (按位与)，~(按位取反)，^(按位异或),，<< (左移)，>>(右移)
            friend xcom_var operator | (const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend xcom_var operator & (const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend xcom_var operator ^ (const xcom_var& a, const xcom_var& b) throw(std::logic_error);
            friend xcom_var operator ~ (const xcom_var& a) throw(std::logic_error);
            friend xcom_var operator << (const xcom_var& a, int i) throw(std::logic_error);
            friend std::ostream & operator <<(std::ostream &os, const xcom_var &a );
            friend xcom_var operator >> (const xcom_var& a, int i) throw(std::logic_error);
            // 赋值运算符 +=, -=, *=, /= , % = , &=, |=, ^=, <<=, >>=
            inline xcom_var& operator +=(const xcom_var& a) throw(std::logic_error)
            {
                *this = *this + a;
                return *this;
            }
            inline xcom_var& operator -=(const xcom_var& a) throw(std::logic_error)
            {
                *this = *this - a;
                return *this;
            }
            inline xcom_var& operator *=(const xcom_var& a) throw(std::logic_error)
            {
                *this = *this * a;
                return *this;
            }
            inline xcom_var& operator /=(const xcom_var& a) throw(std::logic_error)
            {
                *this = *this / a;
                return *this;
            }
            inline xcom_var& operator %=(const xcom_var& a) throw(std::logic_error)
            {
                *this = *this % a;
                return *this;
            }
            inline xcom_var& operator &=(const xcom_var& a) throw(std::logic_error)
            {
                *this = *this & a;
                return *this;
            }
            inline xcom_var& operator |=(const xcom_var& a) throw(std::logic_error)
            {
                *this = *this | a;
                return *this;
            }
            inline xcom_var& operator ^=(const xcom_var& a) throw(std::logic_error)
            {
                *this = *this ^ a;
                return *this;
            }
            inline xcom_var& operator <<=(int i) throw(std::logic_error)
            {
                *this = *this << i;
                return *this;
            }
            inline xcom_var& operator >>=(int i) throw(std::logic_error)
            {
                *this = *this >> i;
                return *this;
            }
        };
        
#ifdef __cplusplus
//    }
#endif
}




#endif /* xcom_var_h */
