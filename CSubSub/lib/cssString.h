//
//  cssString.h
//  CSubSub
//
//  Created by plter on 14-5-20.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#ifndef __CSubSub__cssString__
#define __CSubSub__cssString__

#ifdef __cplusplus
extern "C" {
#endif

#include "cssObject.h"

#define cssStringFields(TYPE) \
    cssObjectFields(TYPE) \
    long _length; \
    char * _cstr; \
    void(*onCssObjectDelloc)(TYPE _this); \
    long (*getLength)(TYPE _this); \
    char*(*getCString)(TYPE _this); \
    TYPE (*addCssString)(TYPE _this,TYPE _other); \
    TYPE (*addCString)(TYPE _this,char * _other); \
    TYPE (*addInt)(TYPE _this,int value); \
    TYPE (*addLong)(TYPE _this,long value); \
    TYPE (*addFloat)(TYPE _this,float value); \
    char (*getChar)(TYPE _this,long index);

cssClass(cssString)

cssString* cssStringInitWithCString(cssString * str,char * cstr);
cssString* cssStringCreateWithCString(char * cstr);
cssString* cssStringCreate();

#ifdef __cplusplus
}
#endif

#endif /* defined(__CSubSub__cssString__) */
