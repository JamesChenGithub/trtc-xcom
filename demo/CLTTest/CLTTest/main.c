//
//  main.m
//  CLTTest
//
//  Created by AlexiChen on 2019/3/1.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#include <stdio.h>
#include <string.h>

typedef int (*Func)(int, int);

int addF(int a, int b){
    return a + b;
}

int decF(int a, int b) {
    return a - b;
}

int mulF(int a, int b) {
    return a * b;
}

int divF(int a, int b) {
    return (int)(a / b);
}


int main (int argc, char **argv)
{
    
    for (int j = 0; j < argc; j++){
        printf("%s ", argv[j]);
    }
    printf("\n");
    
    --argc;
    ++argv;
    
    if (argc == 3) {
        Func func = NULL;
        int a = 0, b = 0;
        int i = 0;
        do {
            if (i == 0)
            {
                char *f = argv[0];
                if (strlen(f) == 1)
                {
                    switch (*f) {
                        case '+':
                            func = addF;
                            break;
                        case '-':
                            func = decF;
                            break;
                        case '*':
                            func = mulF;
                            break;
                        case '/':
                            func = divF;
                            break;
                            
                        default:
                            
                            break;
                    }
                }
                
                
                if (func == NULL) {
                    printf("err func format\n");
                    break;
                }
            }
            else if (i == 1)
            {
                a = atoi(argv[0]);
            }
            else if (i == 2)
            {
                b = atoi(argv[0]);
            }
            i++;
            argc--;
            ++argv;
        }while(argc > 0);
        
        
        int result = func(a , b);
        printf("result = %d\n", result);
    }
    else {
        printf("err cmd format\n");
    }
    
    
    
    
    return 0;
}
