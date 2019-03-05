//
//  main.m
//  xcomxlog
//
//  Created by AlexiChen on 2018/10/15.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#include <iostream>

#include "xcom_log.h"
#include <sys/stat.h>
int main(int argc, const char * argv[]) {
    const char *dir = "/Users/alexichen/UnixSpace/xcomxlog/log/";
    int succ = mkdir(dir, 777);
    return 0;
}
