//
// Created by alexichen on 2018/10/15.
//

#include "xcom_auto_buffer.h"
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

namespace xcom
{
    const xcom_auto_buffer KNullAtuoBuffer;
    
#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif
    
    xcom_auto_buffer::xcom_auto_buffer(size_t _nSize)
    : parray_(NULL)
    , pos_(0)
    , length_(0)
    , capacity_(0)
    , malloc_unitsize_(_nSize)
    {}
    
    
    xcom_auto_buffer::xcom_auto_buffer(void* _pbuffer, size_t _len, size_t _nSize)
    : parray_(NULL)
    , pos_(0)
    , length_(0)
    , capacity_(0)
    , malloc_unitsize_(_nSize) {
        attach(_pbuffer, _len);
    }
    
    xcom_auto_buffer::xcom_auto_buffer(const void* _pbuffer, size_t _len, size_t _nSize)
    : parray_(NULL)
    , pos_(0)
    , length_(0)
    , capacity_(0)
    , malloc_unitsize_(_nSize) {
        write(0, _pbuffer, _len);
    }
    
    
    xcom_auto_buffer::~xcom_auto_buffer() {
        reset();
    }
    
    void xcom_auto_buffer::allocWrite(size_t _readytowrite, bool _changelength) {
        size_t nLen = pos() + _readytowrite;
        fitSize(nLen);
        
        if (_changelength) length_ = max(nLen, length_);
    }
    
    void xcom_auto_buffer::addCapacity(size_t _len) {
        fitSize(capacity() + _len);
    }
    
    void xcom_auto_buffer::write(const void *_pbuffer, size_t _len) {
        write(pos(), _pbuffer, _len);
        seek(_len, xcom_seek_cur);
    }
    
    void xcom_auto_buffer::write(off_t &_pos, const void *_pbuffer, size_t _len) {
        write((const off_t &) _pos, _pbuffer, _len);
        _pos += _len;
    }
    
    void xcom_auto_buffer::write(const off_t &_pos, const void *_pbuffer, size_t _len) {
        size_t nLen = _pos + _len;
        fitSize(nLen);
        length_ = max(nLen, length_);
        memcpy((unsigned char*) ptr() + _pos, _pbuffer, _len);
    }
    
    void xcom_auto_buffer::write(xcom_seek _seek, const void *_pbuffer, size_t _len){
        off_t pos = 0;
        switch (_seek) {
            case xcom_seek_start:
                pos = 0;
                break;
            case xcom_seek_cur:
                pos = pos_;
                break;
            case xcom_seek_end:
                pos = length_;
                break;
            default:
                break;
        }
        
        write(pos, _pbuffer, _len);
    }
    
    size_t xcom_auto_buffer::read(void *_pbuffer, size_t _len) {
        size_t readlen = read(pos(), _pbuffer, _len);
        seek(readlen, xcom_seek_cur);
        return readlen;
    }
    
    size_t xcom_auto_buffer::read(xcom_auto_buffer &_rhs, size_t _len) {
        size_t readlen = read(pos(), _rhs, _len);
        seek(readlen, xcom_seek_cur);
        return readlen;
    }
    
    size_t xcom_auto_buffer::read(off_t &_pos, void *_pbuffer, size_t _len) const {
        size_t readlen = read((const off_t &) _pos, _pbuffer, _len);
        _pos += readlen;
        return readlen;
    }
    
    size_t xcom_auto_buffer::read(off_t &_pos, xcom_auto_buffer &_rhs, size_t _len) const {
        size_t readlen = read((const off_t &) _pos, _rhs, _len);
        _pos += readlen;
        return readlen;
    }
    
    size_t xcom_auto_buffer::read(const off_t &_pos, void *_pbuffer, size_t _len) const {
        
        size_t readlen = length() - _pos;
        readlen = min(readlen, _len);
        memcpy(_pbuffer, posPtr(), readlen);
        return readlen;
    }
    
    size_t xcom_auto_buffer::read(const off_t &_pos, xcom_auto_buffer &_rhs, size_t _len) const {
        size_t readlen = length() - _pos;
        readlen = min(readlen, _len);
        _rhs.write(posPtr(), readlen);
        return readlen;
    }
    
