//
//  main.m
//  MetaTest
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#include <iostream>
#include "STLStack.h"
#include "STLFunc.h"
#include <queue>
#include "STLPointer.h"
#include "STLFuncTemp.h"



int main()
{
    {
        Stack<int> intStack;
        intStack.push(-1);
        intStack.push(2);
        intStack.push(-3);
        std::cout << intStack.pop() << std::endl;
    }
    {
        Stack<char> charStack;
        charStack.push('A');
        charStack.push('B');
        std::cout << charStack.pop() << std::endl;
    }
    {
        Stack<int> intStack;
        intStack.push(-1);
        intStack.push(2);
        intStack.push(-3);
        std::cout << intStack.pop() << std::endl;
    }
    
    {
        Stack<int, Array> intStack;
        intStack.push(-1);
        intStack.push(2);
        intStack.push(-3);
        std::cout << intStack.pop() << std::endl;
        std::cout << intStack.pop() << std::endl;
        std::cout << intStack.pop() << std::endl;
    }
    {
        const int a = 101;
        const int b = 1;
        std::cout << Plus<a, b>::Value << std::endl;
    }
    
    {
        MType<const char>::Type hello = "Hello world";
        MType<const char>::Ptr hello2 = "Hello world";
        std::cout << hello << hello2 << std::endl;
    }
    
    {
        std::cout << Factorial<10>::value << std::endl;
        std::cout << Factorial2<10>::value << std::endl;
    }
    
    {
        int i = 100;
        PointerOf<int>::Result pi = &i;
        Pointer2Of<int>::Result ppi = &pi;
        Pointer2Of<int>::Result2 ppi2 = &pi;
        
        Times<3, int, PointerOf>::Result pppi = &ppi2;
        IntPtr3 pppi3 = pppi;
        Times<4, int, PointerOf>::Result ppppi = &pppi;
        
    }
    
    {
        OutFunc<int>::Result<int, long> a;
    }
    return  0;
}
