#ifndef _MMAP_STREAM_H_
#define _MMAP_STREAM_H_

#include <cstddef>

namespace xcom
{
    unsigned int mmf_granularity();

    class mmap_stream
    {
#if defined(_WIN32)
        typedef void* HANDLE;
#else
        typedef int HANDLE;
#endif
    
    protected:
        char*   data_;
        size_t  offset_;
        size_t  mapped_size_;
        size_t  file_size_;
        int     granularity_;
        HANDLE  file_handle_;
#if defined(_WIN32)
        HANDLE file_mapping_handle_;
#endif
        
    protected:
        size_t  query_file_size_();
    public:
        explicit mmap_stream();
        ~mmap_stream();
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

    // just read
    class mmap_istream: public mmap_stream
    {
    public:
        explicit mmap_istream(char const* pathname = 0, bool map_all = true);
        void open(char const* pathname, bool map_all = true);
        char const* data() const { return data_; }
        void map(size_t offset = 0, size_t size = 0);
    };

    enum mmf_exists_mode
    {
        if_exists_fail,         // fail
        if_exists_just_open,    // just open
        if_exists_map_all,      // open and map
        if_exists_truncate,     // truncate to 0
    };

    enum mmf_doesnt_exist_mode
    {
        if_doesnt_exist_fail,   //  if (not exist) return fail
        if_doesnt_exist_create, //  if (not exist) create and continue
    };

    // write but more complex
    class mmap_ostream: public mmap_stream
    {
    public:
        explicit mmap_ostream(char const* pathname = 0, mmf_exists_mode exists_mode = if_exists_fail, mmf_doesnt_exist_mode doesnt_exist_mode = if_doesnt_exist_create);
        void open(char const* pathname, mmf_exists_mode exists_mode = if_exists_fail, mmf_doesnt_exist_mode doesnt_exist_mode = if_doesnt_exist_create);
        char* data() { return data_; }
        void map(size_t offset = 0, size_t size = 0);
        bool flush();
    };
    
    // append to write
    class mmap_astream: public mmap_ostream
    {
    protected:
        int  map_granularity_count;
    public:
        explicit mmap_astream(char const* pathname = 0, int map_count = 1, mmf_exists_mode exists_mode = if_exists_map_all, mmf_doesnt_exist_mode doesnt_exist_mode = if_doesnt_exist_create);
        // 追加写到mmf文件;
        void append(const char *data, size_t size);
        
        // 将mmf文件追加到pathname尾
        int append_to_file(char const* pathname);
    };
}
#endif // _MMAP_STREAM_H_
