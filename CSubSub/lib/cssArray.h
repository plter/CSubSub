//
//  cssArray.h
//  CSubSub
//
//  Created by plter on 14-5-21.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#ifndef __CSubSub__cssArray__
#define __CSubSub__cssArray__

#ifdef __cplusplus
extern "C" { //c++ header start
#endif

#include "cssObject.h"

#define cssArrayFields(TYPE) \
    cssObjectFields(TYPE) \
    long _length; \
    long _cap; \
    cssObject ** _arr; \
    long (*getLength)(TYPE); \
    long (*getCap)(TYPE); \
    void (*addAt)(TYPE,cssObject * obj,long index); \
    void (*removeAt)(TYPE,long index); \
    void (*add)(TYPE,cssObject * obj); \
    void (*remove)(TYPE,cssObject * obj); \
    cssObject* (*get)(TYPE,long index); \
    void (*_onCssObjectDelloc)(TYPE); \
    void (*clear)(TYPE);

cssClass(cssArray)

cssArray* cssArrayInitWithCap(cssArray* _this,long cap);
cssArray* cssArrayCreateWithCap(long cap);
cssArray* cssArrayCreate();
    
#define cssArrayEach(array,type,obj,code){ \
    type obj; \
    for(long index = 0;index<array->_length;index++){ \
        obj = (type)(array->_arr[index]); \
        code \
    } \
}

#ifdef __cplusplus
} //c++ header end
#endif
#endif /* defined(__CSubSub__cssArray__) */
