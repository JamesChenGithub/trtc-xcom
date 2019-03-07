//
//  xcom_ptrbuf.cpp
//  PtrBuf
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#include "xcom_ptrbuf.h"
#include "xcom_assert.h"
namespace xcom {
    const xcom_ptrbuf KNullPtrBuffer(0, 0, 0);
    
#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif
    
    xcom_ptrbuf::xcom_ptrbuf(void* _ptr, size_t _len, size_t _maxlen)
    : parray_((unsigned char*)_ptr),
    pos_(0), length_(_len),
    max_length_(_maxlen) {
        XCOM_ASSERT(length_ <= max_length_);
    }
    
    xcom_ptrbuf::xcom_ptrbuf(void* _ptr, size_t _len)
    : parray_((unsigned char*)_ptr)
    , pos_(0)
    , length_(_len)
    , max_length_(_len) {
        XCOM_ASSERT(length_ <= max_length_);
    }
    
    xcom_ptrbuf::xcom_ptrbuf() {
        reset();
    }
    
    xcom_ptrbuf::~xcom_ptrbuf() {
    }
    
    void xcom_ptrbuf::write(const void *pBuffer, size_t nLen) {
        XCOM_ASSERT(NULL != pBuffer);
        XCOM_ASSERT(0 <= pos_);
        XCOM_ASSERT((unsigned int) pos_ <= length());
        write(pBuffer, nLen, pos());
        seek(nLen, xcom_ptrbuf_seek_cur);
    }
    
    void xcom_ptrbuf::write(const void *pBuffer, size_t nLen, off_t nPos) {
        
        XCOM_ASSERT(NULL != pBuffer);
        XCOM_ASSERT(0 <= pos_);
        XCOM_ASSERT((unsigned int) pos_ <= length());
        
        size_t copylen = min(nLen, max_length_ - nPos);
        length_ = max(length_, copylen + nPos);
        memcpy((unsigned char*) ptr() + nPos, pBuffer, copylen);
    }
    
    size_t xcom_ptrbuf::read(void *_pBuffer, size_t _nLen) {
        size_t nRead = read(_pBuffer, _nLen, pos());
        seek(nRead, xcom_ptrbuf_seek_cur);
        return nRead;
    }
    
    size_t xcom_ptrbuf::read(void *_pBuffer, size_t _nLen, off_t _nPos) const {
        
        size_t nRead = length() - _nPos;
        nRead = min(nRead, _nLen);
        memcpy(_pBuffer, posPtr(), nRead);
        return nRead;
    }
    
    void  xcom_ptrbuf::seek(off_t _nOffset, xcom_ptrbuf_seek _eOrigin) {
        switch (_eOrigin) {
            case xcom_ptrbuf_seek_start:
                pos_ = _nOffset;
                break;
                
            case xcom_ptrbuf_seek_cur:
                pos_ += _nOffset;
                break;
                
            case xcom_ptrbuf_seek_end:
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
    
    void xcom_ptrbuf::length(off_t _nPos, size_t _nLenght) {
        
        length_ = max_length_ < _nLenght ? max_length_ : _nLenght;
        seek(_nPos, xcom_ptrbuf_seek_start);
    }
    
    void*  xcom_ptrbuf::ptr() {
        return parray_;
    }
    
    const void*  xcom_ptrbuf::ptr() const {
        return parray_;
    }
    
    void* xcom_ptrbuf::posPtr() {
        return ((unsigned char*) ptr()) + pos();
    }
    
    const void* xcom_ptrbuf::posPtr() const {
        return ((unsigned char*) ptr()) + pos();
    }
    
    off_t xcom_ptrbuf::pos() const {
        return pos_;
    }
    
    size_t xcom_ptrbuf::posLength() const {
        return length_ - pos_;
    }
    
    size_t xcom_ptrbuf::length() const {
        return length_;
    }
    
    size_t xcom_ptrbuf::maxLength() const {
        return max_length_;
    }
    
    void xcom_ptrbuf::attach(void *_pBuffer, size_t _nLen, size_t _maxlen) {
        reset();
        parray_ = (unsigned char*)_pBuffer;
        length_ = _nLen;
        max_length_ = _maxlen;
    }
    
    void xcom_ptrbuf::attach(void *_pBuffer, size_t _nLen) {
        attach(_pBuffer, _nLen, _nLen);
    }
    
    void xcom_ptrbuf::reset() {
        parray_ = NULL;
        pos_ = 0;
        length_ = 0;
        max_length_ = 0;
    }
}
