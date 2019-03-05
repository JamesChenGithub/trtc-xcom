//
// Created by alexichen on 2018/10/15.
//


#include "xcom_log_impl.h"

#ifdef _WIN32
#define PRIdMAX "lld"
#define snprintf _snprintf
#else
#define __STDC_FORMAT_MACROS
#define PRIdMAX "jd"
#endif

#include <unistd.h>
#include <sys/stat.h>
//#include <common/CTNUtils.h>

#ifdef ANDROID
#include <android/log.h>
#endif



namespace xcom
{

    XLogImpl::~XLogImpl()
    {
        if (_logBuffer)
        {
            delete _logBuffer;
            _logBuffer = NULL;
        }
        
        if (_asyncThread)
        {
            delete _asyncThread;
            _asyncThread = NULL;
        }
        
        if (_logBufferMemory)
        {
            delete[]_logBufferMemory;
            _logBufferMemory = NULL;
        }
    }

    bool XLogImpl::openLog(const char *logDir, const char *cacheDir, const char *prefix, xcom_log_mode mode) {

        if (_logOpened || logDir == NULL || prefix == NULL)
        {
            return false;
        }
        _logDir = logDir;
        _cacheDir = cacheDir == NULL ? logDir : cacheDir;
        _prefix = prefix;
        //确保logDir,cacheDir目录存在
        int islogdirexist = mkdir(logDir, 777);
        int iscachedirexist =  mkdir(cacheDir, 777);
        if (!(islogdirexist == 0 && iscachedirexist == 0))
        {
            return false;
        }

        bool ret = openShareCache();

        if (ret)
        {
            _logBuffer = new xcom_log_buffer(_mmapFile.getPointer(), LOG_MAP_LENGTH);
        }
        else
        {
            mode = xcom_log_mode_sync;
            _logBufferMemory = new char[LOG_MAP_LENGTH];
            _logBuffer = new xcom_log_buffer(_logBufferMemory, LOG_MAP_LENGTH);
        }
        setLogMode(mode);

        xcom_auto_buffer buffer;
        _logBuffer->flush(buffer);

        if (buffer.ptr()) {
            writeTips2File("~~~~~ begin of cache ~~~~~\n");
            log2file(buffer.ptr(), buffer.length());
            writeTips2File("~~~~~ end of cache ~~~~~\n");
        }
        _logOpened = true;
        return true;
    }

    void XLogImpl::setLogMode(xcom_log_mode mode) {
        _mode = mode;
        _conditionAsync.notify_all();
        if (_mode == xcom_log_mode_async) {
            if (_asyncThread == NULL) {
                _asyncThread = new std::thread(std::bind(&XLogImpl::asyncRun, this));
                _asyncThread->detach();
            }
        }
    }

    void XLogImpl::printLog(xcom_log_info &info, const char *log) {

        if (NULL == _logBuffer || !_logOpened) {
            return;
        }
        char temp[16 * 1024] = {0};
        xcom_log_ptr_buffer log_buff(temp, 0, sizeof(temp));
        logFormat(info, log, log_buff);
        if (_consoleOpen) {
#ifdef ANDROID
            __android_log_print(info.level,info.tag ? info.tag : "tag_null", "%s",log ? log : "log_null");
#else
            printf("%s\r\n",log_buff.ptr());
#endif
        }

        if (_mode == xcom_log_mode_sync) {
            if (_logBuffer->getData().length() >= LOG_MAP_LENGTH * 4 / 5) {
                int ret = snprintf(temp, sizeof(temp),
                                   "[F][ _logBuffer.Length() >= LOG_MAP_LENGTH*4/5, len: %d\n",
                                   (int) _logBuffer->getData().length());
                log_buff.length(ret, ret);
            }

            if (!_logBuffer->write(log_buff.ptr(), (size_t) log_buff.length())) {
                return;
            }

            if (_logBuffer->getData().length() >= LOG_MAP_LENGTH * 1 / 3 || (xcom::xcom_log_level_fatal == info.level)) {
                _conditionAsync.notify_all();
            }
        } else {

            xcom_auto_buffer tmp_buff;
            if (_logBuffer->write(log_buff.ptr(), log_buff.length(), tmp_buff)) {
                log2file(tmp_buff.ptr(), tmp_buff.length());
            }
        }

    }

    void XLogImpl::printLogV(xcom_log_info &info, const char *format, ...) {
        char log[4096] = {0};
        va_list va;
        va_start(va, format);
        vsnprintf(log, sizeof(log), format, va);
        va_end(va);

        printLog(info, log);

    }


