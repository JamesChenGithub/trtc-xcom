//
// Created by alexichen on 2018/10/15.
//

#ifndef XCOM_LOG_H
#define XCOM_LOG_H

#include <stdint.h>
#include <time.h>
#include <sys/time.h>

//typedef void (*consolePrint)(const char* tag,const char *format, ...);

namespace xcom {
    
    typedef enum xcom_log_level
    {
        xcom_log_level_verbose,  // 所有信息
        xcom_log_level_debug,    // 调试日志
        xcom_log_level_info,     // 信息日志
        xcom_log_level_warning,  // 警告日志
        xcom_log_level_error,    // 错误日志
        xcom_log_level_fatal,    // 错误日志
        xcom_log_level_none,     // 关掉日志
    } xcom_log_level;
    
    enum xcom_log_mode{
        xcom_log_mode_async = 0,
        xcom_log_mode_sync,
    };
    
    typedef struct xcom_log_info_t
    {
        xcom_log_level      level;
        const char          *tag;
        const char          *file_name;
        const char          *func_name;
        struct timeval      timeval;
        int                 line;
        int64_t             pid;
        int64_t             tid;
        int64_t             maintid;
        const char          *log_content;
    }xcom_log_info;

    class XLog {

    public:

        static XLog& sharedInstance();

        virtual ~XLog(){}

        virtual bool openLog(const char*logDir,const char* cacheDir, const char*prefix,xcom_log_mode mode = xcom_log_mode_async) = 0;

        virtual void setLogMode(xcom_log_mode mode) = 0;

        virtual void printLog(xcom_log_info &info, const char* log) = 0;

        virtual void printLogV(xcom_log_info &info, const char* format ,...) = 0;

        virtual void enableConsoleLog(bool console) = 0;

        virtual void flushLog() = 0;

        virtual void closeLog() = 0;

        virtual void setLogLevel(xcom_log_level level) = 0;

        virtual xcom_log_level getLogLevel() = 0;

        virtual bool isLogEnabled(xcom_log_level level) = 0;

    };

}
#endif
