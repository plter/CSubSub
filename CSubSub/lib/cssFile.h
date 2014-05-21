//
//  cssFile.h
//  CSubSub
//
//  Created by plter on 14-5-20.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#ifndef __CSubSub__cssFile__
#define __CSubSub__cssFile__

#ifdef __cplusplus
extern "C" {
#endif

#include "cssObject.h"
#include "cssString.h"
#include <stdbool.h>

#define cssFileFields(TYPE) \
    cssObjectFields(TYPE) \
    cssString *_fileName; \
    FILE * _currentCFile;\
    long _size; \
    cssString * _stringContent; \
    cssString * (*getFileName)(TYPE _this); \
    void(*onCssObjectDelloc)(TYPE _this); \
    bool(*open)(TYPE _this,char * mode); \
    long(*getSize)(TYPE _this); \
    void(*close)(TYPE _this); \
    cssString* (*getStringContent)(TYPE _this);


cssClass(cssFile)

cssFile * cssFileInit(cssFile * _this,cssString * fileName);
cssFile * cssFileCreate(cssString * fileName);
    
#ifdef __cplusplus
}
#endif

#endif /* defined(__CSubSub__cssFile__) */
