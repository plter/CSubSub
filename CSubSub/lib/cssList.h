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

typedef struct _cssListItem{
	cssObject * value;
	struct _cssListItem * pre;
	struct _cssListItem * next;
} cssListItem;

#define cssListFields(TYPE) \
    cssObjectFields(TYPE) \
    cssListItem * _begin;\
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
    void (*onCssObjectDelloc)(TYPE _this); \
    void (*clear)(TYPE _this);

cssClass(cssList)

cssList* cssListInit(cssList * _this);
cssList * cssListCreate();

#define cssListEach(list,type,obj,code) { \
    cssListItem * item = list->_begin; \
    type obj=NULL; \
    while(1){ \
        obj = (type)(item->value); \
        code \
        item=item->next; \
        if(item==list->_begin){ \
            break; \
        }\
    }\
}
    
#ifdef __cplusplus
}
#endif

#endif /* defined(__CSubSub__cssList__) */
