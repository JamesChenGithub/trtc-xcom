//
//  xcom_logger_core.cpp
//  PtrBuf
//
//  Created by AlexiChen on 2019/3/11.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#include "xcom_logger_core.h"
#include "xcom_assert.h"

#include <unistd.h>
#include <sys/stat.h>

namespace xcom {
    /**
     *  设置日志参数, 在open之前操作
     *
     */
#define XCOM_LOGGER_TAG "logger"
    void xcom_logger_core::setLogParam(const xcom_logger_param &param) {
        xcom_logger::setLogParam(param);
        // TODO:通知底层处理
    }
    
    void xcom_logger_core::open(xcom_log_mode mode, const char *dir, const char *prefix) {
        XCOM_ASSERT_RETURN(!_log_opened);
        XCOM_ASSERT_RETURN(dir != NULL);
        XCOM_ASSERT_RETURN(prefix != NULL);
        
        xcom_log_set_log_level(_log_param.log_level);
        _logDir = dir;
        
        _prefix = prefix;
        
        //确保logDir,cacheDir目录存在
        mkdir(_logDir.c_str(), 777);
        
        
        bool ret = openShareCache();
        
//        if (ret) {
//            _logBuffer = new TLogBuffer(_mmapFile.getPointer(), LOG_MAP_LENGTH);
//        } else {
//            mode = TLogSync;
//            _logBufferMemory = new char[LOG_MAP_LENGTH];
//            _logBuffer = new TLogBuffer(_logBufferMemory, LOG_MAP_LENGTH);
//        }
//        setLogMode(mode);
//
//        TAutoBuffer buffer;
//        _logBuffer->flush(buffer);
//
//        if (buffer.ptr()) {
//            writeTips2File("~~~~~ begin of cache ~~~~~\n");
//            log2file(buffer.ptr(), buffer.length());
//            writeTips2File("~~~~~ end of cache ~~~~~\n");
//        }
        _log_opened = true;
    }

    
    
    void xcom_logger_core::append(xcom_log_level level, const char *tag, const char *file, const char *func, int line, const char *format, ...) {}
    
    void xcom_logger_core::append(xcom_log_item &info, const char *format, ...) {}
    
    void xcom_logger_core::close() {}
    
    void xcom_logger_core::flush() {}
    
    
    void xcom_logger_core::append(xcom_log_level level, const char *tag, const char *file, const char *func, int line, const char *format, va_list valist) {}
    
    
    bool xcom_logger_core::openShareCache() {
//        char map_file[256] = {0};
//        snprintf(map_file, sizeof(map_file), "%s/%s.cache",
//                 _cacheDir.empty() ? _logDir.c_str() : _cacheDir.c_str(), _prefix.c_str());
//        _mmapFile.mmap(map_file, LOG_MAP_LENGTH);
//        return _mmapFile.getPointer() != NULL;
        return false;
    }
    
}
