//
//  xcom_log_delc.c
//  PtrBuf
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#ifndef XCOM_DIR_PATH_H
#define XCOM_DIR_PATH_H

#include <string>
#include <vector>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace xcom {
    
    // dir or path util
    class xcom_dir_path {
    public:
        enum xcom_dir_path_type {
            windows_path = 0,
            posix_path = 1,
#if defined(_WIN32)
            native_path = windows_path
#else
            native_path = posix_path
#endif
        };
    protected:
        xcom_dir_path_type _type;       // platform
        bool _wide;                     //
        bool _absolute;
        std::vector<std::string> _path;
        
    public:
        
        xcom_dir_path();
        
        xcom_dir_path(const xcom_dir_path &path);
        
        xcom_dir_path(xcom_dir_path &&path);
        
        xcom_dir_path(const char *string);
        
        xcom_dir_path(const std::string &string);
        
        ~xcom_dir_path();
        
        inline size_t length() const {
            return _path.size();
        }
        
        inline bool empty() const {
            return _path.empty();
        }
        
        bool is_absolute() const {
            return _absolute;
        }
        
        xcom_dir_path make_absolute() const;
        
        bool exists() const;
        
        size_t file_size() const;
        
        bool is_directory() const;
        
        bool is_file() const;
        
        std::string extension() const;
        
        std::string filename() const;
        
        xcom_dir_path parent() const;
        
        std::vector<xcom_dir_path> childs() const;
        
        inline time_t creation_time() const {
            return last_status_change_time();
        }
        
        time_t last_access_time() const;
        
        time_t last_modified_time() const;
        
        time_t last_status_change_time() const;
        
        std::string str(xcom_dir_path_type type = native_path) const;
        
        void set_path_type(const std::string &str, xcom_dir_path_type type = native_path);
        
        xcom_dir_path operator/(const xcom_dir_path &other) const;
        
        xcom_dir_path &operator=(const xcom_dir_path &path);
        
        xcom_dir_path &operator=(xcom_dir_path &&path);
        
        friend std::ostream &operator<<(std::ostream &os, const xcom_dir_path &path);
        
        bool operator==(const xcom_dir_path &p) const;
        
        bool operator!=(const xcom_dir_path &p) const;
        
        bool remove_file() const;
        
        bool resize_file(size_t target_length) const;
        
        bool create_directory() const;
        
        bool is_wide();
        
#if defined(_WIN32)
        xcom_dir_path(const std::wstring &wstring);
        
        xcom_dir_path(const wchar_t *wstring);
        
        std::wstring wstr(xcom_dir_path_type type = native_path) const;
        
        void set_path_type(const std::wstring &wstring, xcom_dir_path_type type = native_path);
        
        xcom_dir_path &operator=(const std::wstring &str);
#endif
        
        // pwd
        static xcom_dir_path getcwd();
        
    protected:
        static std::vector<std::string> tokenize(const std::string &string, const std::string &delim);
        
        
    };
    
}
#endif //XCOM_DIR_PATH_H
