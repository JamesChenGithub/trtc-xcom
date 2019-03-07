//
//  xcom_ptrbuf.h
//  PtrBuf
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#ifndef xcom_ptrbuf_h
#define xcom_ptrbuf_h

#include <sys/types.h>
#include <string.h>

namespace xcom {
    class xcom_ptrbuf {
    public:
        enum xcom_ptrbuf_seek {
            xcom_ptrbuf_seek_start,
            xcom_ptrbuf_seek_cur,
            xcom_ptrbuf_seek_end,
        };
    public:
        xcom_ptrbuf(void *ptr, size_t len, size_t maxlen);
        xcom_ptrbuf(void *ptr, size_t len);
        xcom_ptrbuf();
        ~xcom_ptrbuf();
        
        template<class T>
        void write(const T &val) {
            write(&val, sizeof(val));
        }
        
        template<class T>
        void write(int nPos, const T &val) {
            write(&val, sizeof(val), nPos);
        }
        
        void write(const char *const val) {
            write(val, (unsigned int) strlen(val));
        }
        
        void write(int nPos, const char *const val) {
            write(val, (unsigned int) strlen(val), nPos);
        }
        
        void write(const void *pBuffer, size_t nLen);
        void write(const void *pBuffer, size_t nLen, off_t nPos);
        
        template<class T> void read(T &val)
        { read(&val, sizeof(val)); }
        
        template<class T> void read(int nPos, const T &val) const
        { read(&val, sizeof(val), nPos); }
        
        size_t read(void *pBuffer, size_t nLen);
        size_t read(void *pBuffer, size_t nLen, off_t nPos) const;
        
        void seek(off_t nOffset, xcom_ptrbuf_seek eOrigin = xcom_ptrbuf_seek_cur);
        void length(off_t nPos, size_t nLenght);
        
        void* ptr();
        void* posPtr();
        const void* ptr() const;
        const void* posPtr() const;
        
        off_t pos() const;
        size_t posLength() const;
        size_t length() const;
        size_t maxLength() const;
        
        void attach(void *pBuffer, size_t nLen, size_t maxlen);
        void attach(void *pBuffer, size_t nLen);
        void reset();
        
    private:
        xcom_ptrbuf(const xcom_ptrbuf& rhs);
        xcom_ptrbuf& operator = (const xcom_ptrbuf& rhs);
        
    private:
        unsigned char* parray_;
        off_t pos_;
        size_t length_;
        size_t max_length_;
    };
    
    extern const xcom_ptrbuf KNullPtrBuffer;
}


#endif /* xcom_ptrbuf_h */
