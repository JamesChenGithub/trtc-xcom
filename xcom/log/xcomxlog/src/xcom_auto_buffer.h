//
// Created by alexichen on 2018/10/15.
//
#ifndef COMM_AUTOBUFFER_H_
#define COMM_AUTOBUFFER_H_

#include <sys/types.h>
#include <string.h>

namespace xcom
{



class xcom_auto_buffer {
  public:
    enum xcom_seek {
        xcom_seek_start,
        xcom_seek_cur,
        xcom_seek_end,
    };

  public:
    explicit xcom_auto_buffer(size_t _size = 128);
    explicit xcom_auto_buffer(void* _pbuffer, size_t _len, size_t _size = 128);
    explicit xcom_auto_buffer(const void* _pbuffer, size_t _len, size_t _size = 128);
    ~xcom_auto_buffer();

    void allocWrite(size_t _readytowrite, bool _changelength = true);
    void addCapacity(size_t _len);

    template<class T> void write(const T &_val)
    { write(&_val, sizeof(_val));}

    template<class T> void write(off_t &_pos, const T &_val)
    { write(_pos, &_val, sizeof(_val));}

    template<class T> void write(const off_t &_pos, const T &_val)
    { write(_pos, &_val, sizeof(_val));}

    void write(const char *const _val)
    { write(_val, strlen(_val));}

    void write(off_t &_pos, const char *const _val)
    { write(_pos, _val, strlen(_val));}

    void write(const off_t &_pos, const char *const _val)
    { write(_pos, _val, strlen(_val));}

    void write(const void *_pbuffer, size_t _len);
    void write(off_t &_pos, const void *_pbuffer, size_t _len);
    void write(const off_t &_pos, const void *_pbuffer, size_t _len);
    void write(xcom_seek _seek, const void *_pbuffer, size_t _len);

    template<class T> size_t read(T &_val)
    { return read(&_val, sizeof(_val)); }

    template<class T> size_t read(off_t &_pos, T &_val) const
    { return read(_pos, &_val, sizeof(_val)); }

    template<class T> size_t read(const off_t &_pos, T &_val) const
    { return read(_pos, &_val, sizeof(_val)); }

    size_t read(void *_pbuffer, size_t _len);
    size_t read(xcom_auto_buffer &_rhs, size_t _len);

    size_t read(off_t &_pos, void *_pbuffer, size_t _len) const;
    size_t read(off_t &_pos, xcom_auto_buffer &_rhs, size_t _len) const;

    size_t read(const off_t &_pos, void *_pbuffer, size_t _len) const;
    size_t read(const off_t &_pos, xcom_auto_buffer &_rhs, size_t _len) const;

    off_t move(off_t _move_len);

    void seek(off_t _offset, xcom_seek _eorigin);
    void length(off_t _pos, size_t _lenght);

    void* ptr(off_t _offset = 0);
    void* posPtr();
    const void* ptr(off_t _offset = 0) const;
    const void* posPtr() const;

    off_t pos() const;
    size_t posLength() const;
    size_t length() const;
    size_t capacity() const;

    void attach(void *_pbuffer, size_t _len);
    void attach(xcom_auto_buffer &_rhs);
    void* detach(size_t *_plen = NULL);

    void reset();

  private:
    void fitSize(size_t _len);

  private:
    xcom_auto_buffer(const xcom_auto_buffer& _rhs);
    xcom_auto_buffer& operator = (const xcom_auto_buffer& _rhs);

  private:
    unsigned char* parray_;
    off_t pos_;
    size_t length_;
    size_t capacity_;
    size_t malloc_unitsize_;
};

extern const xcom_auto_buffer KNullAtuoBuffer;

template <class S> class copy_wrapper_helper;

template <>
class copy_wrapper_helper<xcom_auto_buffer> {
  public:
    static void copy_constructor(xcom_auto_buffer& _lhs, xcom_auto_buffer& _rhs)
    { _lhs.attach(_rhs); }

    static void copy_constructor(xcom_auto_buffer& _lhs, const xcom_auto_buffer& _rhs)
    { _lhs.attach(const_cast<xcom_auto_buffer &>(_rhs)); }

    static void destructor(xcom_auto_buffer& _delobj) {}
};
}
#endif


