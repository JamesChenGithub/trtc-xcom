//
//  xcom_logger_core.h
//  PtrBuf
//
//  Created by AlexiChen on 2019/3/11.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#ifndef xcom_logger_core_h
#define xcom_logger_core_h

#include "xcom_logger.h"

#include <string>
#include <condition_variable>
#include <mutex>
#include <thread>
#include "xcom_ptrbuf.h"
#include "xcom_mmap_stream.h"

namespace xcom {
    
    class xcom_logger_core : public xcom_logger {
    public:
        xcom_logger_core();
        /**
         *  获取单例
         *  @return xcom_logger 实例
         */
        static xcom_logger& sharedLogger();
        
        /**
         *  设置日志参数, 在open之前操作
         *
         */
        void setLogParam(const xcom_logger_param &param) override;
        
        /**
         *  创建日志
         *  @param mode 模式
         *  @param dir 目录
         *  @param prefix 日志名前缀
         */
        virtual void open(xcom_log_mode mode, const char *dir, const char *prefix) override;
        /**
         *  添加日志
         *  @param level 级别
         *  @param file 文件名
         *  @param func 函数名
         *  @param line 行好
         *  @param format 格式
         */
        virtual void append(xcom_log_level level, const char *tag, const char *file, const char *func, int line, const char *format, ...) override;
        /**
         *  添加日志
         *  @param info 日志信息
         *  @param format 日志格式
         */
        virtual void append(xcom_log_item &info, const char *format, ...) override;
        /**
         *  关闭日志
         */
        virtual void close() override;
        /**
         *  同步日志到文件
         */
        virtual void flush() override;
        
    protected:
        virtual void append(xcom_log_level level, const char *tag, const char *file, const char *func, int line, const char *format, va_list valist) override;
        
    protected:
//        void asyncRun();
        
    private:
        
//        void writeTips2File(const char *_tips_format, ...);
//
//        void deleteTimeoutFiles();
//
        bool openShareCache();
//
//        void log2file(const void *_data, size_t _len);
//
//        bool openLogFile();
//
//        void closeLogFile();
//
//        bool write2file(const void *_data, size_t _len,FILE* _file);
//
//        void makeLogFileName(struct tm &_tm, char *filepath);
//
//        void logFormat(const xcom_log_item &info, const char *logbody, xcom_ptrbuf &_log);
        

    private:
        
        std::string _logDir;
        
        std::string _prefix;
        
        FILE *_currentLogFile;
        
        time_t _openLogFileTime;
        
        bool _log_opened = true;
        
        mmap_astream _mmapFile;
        
        xcom_ptrbuf     *_logBuffer = NULL;
        char *_logBufferMemory = NULL;
        
        std::condition_variable _conditionAsync;
        std::mutex _mutexAsync;
        
        std::mutex _logFileMutex;
        
        std::thread *_asyncThread;
        
    protected:
        static const unsigned int XCOM_LOG_MAP_LENGTH;
        static const unsigned int XCOM_LOG_MAX_FILE_LENGTH;
        static const char *XCOM_LOG_FILE_SUFFIX;
        
    };
    
    const unsigned int xcom_logger_core::XCOM_LOG_MAP_LENGTH = 150 * 1024;
    const unsigned int xcom_logger_core::XCOM_LOG_MAX_FILE_LENGTH = 1024 * 1024 * 100;
    const char *xcom_logger_core::XCOM_LOG_FILE_SUFFIX = ".tlog";
    
//    xcom_logger& xcom_logger::sharedLogger() {
//        static xcom_logger_core shared_logger;
//        return shared_logger;
//    }
   
}

#endif /* xcom_logger_core_h */
