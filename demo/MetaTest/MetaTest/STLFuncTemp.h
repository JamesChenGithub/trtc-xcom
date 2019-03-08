//
//  STLFuncTemp.h
//  MetaTest
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#ifndef STLFuncTemp_h
#define STLFuncTemp_h


template<typename T>
struct OutFunc {
    template<typename U, typename V>
    struct Result{
        
    };
};

//如上我们定义了一个单参元函数OuterFunc，它的返回值是另外一个双参元函数。注意，在调用类或模板内部定义的模板时，标准要求必须使用template关键字。所以我们这样使用OuterFunc的返回值函数：`OuterFunc<int>:: template Result`


// 由于C++标准不允许在类或者模板的内部定义模板的特化，一旦我们定义的内部元函数使用了模板特化，那么就必须定义在外面，再由原来的外层元函数引用。如下：

template<typename U, typename V>
struct InFunc{
    // 主版本实现
};

template<typename T>
struct InFunc<T, T>{
    // 特化版本
};

template <typename T>
struct OuterFunc {
    template<typename U, typename V>
    using Result = InFunc<U, V>;
};


//模式特化，当两个类型相等时，选择特化版本，否则选择非特化版本。
template <typename T, typename U>
struct IsEqual {
    enum {Result = false};
};

template <typename T>
struct IsEqual<T, T> {
    enum {Result = true};
};


template <int N, int M>
struct IsNumEqual {
    enum {Result = false};
};

template <int T>
struct IsNumEqual<T, T> {
    enum {Result = true};
};


#endif /* STLFuncTemp_h */
