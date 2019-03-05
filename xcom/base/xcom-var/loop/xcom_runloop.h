//
//  xcom_runloop.hpp
//  // LogParse
//
//  Created by 陈耀武 on 2018/10/3.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef xcom_runloop_hpp
#define xcom_runloop_hpp

#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>
#include <future>
#include <stdexcept>
#include <sstream>

namespace xcom {
#ifdef __cplusplus
    //    extern "C" {
#endif
class xcom_runloop
{
    
protected:
    enum LoopState{
        Loop_Init,
        Loop_Running,
        Loop_Stopped
    };
protected:
    std::string                             m_loopName = "";
    std::mutex                              m_loop_mutex;
protected:
    std::thread                             m_loopThread;
    std::queue<std::function<void(void)>>   m_loop_queue;
    std::mutex                              m_loop_queue_mutex;
    std::condition_variable                 m_loop_notify;
    
protected:
    std::atomic<LoopState>                  m_loop_state;
    std::atomic<bool>                       m_wait_cancel;
    
protected:
    
    /**
     * 初始化并启动xcom_runloop，如果loopname
     * @param loopname xcom_runloop名称
     */
    xcom_runloop(const std::string &loopname);
    
protected:
    /*
     * 外部使用指针方式时，不需要显示调用析构，直接cancel即可；
     * 外部使用非指针方式时，内部会自己析构
     */
    ~xcom_runloop();
    
protected:
    /**
     * xcom_runloop 线程主循环
     * @param loop 主循环对应的xcom_runloop对像，调用cancel时，内部会自动释放
     */
    static void mainloop(xcom_runloop *loop);
    
protected:
    
    xcom_runloop() = delete;
    xcom_runloop& operator=(const xcom_runloop&) = delete;
    xcom_runloop(const xcom_runloop&) = delete;
    xcom_runloop(const xcom_runloop&&) = delete;
    
protected:
    /**
     * 向线程中投递任务，并解发mainloop开始运行
     * @param action 要执行的任务
     * @return 0 : 投递成功 , -1 投递失败(已调用过cancnel，此时xcom_runloop已停止，或者action为空);
     */
    int postTask(std::function<void(void)> action);
protected:
    
    
    /**
     * 向xcom_runloop中投递任务，xcom_runloop会异步执行action
     * @param action 需要异步执行的任务
     * @return 0 : 投递成功 , -1 投递失败(已调用过cancnel，此时xcom_runloop已停止，或者action为空);
     */
    int async(std::function<void(void)> action);
    
    /**
     * 向xcom_runloop中投递任务，同步等待xcom_runloop执行action
     * @param action 需要等待同步执行的任务
     * @return 0 : 投递成功 , -1 投递失败(已调用过cancnel，此时xcom_runloop已停止，或者action为空);
     */
    int sync(std::function<void(void)> action);
    
public:
    /**
     * 请求xcom_runloop停止执行，队列中未执行的任务不会再执行，可重复调用，但仅首次有效
     */
    void cancel();
    
    /**
     * 请求xcom_runloop停止执行，队列中所有任务执行完才会直接退出，可重复调用，但仅首次有效
     */
    void waitCancel();
    
    
public:
    /**
     * xcom_runloop是否停止
     */
    inline bool isStopped() const {
        return this->m_loop_state.load() == Loop_Stopped;
    }
    
    /**
     * xcom_runloop是否在运行
     */
    inline bool isRunning() const {
        return this->m_loop_state.load() == Loop_Running;
    }
protected:
    /**
     * 同步提交带参数方法，并等待返回值
     * @param f 方法
     * @args f的参数列表
     * @return f的返回值
     */
    template<class F, class... Args>
    auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))>
    {
        // 提交一个任务
        // 调用.get()获取返回值会等待任务执行完,获取返回值
        // 有两种方法可以实现调用类成员，
        // 一种是使用   bind： .commit(std::bind(&CLASS::FUNC, &dog));
        // 一种是用 mem_fn： .commit(std::mem_fn(&CLASS::FUNC), &dog)
        if (this->isStopped())
        {
            std::ostringstream ostr;
            ostr << "commit to xcom_runloop[" << this->m_loopName << "] is stopped" << std::endl;
            throw std::runtime_error(ostr.str());
        }
        using RetType = decltype(f(args...));
        auto task = std::make_shared<std::packaged_task<RetType()> >(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<RetType> future = task->get_future();
        
        {
            std::unique_lock<std::mutex> qlock(this->m_loop_queue_mutex);
            this->m_loop_queue.push([task]{
                (*task)();
            });
        }
        
        if (this->isRunning())
        {
            // Log("[%s] commit task", this->m_loopName.c_str());
            this->m_loop_notify.notify_one();
        }
        
        return future;
    }

};
            
#ifdef __cplusplus
            //    }
#endif
            }

#endif /* xcom_runloop_hpp */
