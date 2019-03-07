//
//  STLPointer.h
//  MetaTest
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#ifndef STLPointer_H
#define STLPointer_H

template <typename T>
struct PointerOf {
    using Result = T*;
};
#define __pointer(...) typename PointerOf<__VA_ARGS__>::Result
template <typename T>
struct Pointer2Of {
    using Result = T**;
    using Result2 = typename PointerOf<typename PointerOf<T>::Result>::Result;
    using Result3 = __pointer(__pointer(T));
};


template<int N, typename T, template<typename> class Func>
struct Times {
    using Result = typename Func<typename Times<N-1, T, Func>::Result>::Result;
};

template<typename T, template<typename> class Func>
struct Times<1, T, Func> {
    using Result = typename Func<T>::Result;
};

using IntPtr3 = typename Times<3, int, PointerOf>::Result;


///////////////////////////
template <int N>
struct CharPointer {
    using Result = typename Times<N, char, PointerOf>::Result;
};

// 元函数转发
template <int N>
struct CharPointerV2 : Times<N, char, PointerOf>{
    
};

template<int N> using CharPointerV3 = Times<N, char, PointerOf>;


//在函数式编程里面，有个概念叫做函数柯里化(currying)，是指一个函数接收部分参数后，并不立即求值，而是继续返回另一个函数。
//我们使用using关键字实现元函数转发，可以达到类似函数柯里化的效果。柯里化可以帮助更容易地复用函数，实现函数之间更低成本且更灵活的组合。
//函数柯里化在函数式编程语言里的意义非常重要，和C++模板元编程里面的还是有区别的。例如在Haskell中，可以不用为柯里化函数定义别名，就直接将其作为另一个函数的参数传递，而在C++模板元编程里目前还做不到。

template<typename T> using Pointer2OfV2 = Times<2, T, PointerOf>;

#endif /* STLPointer_H */
