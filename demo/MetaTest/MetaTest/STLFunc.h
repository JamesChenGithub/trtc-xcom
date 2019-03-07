//
//  STLFunc.h
//  MetaTest
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#ifndef STLFunc_h
#define STLFunc_h

template<int X, int Y>
struct Plus
{
    enum { Value = X + Y };
};

template<int Value>
struct Print
{
    operator char()
    {
        return Value + 0xFF; // INVOKE OVERFLOW WARNNING LOG !
    }
};


template<int X, int Y>
struct Caculate
{
    enum
    {
        Sum = X + Y,
        Dec = X - Y,
        Mul = X * Y,
        Div = X / Y
    };
};


template<typename T>
struct MType{
    typedef T* Type;
    using Ptr = T*;
};

//////
template<int N>
struct Factorial{
    enum {value = N * Factorial<N-1>::value};
};

template<>
struct Factorial<1>
{
    enum {value = 1};
};

template<int N>
struct Factorial2{
    enum { value = Factorial2<N-1>::value + Factorial2<N-2>::value };
};

template<>
struct Factorial2<2>
{
    enum {value = 1};
};

template<>
struct Factorial2<1>
{
    enum {value = 1};
};




#define __DO_JOIN(symbol1, symbol2) symbol1##symbol2
#define _JOIN(symbol1, symbol2) __DO_JOIN(symbol1, symbol2)
#define UNIQUE_NAME(prefix) _JOIN(prefix, __LINE__)

#define __print(...) char UNIQUE_NAME(print_value_) = Print<__VA_ARGS__>()

__print(Plus<3, 4>::Value);

__print(Factorial<10>::value);

__print(Factorial2<10>::value);

#endif /* STLFunc_h */
