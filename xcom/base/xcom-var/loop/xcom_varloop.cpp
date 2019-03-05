//
//  xcom_varloop.cpp
//  xcom-var
//
//  Created by AlexiChen on 2019/3/5.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#include "xcom_varloop.h"
namespace xcom {
#ifdef __cplusplus
    //    extern "C" {
#endif
    xcom_varloop::~xcom_varloop(){
        
    }
    xcom_varloop::xcom_varloop(const std::string &loopname):xcom_runloop(loopname)
    {
       
    }
    
    int xcom_varloop::postTask(const xcom_data &action)
    {
        if (!action.is_callback()) {
            return -1;
        }
        
        xcom_runloop::postTask([=]{
            action.callback();
        });
        
        return 0;
    }
    
    
    int xcom_varloop::async(const xcom_data &action)
    {
        if (!action.is_callback()) {
            return -1;
        }
        
        return this->postTask(action);
    }

    xcom_data xcom_varloop::sync(const xcom_data &action)
    {
        if (!action.is_callback()) {
            return xcom_data();
        }
        // 如果是在当前线程
        std::promise<xcom_data> sync;
        xcom_runloop::postTask([=, &sync](){
            xcom_data ret = action.callback();
            sync.set_value(ret);
        });
        std::future<xcom_data> f = sync.get_future();
        return f.get();
    }
    
#ifdef __cplusplus
    //    }
#endif
}

