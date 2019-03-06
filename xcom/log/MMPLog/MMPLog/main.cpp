//
//  main.m
//  MMPLog
//
//  Created by AlexiChen on 2019/3/6.
//  Copyright © 2019 AlexiChen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "xcom_mmap_stream.h"
#include <iostream> // for std::cout and std::endl
#include <algorithm> // for std::copy

#include <sstream>
#include <iomanip>

__attribute((constructor)) void before_main()
{
    printf("%s\n", __FUNCTION__);
}

__attribute((destructor)) void after_main()
{
    printf("%s\n", __FUNCTION__);
}

using namespace xcom;


int CopyFile(char const* source, char const* dest, bool overwrite)
{
    // Create a read-only memory-mapped-file for reading the source file.
    xcom::mmap_istream source_mf(source);
    
    // Check that the file has been opened.
    if (! source_mf.is_open()) return 1;
    
    // Check that the contents of the file has been mapped into memory.
    if (! source_mf.data()) return 2;
    
    // Create a writable memory-mapped-file for writing
    // the destination file, with the option to overwrite it or not,
    // if such file already exists.
    
    
    xcom::mmap_ostream dest_mf(dest, overwrite ? xcom::if_exists_map_all : xcom::if_exists_fail, xcom::if_doesnt_exist_create);
    const size_t srcfilesize = source_mf.file_size();
    for (int i = 0; i < 4; i++) {
        
        
        // Check that the file has been opened.
        if (! dest_mf.is_open()) return 3;
        // Map into memory a (new) portion of the file,
        // as large as the source file.
        size_t mapsize = 0;
        if (i == 3) {
            mapsize = srcfilesize - 3*srcfilesize/4;
        } else {
            mapsize = srcfilesize/4;
        }
        // 追加
        dest_mf.map(dest_mf.file_size(), srcfilesize/4);
        
        
        // Check that the contents of the file has been mapped into memory.
        if (! dest_mf.data()) return 4;
        
        // Check that the source buffer has the same size
        // of the destination buffer. It cannot be otherwise.
        //if (source_mf.mapped_size() != dest_mf.mapped_size()) return 5;
        
        // Check that the source file has the same size
        // of the destination file. It cannot be otherwise.
        //if (source_mf.file_size() != dest_mf.file_size()) return 6;
        
        // Copy the source buffer to the destination buffer.
        std::copy(source_mf.data() + srcfilesize * i/4 , source_mf.data() + srcfilesize * i/4 + mapsize, dest_mf.data());
        dest_mf.flush();
    }
    
    return 0;
}

int main()
{
    using namespace std;
    
    // Copy the first file, overwriting the second file,
    // if it already exists.
    // It should always print 0, meaning success.
    //cout << CopyFile("xcom_mmap_stream.h", "copy.tmp", true) << endl;
    
    // Copy the first file to the second file,
    // but only if the second file does not already exist.
    // It should always print 3, meaning failure to open the second file,
    // as here the second file already exists.
    //cout << CopyFile("xcom_mmap_stream.h", "copy.tmp", true) << endl;
    
    
    mmap_astream astr("my.log");
    long size = 0;
    static int index = 0;
    for (int j = 0; j < 10; j++) {
        
        for (int i = index * 100; i < (index + 1) * 100; i++) {
            std::ostringstream ostr;
            ostr << "line : " << std::setw(8) << i << "    :  Copy the first file, overwriting the second file, if it already exists, It should always print 0, meaning success."<< std::endl;
            std::string str = ostr.str();
            size += str.length();
            astr.append(str.c_str(), str.length());
            std::cout << str;
            
            if ((i - index * 100) == 50) {
                astr.append_to_file("date.log");
            }
        }
        astr.flush();
        
        index++;
        
        
    }
    std::cout << "write size : " << size << std::endl;
}