    void XLogImpl::enableConsoleLog(bool console) {
        _consoleOpen = console;
    }

    void XLogImpl::flushLog() {
        _conditionAsync.notify_all();
    }

    void XLogImpl::closeLog() {
        _logClosed = true;
        _conditionAsync.notify_all();
    }

    void XLogImpl::setLogLevel(xcom_log_level level) {
        _level = level;
    }

    xcom_log_level XLogImpl::getLogLevel() {
        return _level;
    }

    bool XLogImpl::isLogEnabled(xcom_log_level level) {
        return _level <= level;
    }

    void XLogImpl::asyncRun() {
        deleteTimeoutFiles();

        while (true) {

            if (NULL == _logBuffer) {
                break;
            }
            xcom_auto_buffer tmp;
            _logBuffer->flush(tmp);

            if (NULL != tmp.ptr()) {
                log2file(tmp.ptr(), tmp.length());
            }

            if (_logClosed) {
                break;
            }
            std::unique_lock<std::mutex> lock(_mutexAsync);
            _conditionAsync.wait_for(lock, std::chrono::seconds(10 * 60));
        }
        delete _asyncThread;
        _asyncThread = NULL;
    }

    void XLogImpl::deleteTimeoutFiles() {

        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        char sFileName[1024] = {0};
        for (int i = 0; i < 10; i++) {
            std::time_t tt = std::chrono::system_clock::to_time_t(
                    now - std::chrono::hours(24 * (i + 7)));
            struct tm ptm = *localtime(&tt);
            makeLogFileName(ptm, sFileName);
            remove(sFileName);
        }
    }

    bool XLogImpl::openShareCache() {
        char map_file[256] = {0};
        snprintf(map_file, sizeof(map_file), "%s/%s.mmap2", _cacheDir.empty() ? _logDir.c_str() : _cacheDir.c_str(), _prefix.c_str());
        _mmapFile.mmap(map_file, LOG_MAP_LENGTH);
        return _mmapFile.getPointer() != NULL;
    }

    void XLogImpl::writeTips2File(const char *format, ...) {

        if (NULL == format) {
            return;
        }

        char tips_info[4096] = {0};
        va_list ap;
        va_start(ap, format);
        vsnprintf(tips_info, sizeof(tips_info), format, ap);
        va_end(ap);

        xcom_auto_buffer tmp_buff;
        _logBuffer->write(tips_info, strnlen(tips_info, sizeof(tips_info)), tmp_buff);

        log2file(tmp_buff.ptr(), tmp_buff.length());
    }

    void XLogImpl::log2file(const void *data, size_t len) {
        if (NULL == data || 0 == len) {
            return;
        }

        if (openLogFile()) {
            write2file(data, len, _currentLogFile);
            bool tooManyLog = ftell(_currentLogFile) > LOG_MAX_FILE_LENGTH;
            if (xcom_log_mode_async == _mode || tooManyLog) {
                closeLogFile();
            }
            if (tooManyLog) {
                char sFileName[1024] = {0};
                struct tm ptm = *localtime(&_openLogFileTime);
                makeLogFileName(ptm, sFileName);
                std::string logFileName(sFileName);
                std::string tmpFileName = logFileName + ".tmp";
//                toonim::CTNPathUtils::removeFile(tmpFileName);
//                toonim::CTNPathUtils::renameFile(logFileName, tmpFileName);
            }
        }

    }

    bool XLogImpl::write2file(const void *data, size_t len, FILE *file) {
        if (NULL == file) {
            return false;
        }

        long before_len = ftell(file);
        if (before_len < 0) {
            return false;
        }

        if (1 != fwrite(data, len, 1, file)) {
            int err = ferror(file);

            ftruncate(fileno(file), before_len);
            fseek(file, 0, SEEK_END);

            char err_log[256] = {0};
            snprintf(err_log, sizeof(err_log), "\nwrite file error:%d\n", err);

            xcom_auto_buffer tmp_buff;
            _logBuffer->write(err_log, strnlen(err_log, sizeof(err_log)), tmp_buff);

            fwrite(tmp_buff.ptr(), tmp_buff.length(), 1, file);

            return false;
        }

        return true;
    }

