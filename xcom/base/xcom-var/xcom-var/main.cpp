//
//  main.m
//  xcom_var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#include "xcom_var_type.h"
#include "xcom_var.h"
#include <iostream>

using namespace xcom;
int main(int argc, const char * argv[]) {
    {
        std::cout << "基础参数测试" << std::endl;
        // 基本参数验证
        xcom_var var;
        var = true;
        
        std::cout << var.to_json() << std::endl;
        
        var = (uint8_t)8;
        std::cout << var.to_json() << std::endl;
        
        var = (int8_t)-8;
        std::cout << var.to_json() << std::endl;
        
        var = (uint16_t)16;
        std::cout << var.to_json() << std::endl;
        
        var = (int16_t)-16;
        std::cout << var.to_json() << std::endl;
        
        var = (uint32_t)32;
        std::cout << var.to_json() << std::endl;
        
        var = (int32_t)-32;
        std::cout << var.to_json() << std::endl;
        
        var = (uint64_t)64;
        std::cout << var.to_json() << std::endl;
        
        var = (int64_t)-64;
        std::cout << var.to_json() << std::endl;
        
        var = (float)-64.12121;
        std::cout << var.to_json() << std::endl;
        
        var = (double)-64.212121212121121;
        std::cout << var.to_json() << std::endl;
        
        var = "ab";
        std::cout << var.to_json() << std::endl;
        
        std::string str = "str";
        var = str;
        std::cout << var.to_json() << std::endl;
        
        var = (void *)nullptr;
        std::cout << var.to_json() << std::endl;
    }
    
    {
        std::cout << "operator = 测试" << std::endl;
        xcom_var xv;
        
        xcom_var var;
        var = true;
        xv = var;
        std::cout << xv.to_json() << std::endl;
        
        var = (uint8_t)8;
        xv = var;
        std::cout << xv.to_json() << std::endl;
        
        var = (int8_t)-8;
        xv = var;
        std::cout << xv.to_json() << std::endl;
        
        var = (uint16_t)16;
        xv = var;
        std::cout << xv.to_json() << std::endl;
        
        var = (int16_t)-16;
        xv = var;
        std::cout << xv.to_json() << std::endl;
        
        var = (uint32_t)32;
        xv = var;
        std::cout << xv.to_json() << std::endl;
        
        var = (int32_t)-32;
        xv = var;
        std::cout << xv.to_json() << std::endl;
        
        var = (uint64_t)64;
        xv = var;
        std::cout << xv.to_json() << std::endl;
        
        var = (int64_t)-64;
        xv = var;
        std::cout << xv.to_json() << std::endl;
        
        var = (float)-64.12121;
        xv = var;
        std::cout << xv.to_json() << std::endl;
        
        var = (double)-64.212121212121121;
        xv = var;
        std::cout << xv.to_json() << std::endl;
        
        var = "ab";
        xv = var;
        std::cout << xv.to_json() << std::endl;
        
        std::string str = "str";
        var = str;
        xv = var;
        std::cout << xv.to_json() << std::endl;
        
        var = (void *)nullptr;
        xv = var;
        std::cout << xv.to_json() << std::endl;
    }
    
    {
        std::cout << "operator = 测试" << std::endl;
        xcom_var_ptr vptr(new xcom_var(10));
        std::cout << vptr->to_json() << std::endl;
        
        xcom_var var;
        var = true;
        var = vptr;
        std::cout << var.to_json() << std::endl;
        std::cout << vptr->to_json() << std::endl;
        
        *vptr = "heheh";
        std::cout << var.to_json() << std::endl;
        std::cout << vptr->to_json() << std::endl;
    }
    
    
    return 0;
}
