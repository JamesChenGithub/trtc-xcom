//
//  STLStack.h
//  MetaTest
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#ifndef STLStack_h
#define STLStack_h

#include <vector>
#include <stdexcept>
#include <string>

//// 模板
//template <typename T>
//class Stack {
//private:
//    std::vector<T> mStack;
//public:
//    void push(const T& item) {
//        mStack.push_back(item);
//    }
//    T pop() {
//        if (empty()) {
//            std::string error = "func : ";
//            error += __FUNCTION__;
//            throw std::out_of_range(error);
//        }
//
//        auto elem = mStack.back();
//        mStack.pop_back();
//        return elem;
//    }
//    bool empty() const {
//        return mStack.empty();
//    }
//
//
//};

//// 默认参数
//template <typename T, typename Container = std::vector<T>>
//class Stack {
//private:
//    Container mStack;
//public:
//    void push(const T& item) {
//        mStack.push_back(item);
//    }
//    T pop() {
//        if (empty()) {
//            std::string error = "func : ";
//            error += __FUNCTION__;
//            throw std::out_of_range(error);
//        }
//
//        auto elem = mStack.back();
//        mStack.pop_back();
//        return elem;
//    }
//    bool empty() const {
//        return mStack.empty();
//    }
//
//
//};

// 模板的模板参数
template<typename T,
template<typename Elemm, typename Allocator = std::allocator<Elemm>> class Container = std::vector>
class Stack {
private:
    Container<T> mStack;
public:
    void push(const T& item) {
        mStack.push_back(item);
    }
    T pop() {
        if (empty()) {
            std::string error = "func : ";
            error += __FUNCTION__;
            throw std::out_of_range(error);
        }
        
        auto elem = mStack.back();
        mStack.pop_back();
        return elem;
    }
    bool empty() const {
        return mStack.empty();
    }
    
    
};


template <typename T, typename Alloctor = std::allocator<T>>
class Array {
protected:
    int size = 0;
    int cap = 20;
    T*  array;
public:
    
    Array():size(0), cap(20){
        array = new T[cap];
    }
    
    ~Array(){
        delete [] array;
        array = nullptr;
    }
    
public:
    void put(const T& t)
    {
        if (size >= cap) {
            std::string error = "func : ";
            error += __FUNCTION__;
            throw std::out_of_range(error);
        }
        array[size++] = t;
    }
    T get() {
        if (size < 0) {
            std::string error = "func : ";
            error += __FUNCTION__;
            throw std::out_of_range(error);
        }
        return array[--size];
    }
    
    bool empty() const {
        return size == 0;
    }
};

template <typename T>
class Stack<T, Array> {
protected:
    
    Array<T> mStack;
    
public:
    Stack(){}
    
    void push(const T& item) {
        mStack.put(item);
    }
    T pop() {
        if (empty()) {
            std::string error = "func : ";
            error += __FUNCTION__;
            throw std::out_of_range(error);
        }
        
        auto elem = mStack.get();
        return elem;
    }
    bool empty() const {
        return mStack.empty();
    }
};


#endif /* STLStack_h */
