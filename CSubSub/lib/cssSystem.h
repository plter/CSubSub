//
//  cssSystem.h
//  CSubSub
//
//  Created by plter on 14-5-23.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#ifndef __CSubSub__cssSystem__
#define __CSubSub__cssSystem__


#ifdef __cplusplus
extern "C" { //c++ header start
#endif

#include "cssObject.h"
#include "cssList.h"
#include <stdbool.h>

#define cssSystemFields(TYPE) \
    cssObjectFields(TYPE) \
    cssList * _pendingReleaseList; \
    bool _isLogOn; \
    void (*gc)(TYPE); \
    void (*_onObjectDelloc)(TYPE); \
    void (*logOn)(TYPE); \
    void (*logOff)(TYPE); \
    bool (*isLogOn)(TYPE);
    
cssClass(cssSystem)

cssSystem * cssSystemGetInstance();

    
#define cssSystemLog(format,args...) {\
    if(cssCall(cssSystemGetInstance(),isLogOn)){ \
        time_t t = time(NULL); \
        struct tm* tm = localtime(&t); \
        printf("[%d:%d:%d]",tm->tm_hour,tm->tm_min,tm->tm_sec); \
        printf(format,args); \
        printf("\n"); \
    } \
}
    
#ifdef __cplusplus
} //c++ header end
#endif


#endif /* defined(__CSubSub__cssSystem__) */
