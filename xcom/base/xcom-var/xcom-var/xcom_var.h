//
//  xcom_var.h
//  xcom_var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#ifndef var_hpp
#define var_hpp

#include <string>
#include <vector>
#include <sstream>

#include "xcom_var_type.h"


namespace xcom {
#ifdef __cplusplus
    extern "C" {
#endif
        class xcom_var;
        typedef std::shared_ptr<xcom_var> xcom_var_ptr;
        typedef std::vector<std::pair<std::string, xcom_var_ptr>> xcom_var_dict;
        typedef std::vector<xcom_var_ptr> xcom_var_array;
        typedef xcom_var (*xcom_var_callback)(xcom_var);
        
        
        
        
        class xcom_var
        {
        public:
            
            typedef struct xcom_var_func
            {
            public:
                xcom_var_callback       func;
                xcom_var_ptr            funcpar;
                
            public:
                xcom_var_func();
                xcom_var_func(const xcom_var_func &vf);
                xcom_var_func(xcom_var_func &&vf);
                xcom_var_func(xcom_var_callback callback, const xcom_var &par);
                xcom_var_func(xcom_var_callback callback, xcom_var &&par);
                ~xcom_var_func();
                
                xcom_var_func &operator =(const xcom_var_func &vf);
                xcom_var_func &operator =(xcom_var_func &&vf);
                operator xcom_var() const;
                const char *to_var_json() const;
                const char *to_json() const;
            }xcom_var_func;
            
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
                xcom_var_dict   *dict_val;
                xcom_var_array  *array_val;
                xcom_var_func   *func_val;
                xcom_var_ptr    vptr_val;
            public:
                xcom_var_value();
                ~xcom_var_value();
                
            }xcom_var_value;
            
            
            
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
            
        private:
            const char *to_json(const char *key) const;
        public:
            // basic types
            #define XCOM_VAR_FUNC(T, VT, VAL) \
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
//                            xcom_var_ptr ptr = this->var_val();
//                            printf("ptr = %p  %s\n", ptr.get(), ptr->to_var_json());
//                            *ptr = value;
//                            printf("ptr = %p  %s\n", ptr.get(), ptr->to_var_json());
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
            
            
            XCOM_VAR_FUNC(bool, bool, false)
            XCOM_VAR_FUNC(int8_t, int8, 0)
            XCOM_VAR_FUNC(uint8_t, uint8, 0)
            XCOM_VAR_FUNC(int16_t, int16, 0)
            XCOM_VAR_FUNC(uint16_t, uint16, 0)
            XCOM_VAR_FUNC(int32_t, int32, 0)
            XCOM_VAR_FUNC(uint32_t, uint32, 0)
            XCOM_VAR_FUNC(int64_t, int64, 0)
            XCOM_VAR_FUNC(uint64_t, uint64, 0)
            XCOM_VAR_FUNC(float, float, 0.0)
            XCOM_VAR_FUNC(double, double, 0.0)
            XCOM_VAR_FUNC(void *, ref, NULL)
            
            
            
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
            
            // func
            
            inline xcom_var(xcom_var_func value):xcom_var() {
                this->type = xcom_vtype_func;
                this->obj.func_val = new xcom_var_func(value);
            }
//            inline operator xcom_var_func*() {
//                return this->obj.func_val;
//            }
            inline xcom_var func_val() const {
                if (this->type == xcom_vtype_func && this->obj.func_val) {
                    return this->obj.func_val;
                }
                return xcom_var();
            }
            inline xcom_var &operator = (xcom_var_func *value) {
                
                if (this->type == xcom_vtype_vptr)
                {
                    xcom_var_ptr ptr = this->vptr_val();
                    *ptr = value;
                }
                else
                {
                    this->reset();
                    this->type = xcom_vtype_func;
                    this->obj.func_val = value;
                }
                return *this;
            }
            
            
            
        public:
            /* array */
            xcom_var_ptr operator[](uint32_t index);
            
            /* 'index' based array methods */
            void append(xcom_var data);
            bool erase(uint32_t index);
        private:
            
            /* 'index' based array methods */
            xcom_var_ptr at(uint32_t index);
            
            void init_varray();
        public:
            /* dict */
            xcom_var_ptr operator[](const char *key);
            bool contains(const char *key);
            
            bool erase(const char *key);
        private:
            void init_vdict();
            
            /* 'key-value' dictionary methods */
            void put(const char *key, xcom_var &&data);
            
            xcom_var_ptr get(const char *key);
            
        public:
            /* buffer */
            void set_buffer(const void *data, uint32_t len);

            
        public:
            inline bool is_number() const { return this->type <= xcom_vtype_string; }
            inline bool is_array() const { return this->type == xcom_vtype_array; }
            inline bool is_dict() const { return this->type == xcom_vtype_dict;}
            
            // just array or dict vaild, return empty;
            // other return false
            bool empty();
            
            // just array or dict vaild, return size;
            // other return 1
            uint32_t size();
        };
        
#ifdef __cplusplus
    }
}
#endif




#endif /* var_hpp */
