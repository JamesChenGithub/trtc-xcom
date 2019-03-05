//
//  xcom_varloop.h
//  xcom-var
//
//  Created by AlexiChen on 2019/3/5.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#ifndef xcom_varloop_h
#define xcom_varloop_h

#include "xcom_runloop.h"
#include "xcom_data.h"

namespace xcom {
#ifdef __cplusplus
    //    extern "C" {
#endif
    class xcom_varloop : public xcom_runloop
    {
        
        
    protected:
        
        /**
         * 初始化并启动xcom_varloop
         * @param loopname xcom_varloop名称
         */
        xcom_varloop(const std::string &loopname);
        
    protected:
        /*
         * 外部使用指针方式时，不需要显示调用析构，直接cancel即可；
         * 外部使用非指针方式时，内部会自己析构
         */
        ~xcom_varloop();
        
    protected:
        
        xcom_varloop() = delete;
        xcom_varloop& operator=(const xcom_runloop&) = delete;
        xcom_varloop(const xcom_runloop&) = delete;
        xcom_varloop(const xcom_runloop&&) = delete;
        
    protected:
        /**
         * 向线程中投递任务，并解发mainloop开始运行
         * @param action 要执行的任务
         * @return 0 : 投递成功 , -1 投递失败(已调用过cancnel，此时xcom_varloop已停止，或者action不为callback);
         */
        int postTask(const xcom_data &action);
        
    public:
        /**
         * 向xcom_varloop中投递任务，xcom_varloop会异步执行action
         * @param action 需要异步执行的任务
         * @return 0 : 投递成功 , -1 投递失败(已调用过cancnel，此时xcom_runloop已停止，或者action不为callback);
         */
        int async(const xcom_data &action);
        
        /**
         * 向xcom_varloop中投递任务，同步等待xcom_varloop执行action
         * @param action 需要等待同步执行的任务
         * @return action.callback()执行结果result : 如果result.is_valied() = true,执行成功 , false 投递失败(已调用过cancnel，此时xcom_varloop已停止，或者action不为callback);
         */
        xcom_data sync(const xcom_data &action);
        
        
        
    };
    
#ifdef __cplusplus
    //    }
#endif
}

#endif /* xcom_varloop_h */
