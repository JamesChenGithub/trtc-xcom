//
//  xcom_logger.h
//  PtrBuf
//
//  Created by AlexiChen on 2019/3/11.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#ifndef xcom_logger_h
#define xcom_logger_h

#include "xcom_compiler_def.h"
#include "xcom_log_delc.h"

#pragma GCC visibility push(default)
namespace xcom {
    
    typedef struct xcom_logger_param {
        xcom_log_level log_level = xcom_log_level_none;             // 日志级别
        xcom_log_mode  log_mode = xcom_log_mode_async;              // 输出方式
        bool console = false;                                      // 控制台输出
        bool compress = false;                                     // 是否压缩
    } xcom_logger_param;
    
    class XCOM_EXPORT_FUNC xcom_logger {
    
    protected:
        xcom_logger_param _log_param;   // 日志参数
    private:
        xcom_logger& operator=(const xcom_logger&) = delete;
        xcom_logger(const xcom_logger&) = delete;
        xcom_logger(const xcom_logger&&) = delete;
    public:
        virtual ~xcom_logger(){}
        
        
        
    public:
        /**
         *  获取单例
         *  @return xcom_logger 实例
         */
        static xcom_logger& sharedLogger();
        
        /**
         *  设置日志参数, 在open之前操作
         *
         */
        virtual void setLogParam(const xcom_logger_param &param);
        /**
         *  获取日志参数
         */
        virtual xcom_logger_param getLogParam() const;
        /**
         *  创建日志
         *  @param mode 模式
         *  @param dir 目录
         *  @param prefix 日志名前缀
         */
        virtual void open(xcom_log_mode mode, const char *dir, const char *prefix) = 0;
        /**
         *  添加日志
         *  @param level 级别
         *  @param file 文件名
         *  @param func 函数名
         *  @param line 行好
         *  @param format 格式
         */
        virtual void append(xcom_log_level level, const char *tag, const char *file, const char *func, int line, const char *format, ...) = 0;
        /**
         *  添加日志
         *  @param info 日志信息
         *  @param format 日志格式
         */
        virtual void append(xcom_log_item &info, const char *format, ...) = 0;
        /**
         *  关闭日志
         */
        virtual void close() = 0;
        /**
         *  同步日志到文件
         */
        virtual void flush() = 0;
    
    protected:
        virtual void append(xcom_log_level level, const char *tag, const char *file, const char *func, int line, const char *format, va_list valist) = 0;
    };
}

#if defined(WIN32)
#define __FILENAME__ (strrchr(__FILE__, '\\') + 1)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') + 1)
#endif

#ifdef DISABLE_LOG

#define XLog(level, tag, fmt, ...)
#define XLogE(tag, fmt, ...)
#define XLogW(tag, fmt, ...)
#define XLogI(tag, fmt, ...)
#define XLogD(tag, fmt, ...)
#define XLogV(tag, fmt, ...)
#define XLogF(tag, fmt, ...)

#else

#define XLog(level, tag, fmt, ...) xcom::xcom_logger::sharedLogger().append(level, tag, __FILENAME__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define XLogE(tag, fmt, ...) XLog(xcom_log_level_error, tag, fmt, ##__VA_ARGS__)
#define XLogW(tag, fmt, ...) XLog(xcom_log_level_warn, tag, fmt, ##__VA_ARGS__)
#define XLogI(tag, fmt, ...) XLog(xcom_log_level_info, tag, fmt, ##__VA_ARGS__)
#define XLogD(tag, fmt, ...) XLog(xcom_log_level_debug, tag, fmt, ##__VA_ARGS__)
#define XLogV(tag, fmt, ...) XLog(xcom_log_level_verbose, tag, fmt, ##__VA_ARGS__)
#define XLogF(tag, fmt, ...) XLog(xcom_log_level_fatal, tag, fmt, ##__VA_ARGS__)

#endif

#pragma GCC visibility pop


#endif /* xcom_logger_h */
