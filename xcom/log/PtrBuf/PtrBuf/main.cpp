//
//  main.m
//  PtrBuf
//
//  Created by AlexiChen on 2019/3/7.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#include "xcom_dir_path.h"
#include <iostream>
#include <fstream>

using namespace std;
int main(int argc, const char * argv[]) {
    
    ifstream inf("data.txt", ios::in);
    
    ofstream outf1("simple.txt");
    
    if (!outf1.is_open()) {
        cout << "simple.txt open err" << endl;
    }
    
    ofstream outf2("split.txt");
    
    if (!outf2.is_open()) {
        cout << "split.txt open err" << endl;
    }
    
    if (inf.is_open())
    {
        
        int linenum = 0;
        while (!inf.eof())
        {
            std::string line;
            std::getline(inf, line);
            cout << ++linenum << " : " <<line << endl;
            
            const char *cline = line.c_str();
            size_t len = line.length();
            int pos = 0;
            while (*(cline + len - (++pos)) != '\t' && pos < len) {
                
            }
        
            std::string posstr = (cline + len - (pos) + 1);
            
            cout << linenum << " : " << posstr << endl;
            
            if (posstr.length() > 13) {
                outf2 << line << endl;
            } else {
                outf1 << line << endl;
            }
            
        }
        outf1.flush();
        outf1.close();
        
        outf2.flush();
        outf2.close();
        inf.close();
    }
    return 0;
}


