//
// Created by alexichen on 2018/7/9.
//

#ifndef XCOM_LOG_BUFFER_H
#define XCOM_LOG_BUFFER_H

#include <string>
#include <stdint.h>
#include <mutex>

#include "xcom_log_ptr_buffer.h"
#include "xcom_auto_buffer.h"

namespace xcom {
    
    class xcom_log_crypt;
    
    class xcom_log_buffer {
        
    public:
        xcom_log_buffer(void *_pbuffer, size_t _len, bool _is_compress = false);
        
        ~xcom_log_buffer();
        
    public:
        xcom_log_ptr_buffer &getData();
        
        void flush(xcom_auto_buffer &_buff);
        
        bool write(const void *_data, size_t _inputlen, xcom_auto_buffer &_out_buff);
        
        bool write(const void *_data, size_t _length);
        
    private:
        
        bool reset();
        
        void clear();
        
    private:
        std::mutex _logBufferMutex;
        xcom_log_ptr_buffer _logBuff;
        //    z_stream _cstream;
        xcom_log_crypt * _pLogCrypt;
        
        bool is_compress_;
        
    };
}
#endif

