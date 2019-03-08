//
//  main.m
//  debug-objc
//
//  Created by Closure on 2018/12/4.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSObject *a = [[NSObject alloc] init];
        NSLog(@"%@", a);
        
        NSObject *b = [[NSObject alloc] init];
        NSLog(@"%@", b);
        // insert code here...
        NSLog(@"Hello, World!");
    }
    return 0;
}
