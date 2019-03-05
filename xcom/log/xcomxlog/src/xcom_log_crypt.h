
#ifndef LOG_CRYPT_H_
#define LOG_CRYPT_H_

#include <stdint.h>
#include <string>

#include "xcom_auto_buffer.h"

namespace xcom {
    

class xcom_log_crypt {
public:
    xcom_log_crypt();
    virtual ~xcom_log_crypt() {}
    
private:
    xcom_log_crypt(const xcom_log_crypt&);
    xcom_log_crypt& operator=(const xcom_log_crypt&);

private:
    static uint32_t getHeaderLen();

    static uint32_t getTailerLen();

    static uint16_t getSeq(bool sync);

public:

    static uint16_t getLogLength(const char *const _data, int32_t _len);

    static uint32_t getValidLength(const char *const _data,int32_t _len);

    void cryptSyncLog(const char *const _log_data, int32_t _input_len, xcom_auto_buffer &_out_buff);
    void cryptAsyncLog(const char *const _log_data, int32_t _input_len, xcom_auto_buffer &_out_buff);
    
private:
    bool is_crypt_;

};

}

#endif /* LOG_CRYPT_H_ */
