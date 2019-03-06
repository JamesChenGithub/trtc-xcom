//
//  main.m
//  MMPLog
//
//  Created by AlexiChen on 2019/3/6.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "xcom_mmf_stream.h"

__attribute((constructor)) void before_main()
{
    printf("%s/n", __FUNCTION__);
}

__attribute((destructor)) void after_main()
{
    printf("%s/n", __FUNCTION__);
}

using namespace xcom;
int main()
{
    mmf_ostream ofstream("1.txt", if_exists_map_all, if_doesnt_exist_create);
    return 0;
}