    bool XLogImpl::openLogFile() {
        std::unique_lock<std::mutex> lock_file(_logFileMutex);
        struct timeval tv;
        gettimeofday(&tv, NULL);

        time_t now_time = tv.tv_sec;
        tm tm_now = *localtime((const time_t *) &now_time);

        if (NULL != _currentLogFile) {
            tm tm_file = *localtime(&_openLogFileTime);

            if (tm_file.tm_year == tm_now.tm_year && tm_file.tm_mon == tm_now.tm_mon &&
                tm_file.tm_mday == tm_now.tm_mday) {
                return true;
            }
            fclose(_currentLogFile);
            _currentLogFile = NULL;
        }

        static char s_last_file_path[1024] = {0};

        //系统时间被修改,当前时间小于上次的时间
        if (now_time < _openLogFileTime) {
            _openLogFileTime = now_time;
            _currentLogFile = fopen(s_last_file_path, "ab");

            return NULL != _currentLogFile;
        }

        char log_file_path[1024] = {0};
        makeLogFileName(tm_now, log_file_path);

        _currentLogFile = fopen(log_file_path, "ab");

        memcpy(s_last_file_path, log_file_path, sizeof(s_last_file_path));
        _openLogFileTime = now_time;

        return NULL != _currentLogFile;
    }

    void XLogImpl::closeLogFile() {
        std::unique_lock<std::mutex> lock_file(_logFileMutex);
        if (NULL == _currentLogFile) {
            return;
        }
        fclose(_currentLogFile);
        _currentLogFile = NULL;
    }

    void XLogImpl::makeLogFileName(struct tm &_tm, char *filepath) {

        char temp[64] = {0};
        snprintf(temp, 64, "_%d%02d%02d", 1900 + _tm.tm_year, 1 + _tm.tm_mon, _tm.tm_mday);

        std::string log_file_path = _logDir;
        log_file_path += "/";
        log_file_path += _prefix;
        log_file_path += temp;
        log_file_path += LOG_FILE_SUFFIX;

        strncpy(filepath, log_file_path.c_str(), log_file_path.size());
        filepath[log_file_path.size()] = '\0';
        
        printf("Tmail log file:%s\n", log_file_path.c_str());
    }


    void XLogImpl::logFormat(const xcom_log_info &info, const char *logbody, xcom_log_ptr_buffer &log_buff) {
        static const char *levelStrings[] = {
                "UN",
                "DE",
                "V",
                "D",  // debug
                "I",  // info
                "W",  // warn
                "E",  // error
                "F",  // fatal
                "S"
        };

        char temp_time[64] = {0};

        if (0 != info.timeval.tv_sec) {
            time_t sec = info.timeval.tv_sec;
            tm tm = *localtime((const time_t *) &sec);
#ifdef ANDROID
            snprintf(temp_time, sizeof(temp_time), "%d-%02d-%02d %02d:%02d:%02d.%.3ld",
                     1900 + tm.tm_year, 1 + tm.tm_mon, tm.tm_mday,
                      tm.tm_hour, tm.tm_min, tm.tm_sec,
                     info.timev.tv_usec / 1000);
#elif _WIN32
            snprintf(temp_time, sizeof(temp_time), "%d-%02d-%02d %02d:%02d:%02d.%.3d", 1900 + tm.tm_year, 1 + tm.tm_mon, tm.tm_mday,
                tm.tm_hour, tm.tm_min, tm.tm_sec, info.timev.tv_usec / 1000);
#else
        snprintf(temp_time, sizeof(temp_time), "%d-%02d-%02d %02d:%02d:%02d.%.3d", 1900 + tm.tm_year, 1 + tm.tm_mon, tm.tm_mday,
                  tm.tm_hour, tm.tm_min, tm.tm_sec, info.timeval.tv_usec / 1000);
#endif
        }

        int ret = snprintf((char *) log_buff.posPtr(), 1024,
                           "[%s][%s][%lld%s]",  // **CPPLINT SKIP**
                           info.tag ? info.tag : "", temp_time,
                           info.tid, info.tid == info.maintid ? "*" : "");

        log_buff.length(log_buff.pos() + ret, log_buff.length() + ret);

        if (NULL != logbody) {

            size_t bodylen = log_buff.maxLength() - log_buff.length() > 130 ? log_buff.maxLength() -
                                                                              log_buff.length() -
                                                                              130 : 0;
            bodylen = bodylen > 0xFFFFU ? 0xFFFFU : bodylen;
            bodylen = strnlen(logbody, bodylen);
            bodylen = bodylen > 0xFFFFU ? 0xFFFFU : bodylen;
            log_buff.write(logbody, bodylen);
        } else {
            log_buff.write("error!! NULL==_logbody");
        }

        char nextline = '\n';

        if (*((char *) log_buff.posPtr() - 1) != nextline) {
            log_buff.write(&nextline, 1);
        }
    }


}

