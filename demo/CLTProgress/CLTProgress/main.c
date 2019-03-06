//
//  main.m
//  CLTProgress
//
//  Created by AlexiChen on 2019/3/6.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <curses.h>
///*
// */
//int main(int argc,char* argv[]){
//    int i;
//    char x[300];
//    memset(x,0,300);
//    for(i=0;i<101;i++){
//        if(i == 100)
//        {
//            sprintf(&x[0],"%3d",i);
//            x[3]='%';
//            x[4+i]='=';
//
//            printf("\r%s=",x);
//            fflush(stdout);
//        }else{
//            sprintf(&x[0],"%2d",i);
//            x[2]='%';
//            x[3+i]='=';
//
//            printf("\r%s>",x);
//            fflush(stdout);
//            usleep(500000);
//        }
//    }
//    printf("\n");
//
//}


//int main(int argc,char* argv[]){
//    int i;
//    const int kMax = 108;
//    const int kPro = 100;
//    char x[kMax];
//    char num[4];
//    memset(x,' ',kMax);
//    x[kMax-1] = '\0';
//    for(i=0;i < kPro+1; i++){
//
//        x[kMax - 2]='%';
//        sprintf(num,"%d",i);
//        int j = 4;
//        int index = 3;
//        while (j > 0) {
//            j--;
//            if (num[j] != '\0') {
//
//                x[kMax - index] = num[j];
//                index++;
//            }
//        }
//        x[i]='=';
//        x[i + 1]='>';
//        printf("\r%s",x);
//        fflush(stdout);
//        usleep(100000);
//    }
//    printf("\n");
//
//}

//int main ( int argc, char *argv[] ) {
//
//    printf("hello,vimer\n");
//    char cursor[4] = {'|','\\','-','/'};
//    int i;
//    for(i = 0; i < 100; ++i)
//    {
//        int k = i%4;
//
//        switch (k)
//        {
//            case 0:
//                printf("\r%c",cursor[0]);
//                fflush(stdout);
//                break;
//
//            case 1:
//                printf("\r%c",cursor[1]);
//
//                fflush(stdout);
//                break;
//
//            case 2 :
//                printf("\r%c",cursor[2]);
//                fflush(stdout);
//                break;
//
//            case 3 :
//                printf("\r%c",cursor[3]);
//                fflush(stdout);
//                break;
//        }
//
//        usleep(500000);
//    }
//    return 0;
//}




//int main ( int argc, char *argv[] ) {
//
//    struct winsize size;
//    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
//    printf("%d\n",size.ws_col);
//    printf("%d\n",size.ws_row);
//    printf("hello,vimer\n");
//
//    if (size.ws_col == 0) {
//        size.ws_col = 120;
//    }
//    int random = rand() % 10;
//    for (int ra = 0; ra < random; ra++) {
//        const int kMax = size.ws_col > 108 ? 108 : size.ws_col - 10;
//        const int kPro = size.ws_col > 108 ? 100 : size.ws_col - 18;
//        char x[kMax];
//        char num[4];
//        memset(x,' ',kMax);
//        char cursor[4] = {'|','\\','-','/'};
//        x[kMax-1] = '\0';
//        for(int k=0;k <= 4*kPro + 1; k++){
//            int i = (int)(100.0 * k/(4*kPro + 1));
//
//            int ci = kPro * i / 100;
//            x[kMax - 2]='%';
//            sprintf(num,"%d",i);
//            int j = 4;
//            int index = 3;
//            while (j > 0) {
//                j--;
//                if (num[j] != '\0') {
//
//                    x[kMax - index] = num[j];
//                    index++;
//                }
//            }
//            if (ci > 0) {
//                x[ci-1]='=';
//            }
//
//            x[ci]= cursor[k%4];
//            printf("\r%s",x);
//            fflush(stdout);
//            usleep((rand()%10) * 2000);
//        }
//        x[kPro-1]= '=';
//        x[kPro]= '=';
//        printf("\r%s",x);
//        fflush(stdout);
//        usleep((rand()%10) * 1000);
//        printf("\n下载完成\n");
//    }
//
//
//
//    return 0;
//}


int main ( int argc, char *argv[] ) {

    
    int random = rand() % 10;
    char x[11];
    memset(x, 0,11);
    char y[11];
    memset(y, 0,11);
    for (int ra = 0; ra < random; ra++) {
        for (int i =0; i < 10; i++) {
            x[i] = '0'+i;
            y[i] = 'a'+i;
        }
        
        printf("%s\n",x);
        printf("%s\n",y);
        usleep(1000 * 1000);
    }



    return 0;
}

