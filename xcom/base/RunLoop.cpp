//
//  Runloop.cpp
//  // LogParse
//
//  Created by 陈耀武 on 2018/10/3.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#include "RunLoop.h"


RunLoop::~RunLoop(){
    cancel();
    printf("RunLoop : [%s] dealloc\n", this->m_loopName.c_str());
    // Log("[%s] dealloc", this->m_loopName.c_str());
}
RunLoop::RunLoop(const std::string &loopname)
{
    m_loop_state.store(Loop_Init);
    m_wait_cancel.store(false);
    m_loopName = loopname;
    m_loopThread = std::thread(&RunLoop::mainloop, this);
    m_loopThread.detach();
}


void RunLoop::mainloop(RunLoop *self)
{
    if (self)
    {
        std::string threadname = self->m_loopName;
        // Log("[%s] Thread started", threadname.c_str());
        
        if (self->m_loop_state.load() == Loop_Init) {
            
            self->m_loop_state.store(Loop_Running);
            do
            {
                // Log("[%s] wait task", threadname.c_str());
                
                if (self->m_loop_queue.empty()) {
                    // if had posted task but thread suppend before wait, then the posted not execute immediately
                    std::unique_lock<std::mutex> lock(self->m_loop_mutex);
                    self->m_loop_notify.wait(lock);
                }
                
                
                while (!(self->m_loop_queue.empty()) && (self->isRunning() || self->m_wait_cancel.load()))
                {
                    std::function<void(void)> action = nullptr;
                    {
                        std::unique_lock<std::mutex> qlock(self->m_loop_queue_mutex);
                        action = self->m_loop_queue.front();
                        self->m_loop_queue.pop();
                    }
                    if (action)
                    {
                        action();
                    }
                }
                
            } while(self->isRunning());
        }
        else if (self->isStopped() && self->m_wait_cancel.load())
        {
            // 在waitcancel时，有可能队列还有任务未执行
            while (!(self->m_loop_queue.empty()))
            {
                std::function<void(void)> action = nullptr;
                {
                    std::unique_lock<std::mutex> qlock(self->m_loop_queue_mutex);
                    action = self->m_loop_queue.front();
                    self->m_loop_queue.pop();
                }
                if (action)
                {
                    action();
                }
            }
        }
        
        delete self;
        self = nullptr;
    }
    
}


void RunLoop::cancel()
{
    if (this->isStopped())
    {
        // Log("[%s] has canceled", this->m_loopName.c_str());
        return;
    }

    if (this->isRunning())
    {
        this->m_loop_state.store(Loop_Stopped);
        // Log("[%s] cancel", this->m_loopName.c_str());
        this->m_loop_notify.notify_one();
    }
}

void RunLoop::waitCancel()
{
    m_wait_cancel.store(true);
    cancel();
}

int RunLoop::postTask(std::function<void ()> action)
{
    if (action == nullptr || this->isStopped())
    {
        return -1;
    }
    
    if (action)
    {
        std::unique_lock<std::mutex> qlock(this->m_loop_queue_mutex);
        this->m_loop_queue.push(action);
        
        if (this->isRunning())
        {
            // Log("[%s] post task", this->m_loopName.c_str());
            this->m_loop_notify.notify_one();
        }
    }
    
    return 0;
}


int RunLoop::async(std::function<void(void)> action)
{
    if (action == nullptr || this->isStopped())
    {
        return -1;
    }
    return this->postTask(action);
}

int RunLoop::sync(std::function<void(void)> action)
{
    if (action == nullptr  || this->isStopped())
    {
        return -1;
    }
    // 如果是在当前线程
    std::promise<bool> sync;
    this->postTask([=, &sync](){
        if (action) {
            action();
        }
        sync.set_value(true);
    });
    std::future<bool> f = sync.get_future();
    f.get();
    return 0;
}


