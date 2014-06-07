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
    void cssFunc(TYPE,_onCssObjectDelloc); \
    long cssFunc(TYPE,getLength); \
    char* cssFunc(TYPE,getCString); \
    TYPE cssFuncA(TYPE,addCssString,TYPE _other); \
    TYPE cssFuncA(TYPE,addCString,char * _other); \
    TYPE cssFuncA(TYPE,addInt,int value); \
    TYPE cssFuncA(TYPE,addLong,long value); \
    TYPE cssFuncA(TYPE,addFloat,float value); \
    char cssFuncA(TYPE,getChar,long index);

cssClass(cssString)

cssString* cssStringInitWithCString(cssString * str,char * cstr);
cssString* cssStringCreateWithCString(char * cstr);
cssString* cssStringCreate();

#ifdef __cplusplus
}
#endif

#endif /* defined(__CSubSub__cssString__) */
