//
//  git.c
//  git
//
//  Created by AlexiChen on 2019/3/1.
//  Copyright © 2019年 AlexiChen. All rights reserved.
//

#include <stdio.h>
#include <string.h>


void version() {
    printf("version      1.2.3\n");
}

void clone() {
    printf("clone      Clone a repository into a new directory\n");
}

void init() {
    printf("init       Create an empty Git repository or reinitialize an existing one\n");
}

int main (int argc, char **argv)
{
    
    for (int j = 0; j < argc; j++){
        printf("%s ", argv[j]);
    }
    printf("\n");
    
    --argc;
    ++argv;
    
    if (argc > 0 ) {
        do {
            char *ar = *argv;
            if (*ar == '-') {
                ar++;
                char par = (*argv)[1];
                
                switch (par) {
                    case 'i':
                        init();
                        break;
                        
                    case 'v':
                        version();
                        break;
                        
                    case 'c':
                        clone();
                        break;
                        
                    case '-':
                    {
                        
                        ar++;
                        int len = strlen(ar);
                        if (len > 2) {
                            if (strcmp(ar, "version") == 0) {
                                version();
                            }
                            else if (strcmp(ar, "clone") == 0) {
                                clone();
                            }
                            else if (strcmp(ar, "init") == 0) {
                                init();
                            }
                            else {
                                printf("err cmd format\n");
                            }
                        }
                
                
                    }
                        break;
                        
                    default:
                        break;
                }
            }
            
            
            --argc;
            ++argv;
        } while(argc > 0);
    }
    else {
        printf("err cmd format\n");
    }
}
