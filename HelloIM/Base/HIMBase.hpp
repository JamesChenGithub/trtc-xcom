//
//  HIMBase.hpp
//  HelloIM
//
//  Created by AlexiChen on 2017/10/10.
//  Copyright © 2017年 AlexiChen. All rights reserved.
//

#ifndef HIMBase_hpp
#define HIMBase_hpp

#include <stdio.h>
#include <iostream>

using namespace HelloIM
{
    
    class HIMBase
    {
    private:
        std::string _moduleName;
        
    protected:
        HIMBase(const std::string mn = ""):_moduleName(mn){
            
        }
        
    private:
    }
    
}


#endif /* HIMBase_hpp */
