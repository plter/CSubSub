//
//  cssList.h
//  CSubSub
//
//  Created by plter on 14-5-20.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#ifndef __CSubSub__cssList__
#define __CSubSub__cssList__

#ifdef __cplusplus
extern "C" {
#endif

#include "cssObject.h"

struct _cssListItem{
	cssObject * value;
	struct _cssListItem * pre;
	struct _cssListItem * next;
};

#define cssListFields(TYPE) \
    cssObjectFields(TYPE) \
    struct _cssListItem * _begin; \
    struct _cssListItem * _end; \
    long _length; \
    long (*getLength)(TYPE _this); \
    void (*addAt)(TYPE _this,cssObject *obj,long index);\
    void (*addAtLast)(TYPE _this,cssObject* obj); \
    void (*addAtFirst)(TYPE _this,cssObject * obj); \
    void (*removeAt)(TYPE _this,long index); \
    void (*removeFirst)(TYPE _this); \
    void (*removeLast)(TYPE _this); \
    void (*remove)(TYPE _this,cssObject* obj); \
    cssObject * (*get)(TYPE _this,long index); \
    void (*_onCssObjectDelloc)(TYPE _this); \
    void (*clear)(TYPE _this); \
    void (*removeListItem)(TYPE,struct _cssListItem *); \
    void (*addListItem)(TYPE,struct _cssListItem *);

cssClass(cssList)

cssList* cssListInit(cssList * _this);
    cssCreateFunc(cssList);
    
#define cssListEach(list,type,obj,code) {\
    type obj = NULL; \
    for (struct _cssListItem * item = list->_begin; list->_length>0&&item!=list->_end; item=item->next) {\
        obj = (type)(item->value) ; \
        code \
    }\
}

#ifdef __cplusplus
}
#endif

#endif /* defined(__CSubSub__cssList__) */
