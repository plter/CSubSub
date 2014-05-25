//
//  cssMap.h
//  CSubSub
//
//  Created by plter on 14-5-25.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#ifndef __CSubSub__cssMap__
#define __CSubSub__cssMap__

#ifdef __cplusplus
extern "C" { //c++ header start
#endif
    
#include "cssObject.h"
#include "cssString.h"
#include "cssList.h"
#include <stdbool.h>
    
    
#define cssMapFields(TYPE) \
    cssObjectFields(TYPE) \
    cssList * _kvList; \
    void (*put)(TYPE,char * key,cssObject * value); \
    cssObject* (*get)(TYPE,char *key); \
    bool (*containsKey)(TYPE,char * key); \
    long (*getLength)(TYPE); \
    void (*_onObjectDelloc)(TYPE); \
    void (*remove)(TYPE,char *key);
    
cssClass(cssMap)
    
    cssMap* cssMapInit(cssMap * _this);
    cssCreateFunc(cssMap);
    
    
    
#ifdef __cplusplus
} //c++ header end
#endif


#endif /* defined(__CSubSub__cssMap__) */
