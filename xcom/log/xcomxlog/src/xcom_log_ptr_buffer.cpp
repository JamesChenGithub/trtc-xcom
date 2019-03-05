
#include "xcom_log_ptr_buffer.h"

#include <string.h>

namespace xcom
{
    
    
    const xcom_log_ptr_buffer KNullPtrBuffer(0, 0, 0);
    //
    // Created by alexichen on 2018/10/15.
    //
#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif
    
    xcom_log_ptr_buffer::xcom_log_ptr_buffer(void* _ptr, size_t _len, size_t _maxlen)
    : parray_((unsigned char*)_ptr)
    , pos_(0)
    , length_(_len)
    , max_length_(_maxlen) {
    }
    
    xcom_log_ptr_buffer::xcom_log_ptr_buffer(void* _ptr, size_t _len)
    : parray_((unsigned char*)_ptr)
    , pos_(0)
    , length_(_len)
    , max_length_(_len) {
    }
    
    xcom_log_ptr_buffer::xcom_log_ptr_buffer() {
        reset();
    }
    
    xcom_log_ptr_buffer::~xcom_log_ptr_buffer() {
    }
    
    void xcom_log_ptr_buffer::write(const void *_pBuffer, size_t _nLen) {
        write(_pBuffer, _nLen, pos());
        seek(_nLen, xcom_seek_cur);
    }
    
    void xcom_log_ptr_buffer::write(const void *_pBuffer, size_t _nLen, off_t _nPos) {
        size_t copylen = min(_nLen, max_length_ - _nPos);
        length_ = max(length_, copylen + _nPos);
        memcpy((unsigned char*) ptr() + _nPos, _pBuffer, copylen);
    }
    
    size_t xcom_log_ptr_buffer::read(void *_pBuffer, size_t _nLen) {
        size_t nRead = read(_pBuffer, _nLen, pos());
        seek(nRead, xcom_seek_cur);
        return nRead;
    }
    
    size_t xcom_log_ptr_buffer::read(void *_pBuffer, size_t _nLen, off_t _nPos) const {
        
        size_t nRead = length() - _nPos;
        nRead = min(nRead, _nLen);
        memcpy(_pBuffer, posPtr(), nRead);
        return nRead;
    }
    
    void  xcom_log_ptr_buffer::seek(off_t _nOffset, xcom_seek _eOrigin) {
        switch (_eOrigin) {
            case xcom_seek_start:
                pos_ = _nOffset;
                break;
                
            case xcom_seek_cur:
                pos_ += _nOffset;
                break;
                
            case xcom_seek_end:
                pos_ = length_ + _nOffset;
                break;
                
            default:
                break;
        }
        
        if (pos_ < 0)
            pos_ = 0;
        
        if ((unsigned int)pos_ > length_)
            pos_ = length_;
    }
    
    void xcom_log_ptr_buffer::length(off_t _nPos, size_t _nLenght) {
        
        length_ = max_length_ < _nLenght ? max_length_ : _nLenght;
        seek(_nPos, xcom_seek_start);
    }
    
    void*  xcom_log_ptr_buffer::ptr() {
        return parray_;
    }
    
    const void*  xcom_log_ptr_buffer::ptr() const {
        return parray_;
    }
    
    void* xcom_log_ptr_buffer::posPtr() {
        return ((unsigned char*) ptr()) + pos();
    }
    
    const void* xcom_log_ptr_buffer::posPtr() const {
        return ((unsigned char*) ptr()) + pos();
    }
    
    off_t xcom_log_ptr_buffer::pos() const {
        return pos_;
    }
    
    size_t xcom_log_ptr_buffer::posLength() const {
        return length_ - pos_;
    }
    
    size_t xcom_log_ptr_buffer::length() const {
        return length_;
    }
    
    size_t xcom_log_ptr_buffer::maxLength() const {
        return max_length_;
    }
    
    void xcom_log_ptr_buffer::attach(void *_pBuffer, size_t _nLen, size_t _maxlen) {
        reset();
        parray_ = (unsigned char*)_pBuffer;
        length_ = _nLen;
        max_length_ = _maxlen;
    }
    
    void xcom_log_ptr_buffer::attach(void *_pBuffer, size_t _nLen) {
        attach(_pBuffer, _nLen, _nLen);
    }
    
    void xcom_log_ptr_buffer::reset() {
        parray_ = NULL;
        pos_ = 0;
        length_ = 0;
        max_length_ = 0;
    }
    
}
