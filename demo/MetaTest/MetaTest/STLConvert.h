//
//  STLConvert.h
//  MetaTest
//
//  Created by AlexiChen on 2019/3/8.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#ifndef STLConvert_h
#define STLConvert_h

#include "STLFuncTemp.h"
#define __int(v) typename IntType<v>::Result
#define __bool(...) typename BoolType<__VA_ARGS__>::Result
#define __true() typename TrueType::Result
#define __false() typename FalseType::Result

__int(4);
__int(6);
__bool(true);

#define __is_eq(...) typename IsEqual2<__VA_ARGS__>::Result

____print(__is_eq(__int(4), __int(4)));
____print(__is_eq(__int(4), __int(5)));
____print(__is_eq(__int(4), __bool(true)));


template <typename T>
struct Value {
    enum {Result = T::Value};
};

#define __value(...) Value<__VA_ARGS__>::Result


///////////////////////////////////

template <typename Condition, typename Then, typename Else> struct IfThenElse;


template <typename Then, typename Else>
struct IfThenElse<TrueType, Then, Else> {
    using Result = Then;
};

template <typename Then, typename Else>
struct IfThenElse<FalseType, Then, Else> {
    using Result = Else;
};

#define __if(...) typename IfThenElse<__VA_ARGS__>::Result
///////////////////////////////////
//IsConvertible :: (typename T -> typename U) -> BoolType
template<typename T, typename U>
struct IsConvertible {
private:
    using YES = char;
    struct NO { char dummy[2];};
    
    static YES test(U);
    static NO test(...);
    static T self();
    
public:
    using Result = BoolType<(sizeof(test(self())) == sizeof(YES))>;
};

#define __is_convertible(...) typename IsConvertible<__VA_ARGS__>::Result

__is_convertible(char, int);   // 返回__true()
__is_convertible(char, void*);// 返回__false()
__is_convertible(char*, void*);// 返回__true()


struct Base{};
struct Derived : Base {};

__is_convertible(Base*, Derived*); // 返回__false()
__is_convertible(Derived*, Base*); // 返回__true()

#endif /* STLConvert_h */
