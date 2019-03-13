//
//  xcom_logger.cpp
//  PtrBuf
//
//  Created by AlexiChen on 2019/3/11.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#include "xcom_logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
namespace xcom {
    
    
    void xcom_logger::setLogParam(const xcom_logger_param &param)
    {
        _log_param.log_level = param.log_level;
        _log_param.log_mode = param.log_mode;
        _log_param.console = param.console;
        _log_param.compress = param.compress;
    }
    
    xcom_logger_param xcom_logger::getLogParam() const
    {
        xcom_logger_param param;
        param.log_level = _log_param.log_level;
        param.log_mode = _log_param.log_mode;
        param.console = _log_param.console;
        param.compress = _log_param.compress;
        return param;
    }
}
