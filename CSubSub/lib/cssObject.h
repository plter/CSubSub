//
//  cssObject.h
//  CSubSub
//
//  Created by plter on 14-5-20.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#ifndef __CSubSub__cssObject__
#define __CSubSub__cssObject__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define cssClass(name) typedef struct name{name##Fields(struct name *)}name;
#define cssAs(type,object) ((type)(object))
#define cssAlloc(__class__) cssAs(__class__ *,malloc(sizeof(__class__)))
#define cssDelloc(object) free(object)
#define cssCreateFunc(__class__) __class__ * __class__##Create()
#define cssCreateFuncImpl(__class__) cssCreateFunc(__class__) { \
    __class__ * _ins = cssAlloc(__class__); \
    if(_ins){ \
        __class__##Init(_ins); \
        _ins->autorelease(_ins); \
    } \
    return _ins; \
}


//TYPE is type of the class that you wanna to create
#define cssObjectFields(TYPE) \
    int _retainCount; \
    void (*retain)(TYPE _this); \
    void (*release)(TYPE _this); \
    TYPE (*autorelease)(TYPE _this); \
    int (*retainCount)(TYPE _this); \
    void (*onDelloc)(TYPE _this);

cssClass(cssObject)

cssObject* cssObjectInit(cssObject *_this);
    
#ifdef __cplusplus
}
#endif

#endif /* defined(__CSubSub__cssObject__) */
