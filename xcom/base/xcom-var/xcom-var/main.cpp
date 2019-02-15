//
//  main.m
//  xcom_var
//
//  Created by AlexiChen on 2019/2/14.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#include "xcom_var_type.h"
#include "xcom_var.h"
#include "xcom_data.h"
#include <iostream>

using namespace xcom;
int main(int argc, const char * argv[]) {
    //    {
    //        std::cout << "基础参数测试" << std::endl;
    //        // 基本参数验证
    //        xcom_var var;
    //        var = true;
    //
    //        std::cout << var.to_json() << std::endl;
    //
    //        var = (uint8_t)8;
    //        std::cout << var.to_json() << std::endl;
    //
    //        var = (int8_t)-8;
    //        std::cout << var.to_json() << std::endl;
    //
    //        var = (uint16_t)16;
    //        std::cout << var.to_json() << std::endl;
    //
    //        var = (int16_t)-16;
    //        std::cout << var.to_json() << std::endl;
    //
    //        var = (uint32_t)32;
    //        std::cout << var.to_json() << std::endl;
    //
    //        var = (int32_t)-32;
    //        std::cout << var.to_json() << std::endl;
    //
    //        var = (uint64_t)64;
    //        std::cout << var.to_json() << std::endl;
    //
    //        var = (int64_t)-64;
    //        std::cout << var.to_json() << std::endl;
    //
    //        var = (float)-64.12121;
    //        std::cout << var.to_json() << std::endl;
    //
    //        var = (double)-64.212121212121121;
    //        std::cout << var.to_json() << std::endl;
    //
    //        var = "ab";
    //        std::cout << var.to_json() << std::endl;
    //
    //        std::string str = "str";
    //        var = str;
    //        std::cout << var.to_json() << std::endl;
    //
    //        var = (void *)nullptr;
    //        std::cout << var.to_json() << std::endl;
    //    }
    //
    //    {
    //        std::cout << "operator = 测试" << std::endl;
    //        xcom_var xv;
    //
    //        xcom_var var;
    //        var = true;
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //
    //        var = (uint8_t)8;
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //
    //        var = (int8_t)-8;
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //
    //        var = (uint16_t)16;
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //
    //        var = (int16_t)-16;
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //
    //        var = (uint32_t)32;
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //
    //        var = (int32_t)-32;
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //
    //        var = (uint64_t)64;
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //
    //        var = (int64_t)-64;
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //
    //        var = (float)-64.12121;
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //
    //        var = (double)-64.212121212121121;
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //
    //        var = "ab";
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //
    //        std::string str = "str";
    //        var = str;
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //
    //        var = (void *)nullptr;
    //        xv = var;
    //        std::cout << xv.to_json() << std::endl;
    //    }
    //
    //    {
    //        std::cout << "operator = 测试" << std::endl;
    //        xcom_var_ptr vptr(new xcom_var(10));
    //        std::cout << vptr->to_json() << std::endl;
    //
    //        xcom_var var;
    //        var = true;
    //        var = vptr;
    //        std::cout << var.to_json() << std::endl;
    //        std::cout << vptr->to_json() << std::endl;
    //
    //        *vptr = "heheh";
    //        std::cout << var.to_json() << std::endl;
    //        std::cout << vptr->to_json() << std::endl;
    //    }
    
    {
        xcom_data var;
//        var["enable"] = true;
//        var["age"] = 18;
        xcom_data content;
        {
            content["sage"]=18;
            //            std::cout << "content :" << content.to_json() << std::endl;
            content["age"]=28;
        }
        //        std::cout << "content :" << content.to_var_json() << std::endl;
        //        std::cout << "content :" << content.to_json() << std::endl;
        
        var["content"] = content;
        std::cout << "var :" << var.to_json() << std::endl;
        content["age"]=100;
        var["content2"] = content;
        std::cout << "var :" << var.to_json() << std::endl;
         content["sage"]=100;
        var["content3"] = content;
        std::cout << "var :" << var.to_json() << std::endl;
        content.erase("sage");
        var["haha"] = content;
        std::cout << "var :" << var.to_json() << std::endl;
        
        
        std::cout << "var :" << var.to_json() << std::endl;
        
    }
    
    {
        xcom_data var;
        
        {
            xcom_data content;
            content["sage"]=18;
            
            content["age"]=28;
             var["content"] = std::move(content);
            std::cout << "var :" << var.to_json() << std::endl;
        }
        
        {
            xcom_data content;
            content["sage2"]=128;
            
            content["age3"]=238;
            var["content2"] = std::move(content);
            std::cout << "var :" << var.to_json() << std::endl;
        }
        
        {
            xcom_data content;
            content["sage2"]=11128;
            
            content["age3"]=22238;
            var["content3"] = std::move(content);
            std::cout << "var :" << var.to_json() << std::endl;
        }
        std::cout << "var :" << var.to_json() << std::endl;
        
    }
    
    {
        xcom_data var;
        
        void *i100 = malloc(100);
        memset(i100, 0, 100);
        var.set_buf(i100, 100);
        memset(i100, 2, 100);
        free(i100);
        std::cout << "var :" << var.to_json() << std::endl;
        
    }
    
    {
        xcom_data var;
        
        
        
    }
    
    //
    return 0;
    
    
    {
        std::cout<<sizeof(xcom_var_value) << "    " << sizeof(double) <<  "    "<<  sizeof(uint64_t)<<  "    " << sizeof(std::string) <<  "    " << sizeof(std::shared_ptr<std::string>)<< "    " << sizeof(xcom_var_buf) << std::endl;;
    }
    {
        xcom_var var;
        var = false;
        std::cout << "var :" << var.to_var_json() << std::endl;
        std::cout << "var :" << var.to_json() << std::endl;
    }
    {
        xcom_var var(false);
        var = 8;
        std::cout << "var :" << var.to_var_json() << std::endl;
        std::cout << "var :" << var.to_json() << std::endl;
    }
    
    {
        xcom_var var(false);
        
        var = "1234";
        std::cout << var.to_json() << std::endl;
        var = 2;
        std::cout << var.to_var_json() << std::endl;
        var = 2.5f;
        std::cout << var.to_var_json() << std::endl;
        var = "121212";
        std::cout << var.to_var_json() << std::endl;
        var = 5.0;
        std::cout << var.to_var_json() << std::endl;
        var = 5u;
        std::cout << var.to_var_json() << std::endl;
        var = (uint64_t)5;
        std::cout << var.to_var_json() << std::endl;
        var = true;
        std::cout << var.to_var_json() << std::endl;
        
        xcom_var a("adasdf");
        var = a;
        
        std::cout << var.to_json() << std::endl;
        
        xcom_var ab("adasdfadadsasdf");
        var = std::move(ab);
        std::cout << var.to_json() << std::endl;
        var = 123u;
        
        std::cout << var.to_json() << std::endl;
    }
    
    {
        xcom_data var;
        var["enable"] = true;
        std::string str = var.to_var_json();
        var["age"] = 100;
        std::cout << "var :" <<  str << std::endl;
        str = var.to_json();
        std::cout << "var :" <<  str << std::endl;
        
        xcom_data content;
        {
            content["age"]=18;
            content["size"]=28;
            content["house"]=38;
            content["house"]=48;
            content["desc"]="qweqwerqwerqwer";
            
            std::cout << "content : " << content.to_json() << std::endl;
        }
        
        var["content"] = content;
        var["content2"] = content;
        
        std::cout << "var :" << var.to_var_json() << std::endl;
        std::cout << "var :" << var.to_json() << std::endl;
        
    }
    
    {
        xcom_data var;
        var["enable"] = true;
        std::string str = var.to_var_json();
        var["age"] = 100;
        std::cout << "var :" <<  str << std::endl;
        str = var.to_json();
        std::cout << "var :" <<  str << std::endl;
        
        xcom_data content;
        {
            content["age"]=18;
            content["size"]=28;
            content["house"]=38;
            content["house"]=48;
            
            std::cout << "content : " << content.to_json() << std::endl;
        }
        
        var["content"] = content;
        var["content2"] = content;
        var["content3"] = content;
        
        std::cout << "var :" << var.to_var_json() << std::endl;
        std::cout << "var :" << var.to_json() << std::endl;
        
    }
    
    {
        //        xcom_data var;
        //
        //        xcom_data content;
        //        {
        //            content["sage"]=18;
        //            content["age"]=18;
        //        }
        //
        //        var.append(content);
        //        std::cout << "var :" << var.to_var_json() << std::endl << std::endl;
        //        std::cout << "var :" << var.to_json() << std::endl << std::endl;
        
        
        //        content["sage"]=28;
        //        content["age"]=28;
        //        var.append(content);
        //
        //        content["sage"]=38;
        //        content["age"]=38;
        //        var.append(content);
        //
        //        content["sage"]=48;
        //        content["age"]=48;
        //        var.append(content);
        //
        //
        //        std::cout << "var :" << var.to_var_json() << std::endl << std::endl;
        //        std::cout << "var :" << var.to_json() << std::endl << std::endl;
        
    }
    
    return 0;
}
