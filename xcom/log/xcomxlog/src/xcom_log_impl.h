//
// Created by alexichen on 2018/10/15.
//
#ifndef XCOM_LOG_IMPL_H
#define XCOM_LOG_IMPL_H
#include "xcom_log.h"
#include <string>
#include <condition_variable>
#include <mutex>
#include <thread>
#include "xcom_log_buffer.h"
#include "xcom_log_cache.h"


namespace xcom {

    class XLogImpl : public XLog {

    public:
        XLogImpl() : _logClosed(false), _consoleOpen(false), _asyncThread(NULL), _level(xcom_log_level_verbose),_logBufferMemory(NULL) {
        }

        virtual ~XLogImpl();

        virtual bool openLog(const char *logDir, const char *cacheDir, const char *prefix, xcom_log_mode mode);

        virtual void setLogMode(xcom_log_mode mode);

        virtual void printLog(xcom_log_info &info, const char *log);

        virtual void printLogV(xcom_log_info &info, const char *format, ...);

        virtual void enableConsoleLog(bool console);

        virtual void flushLog();

        virtual void closeLog();

        virtual void setLogLevel(xcom_log_level level);

        virtual xcom_log_level getLogLevel();

        virtual bool isLogEnabled(xcom_log_level level);

    protected:
        void asyncRun();

    private:
        void writeTips2File(const char *_tips_format, ...);

        void deleteTimeoutFiles();

        bool openShareCache();

        void log2file(const void *_data, size_t _len);

        bool openLogFile();

        void closeLogFile();

        bool write2file(const void *_data, size_t _len,FILE* _file);

        void makeLogFileName(struct tm &_tm, char *filepath);

        void logFormat(const xcom_log_info &_info, const char *_logbody, xcom_log_ptr_buffer &_log);

    public:
        static const unsigned int LOG_MAP_LENGTH;
        static const unsigned int LOG_MAX_FILE_LENGTH;

        static const char *LOG_FILE_SUFFIX;
    private:

        std::string _logDir;

        std::string _cacheDir;

        std::string _prefix;

        FILE *_currentLogFile;

        time_t _openLogFileTime;

        xcom_log_mode _mode;

        xcom_log_level _level;

        bool _consoleOpen;

        bool _logClosed = false;

        bool _logOpened = false;

        xcom_log_cache _mmapFile;

        xcom_log_buffer *_logBuffer = NULL;
        char *_logBufferMemory = NULL;

        std::condition_variable _conditionAsync;
        std::mutex _mutexAsync;

        std::mutex _logFileMutex;

        std::thread *_asyncThread;

    };

    const unsigned int XLogImpl::LOG_MAP_LENGTH = 150 * 1024;
    const unsigned int XLogImpl::LOG_MAX_FILE_LENGTH = 1024 * 1024 * 100;
    const char *XLogImpl::LOG_FILE_SUFFIX = ".xlog";

    XLog& XLog::sharedInstance() {
        static XLogImpl impl;
        return impl;
    }

}

#endif
