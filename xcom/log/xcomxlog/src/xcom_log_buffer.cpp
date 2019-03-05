//
// Created by alexichen on 2018/7/9.
//

#include "xcom_log_buffer.h"

#include "xcom_log_crypt.h"

namespace xcom {
    xcom_log_buffer::xcom_log_buffer(void *_pbuffer, size_t _len, bool _isCompress) : is_compress_(_isCompress) {
        _logBuff.attach(_pbuffer, _len);
        
        _pLogCrypt = new xcom_log_crypt();
        //    if (is_compress_) {
        //        memset(&cstream_, 0, sizeof(cstream_));
        //    }
    }
    
    xcom_log_buffer::~xcom_log_buffer() {
        //    if (is_compress_ && Z_NULL != cstream_.state) {
        //        deflateEnd(&cstream_);
        //    }
        delete _pLogCrypt;
    }
    
    xcom_log_ptr_buffer &xcom_log_buffer::getData() {
        return _logBuff;
    }
    
    
    void xcom_log_buffer::flush(xcom_auto_buffer &_buff) {
        
        _logBufferMutex.lock();
        if (xcom_log_crypt::getLogLength((char *) _logBuff.ptr(), _logBuff.length()) != 0) {
            uint32_t valid_len = xcom_log_crypt::getValidLength((char*) _logBuff.ptr(), _logBuff.length());
            _buff.write(_logBuff.ptr(), valid_len);
        }
        clear();
        _logBufferMutex.unlock();
    }
    
    bool xcom_log_buffer::write(const void *_data, size_t _inputlen, xcom_auto_buffer &_out_buff) {
        if (NULL == _data || 0 == _inputlen) {
            return false;
        }
        
        if (is_compress_) {
            //TODO
            //        compressLog(_data,_length,outBuffer);
        }
        _pLogCrypt->cryptSyncLog((char *) _data, _inputlen, _out_buff);
        
        return true;
    }
    
    
    bool xcom_log_buffer::write(const void *_data, size_t _length) {
        if (NULL == _data || 0 == _length) {
            return false;
        }
        
        if (is_compress_) {
            //TODO
            //        compressLog(_data,_length,outBuffer);
        }
        
        xcom_auto_buffer out_buffer;
        _pLogCrypt->cryptAsyncLog((char *) _data, _length, out_buffer);
        
        _logBufferMutex.lock();
        if (_logBuff.length() == 0) {
            reset();
        }
        _logBuff.write(out_buffer.ptr(), out_buffer.length());
        _logBufferMutex.unlock();
        return true;
    }
    
    bool xcom_log_buffer::reset() {
        
        clear();
        
        if (is_compress_) {
            //        cstream_.zalloc = Z_NULL;
            //        cstream_.zfree = Z_NULL;
            //        cstream_.opaque = Z_NULL;
            //
            //        if (Z_OK !=
            //            deflateInit2(&cstream_, Z_BEST_COMPRESSION, Z_DEFLATED, -MAX_WBITS, MAX_MEM_LEVEL,
            //                         Z_DEFAULT_STRATEGY)) {
            //            return false;
            //        }
            //
        }
        
        return true;
    }
    
    void xcom_log_buffer::clear() {
        memset(_logBuff.ptr(), 0, _logBuff.maxLength());
        _logBuff.length(0, 0);
    }
    
    
}
