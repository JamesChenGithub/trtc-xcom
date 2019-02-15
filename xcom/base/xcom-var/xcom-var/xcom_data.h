//
//  xcom_data.h
//  xcom-var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#ifndef xcom_data_h
#define xcom_data_h

#include <vector>


namespace xcom {
    
    class xcom_var;
    class xcom_data;
    typedef xcom_data (*xcom_data_callback)(xcom_data &);
    
    class xcom_data
    {
    public:
        // basic declare
        xcom_data();
        ~xcom_data();
        
        xcom_data(const xcom_data &data);
        xcom_data(xcom_data &&data);
        
        xcom_data &operator = (const xcom_data &data);
        xcom_data &operator = (xcom_data &&data);
        
    public:
        // basic type delc
#define XCOM_DATA_DELC(T, VT, VAL) \
        xcom_data(T value);\
        operator T() const;  \
        T VT##_val() const;  \
        xcom_data &operator = (T value); \
        bool operator == (const T value) const; \

        XCOM_DATA_DELC(bool, bool, false)
        XCOM_DATA_DELC(int8_t, int8, 0)
        XCOM_DATA_DELC(uint8_t, uint8, 0)
        XCOM_DATA_DELC(int16_t, int16, 0)
        XCOM_DATA_DELC(uint16_t, uint16, 0)
        XCOM_DATA_DELC(int32_t, int32, 0)
        XCOM_DATA_DELC(uint32_t, uint32, 0)
        XCOM_DATA_DELC(int64_t, int64, 0)
        XCOM_DATA_DELC(uint64_t, uint64, 0)
        XCOM_DATA_DELC(float, float, 0.0)
        XCOM_DATA_DELC(double, double, 0.0)
        XCOM_DATA_DELC(void *, ref, NULL)
        
    public:
        // string delc
        xcom_data(const char *data);
        operator const char *() const;
        const char * string_val() const;
        xcom_data &operator = (const char *data);
        bool operator == (const char* data) const;
        
    public:
        // dict delc
        xcom_data operator[](const char *key);
        bool contains(const char *key);
        bool erase(const char *key);
        
    public:
        // array
        void append(xcom_data data);
        xcom_data operator[](int32_t index);
        bool erase(int32_t index);
    public:
        // buf
        void set_buf(const void *buf, uint32_t len);
        
    public:
        // func
        void set_callback(const xcom_data_callback funcAddr, xcom_data &data);
        xcom_data callback();
    public:
        // tool
        const char *to_var_json() const;
        const char *to_json() const ;
        
        // just array or dict vaild, return empty;
        // other return false
        bool empty() const;
        
        // just array or dict vaild, return size;
        // other return 1
        uint32_t size() const;
        
    private:
        xcom_var *_core = nullptr;
        bool isowed = true;
    private:
        xcom_data(xcom_var *var, bool isPrivateTag);
        xcom_data(const xcom_var &var, bool isPrivateTag);
    private:
        
    private:
        operator xcom_var();
        // 重置
        void reset();
        // 复制
        void reset(const xcom_data &var);
        // move
        void reset(xcom_data &&var);
        
    
        
    };
    
}


#endif /* xcom_data_h */
