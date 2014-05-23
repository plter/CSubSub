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

#define cssSystemFields(TYPE) \
    cssObjectFields(TYPE) \
    cssList * _pendingReleaseList; \
    void (*gc)(); \
    void (*_onObjectDelloc)(TYPE); 
    
cssClass(cssSystem)

cssSystem * cssSystemGetInstance();

    
#ifdef __cplusplus
} //c++ header end
#endif


#endif /* defined(__CSubSub__cssSystem__) */
