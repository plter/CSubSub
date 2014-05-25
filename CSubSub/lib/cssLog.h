//
//  cssLog.h
//  CSubSub
//
//  Created by plter on 14-5-25.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#ifndef __CSubSub__cssLog__
#define __CSubSub__cssLog__

#ifdef __cplusplus
extern "C" { //c++ header start
#endif
    
#include "cssObject.h"
#include <stdbool.h>
    
#define cssLogOut(format,args...) {\
        time_t t = time(NULL); \
        struct tm* tm = localtime(&t); \
        printf("[%d:%d:%d]",tm->tm_hour,tm->tm_min,tm->tm_sec); \
        printf(format,args); \
        printf("\n"); \
}
    
    
#ifdef __cplusplus
} //c++ header end
#endif

#endif /* defined(__CSubSub__cssLog__) */