    off_t xcom_auto_buffer::move(off_t _move_len) {
        if (0 < _move_len) {
            fitSize(length() + _move_len);
            memmove(parray_ + _move_len, parray_, length());
            memset(parray_, 0, _move_len);
            length(pos() + _move_len, length() + _move_len);
        } else {
            size_t move_len = -_move_len;
            
            if (move_len > length()) move_len = length();
            
            memmove(parray_, parray_ + move_len, length() - move_len);
            length(move_len < (size_t) pos() ? pos() - move_len : 0, length() - move_len);
        }
        
        return length();
    }
    
    void  xcom_auto_buffer::seek(off_t _offset, xcom_seek _eorigin) {
        switch (_eorigin) {
            case xcom_seek_start:
                pos_ = _offset;
                break;
                
            case xcom_seek_cur:
                pos_ += _offset;
                break;
                
            case xcom_seek_end:
                pos_ = length_ + _offset;
                break;
                
            default:
                break;
        }
        
        if (pos_ < 0)
            pos_ = 0;
        
        if ((size_t)pos_ > length_)
            pos_ = length_;
    }
    
    void xcom_auto_buffer::length(off_t _pos, size_t _lenght) {
        length_ = _lenght;
        seek(_pos, xcom_seek_start);
    }
    
    void*  xcom_auto_buffer::ptr(off_t _offset) {
        return (char*)parray_ + _offset;
    }
    
    const void*  xcom_auto_buffer::ptr(off_t _offset) const {
        return (const char*)parray_ + _offset;
    }
    
    void* xcom_auto_buffer::posPtr() {
        return ((unsigned char*) ptr()) + pos();
    }
    
    const void* xcom_auto_buffer::posPtr() const {
        return ((unsigned char*) ptr()) + pos();
    }
    
    off_t xcom_auto_buffer::pos() const {
        return pos_;
    }
    
    size_t xcom_auto_buffer::posLength() const {
        return length_ - pos_;
    }
    
    size_t xcom_auto_buffer::length() const {
        return length_;
    }
    
    size_t xcom_auto_buffer::capacity() const {
        return capacity_;
    }
    
    void xcom_auto_buffer::attach(void *_pbuffer, size_t _len) {
        reset();
        parray_ = (unsigned char*)_pbuffer;
        length_ = _len;
        capacity_ = _len;
    }
    
    void xcom_auto_buffer::attach(xcom_auto_buffer &_rhs) {
        reset();
        parray_ = _rhs.parray_;
        pos_ = _rhs.pos_;
        length_ = _rhs.length_;
        capacity_ = _rhs.capacity_;
        
        _rhs.parray_ = NULL;
        _rhs.reset();
    }
    
    void* xcom_auto_buffer::detach(size_t *_plen) {
        unsigned char* ret = parray_;
        parray_ = NULL;
        size_t nLen = length();
        
        if (NULL != _plen)
            *_plen = nLen;
        
        reset();
        return ret;
    }
    
    void xcom_auto_buffer::reset() {
        if (NULL != parray_)
            free(parray_);
        
        parray_ = NULL;
        pos_ = 0;
        length_ = 0;
        capacity_ = 0;
    }
    
    void xcom_auto_buffer::fitSize(size_t _len) {
        if (_len > capacity_) {
            size_t mallocsize = ((_len + malloc_unitsize_ -1)/malloc_unitsize_)*malloc_unitsize_ ;
            
            void* p = realloc(parray_, mallocsize);
            
            if (NULL == p) {
                //            ASSERT2(p, "_len=%" PRIu64 ", m_nMallocUnitSize=%" PRIu64 ", nMallocSize=%" PRIu64", m_nCapacity=%" PRIu64,
                //                    (uint64_t)_len, (uint64_t)malloc_unitsize_, (uint64_t)mallocsize, (uint64_t)capacity_);
                free(parray_);
            }
            
            parray_ = (unsigned char*) p;
            
            //        ASSERT2(_len <= 10 * 1024 * 1024, "%u", (uint32_t)_len);
            //        ASSERT(parray_);
            
            memset(parray_+capacity_, 0, mallocsize-capacity_);
            capacity_ = mallocsize;
        }
    }
}

