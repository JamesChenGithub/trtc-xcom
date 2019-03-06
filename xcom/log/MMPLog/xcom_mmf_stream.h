#ifndef _MMP_STREAM_H_
#define _MMP_STREAM_H_

#include <cstddef> // for size_t

namespace xcom
{
    unsigned int mmf_granularity();

    class mmf_stream
    {
#if defined(_WIN32)
        typedef void* HANDLE;
#else
        typedef int HANDLE;
#endif
    protected:
        size_t  query_file_size_();
        char*   data_;
        size_t  offset_;
        size_t  mapped_size_;
        size_t  file_size_;
        int     granularity_;
        HANDLE  file_handle_;
#if defined(_WIN32)
        HANDLE file_mapping_handle_;
#endif
    public:
        explicit mmf_stream();
        ~mmf_stream();
        size_t offset() const { return offset_; }
        size_t mapped_size() const { return mapped_size_; }
        size_t file_size() const { return file_size_; }
        void unmap();
        void close();
        bool is_open() const
        {
            return file_handle_ !=
    #if defined(_WIN32)
            (void*)
    #endif
            -1;
        }        
  
        HANDLE file_handle() const
        {
            return file_handle_;
        }
    
    };

    class mmf_istream: public mmf_stream
    {
    public:
        explicit mmf_istream(char const* pathname = 0, bool map_all = true);
        void open(char const* pathname, bool map_all = true);
        char const* data() const { return data_; }
        void map(size_t offset = 0, size_t size = 0);
    };

    enum mmf_exists_mode
    {
        if_exists_fail,
        if_exists_just_open,
        if_exists_map_all,
        if_exists_truncate,
    };

    enum mmf_doesnt_exist_mode
    {
        if_doesnt_exist_fail,
        if_doesnt_exist_create,
    };

    class mmf_ostream: public mmf_stream
    {
    public:
        explicit mmf_ostream(char const* pathname = 0,
            mmf_exists_mode exists_mode = if_exists_fail,
            mmf_doesnt_exist_mode doesnt_exist_mode = if_doesnt_exist_create);
        void open(char const* pathname,
            mmf_exists_mode exists_mode = if_exists_fail,
            mmf_doesnt_exist_mode doesnt_exist_mode = if_doesnt_exist_create);
        char* data() { return data_; }
        void map(size_t offset = 0, size_t size = 0);
        bool flush();
    };
}
#endif // _MMP_STREAM_H_
