//
//  main.m
//  gx_sed
//
//  Created by Gengxin Gu on 16/4/20.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "GCMain.h"

int main(int argc, const char * argv[]) {
    int res;
    @autoreleasepool {
        res=gcmain(argc, argv);
    }
    return res;
}
