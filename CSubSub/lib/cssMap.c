//
//  cssMap.c
//  CSubSub
//
//  Created by plter on 14-5-25.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include "cssMap.h"
#include <string.h>
#include "cssSystem.h"

//KV class >>>>>>>>>>>>>>>>>>>>>>>
#define cssMapKVFields(TYPE) \
cssObjectFields(TYPE) \
char * key; \
cssObject * value; \
void (*_onObjectDelloc)(TYPE);

cssClass(cssMapKV)

static void cssMapKVOnDelloc(cssMapKV * _this){
    _this->value->release(_this->value);
    
    _this->_onObjectDelloc(_this);
}

static cssMapKV * cssMapKVInit(cssMapKV * _this,char * key,cssObject * value){
    cssObjectInit(cssAs(cssObject*, _this));
    
    _this->_onObjectDelloc = _this->onDelloc;
    _this->onDelloc = &cssMapKVOnDelloc;
    
    _this->key = key;
    _this->value = value;
    value->retain(value);
    return _this;
}
//KV class <<<<<<<<<<<<<<<<<<<<<<<<<


void cssMapOnDelloc(cssMap * _this){
    
    cssSystemLog("delloc map %lld", (long long)_this);
    
    _this->_kvList->release(_this->_kvList);
    
    _this->_onObjectDelloc(_this);
}

bool cssMapContainsKey(cssMap * _this,char * key){
    cssListEach(_this->_kvList, cssMapKV*, obj, {
        if (strcmp(obj->key, key)==0) {
            return true;
        }
    })
    
    return false;
}

void cssMapPut(cssMap * _this,char * key,cssObject * value){
    if (!cssMapContainsKey(_this, key)) {
        cssMapKV * kv = cssMapKVInit(cssAlloc(cssMapKV), key, value);
        _this->_kvList->addAtLast(_this->_kvList,cssAs(cssObject*,kv));
        kv->release(kv);
    }
}

long cssMapGetLength(cssMap * _this){
    return _this->_kvList->getLength(_this->_kvList);
}

cssObject * cssMapGet(cssMap * _this,char * key){
    cssListEach(_this->_kvList, cssMapKV*, kv, {
        if (strcmp(key, kv->key)==0) {
            return kv->value;
        }
    })
    
    return NULL;
}

void cssMapRemove(cssMap * _this,char *key){
    cssListEach(_this->_kvList, cssMapKV*, kv, {
        if (strcmp(key, kv->key)==0) {
            _this->_kvList->removeListItem(_this->_kvList,item);
            break;
        }
    })
}

cssMap * cssMapInit(cssMap * _this){
    cssObjectInit(cssAs(cssObject*, _this));
    
    _this->_onObjectDelloc = _this->onDelloc;
    _this->onDelloc = &cssMapOnDelloc;
    
    _this->_kvList = cssListInit(cssAlloc(cssList));
    _this->put = &cssMapPut;
    _this->containsKey = &cssMapContainsKey;
    _this->get = &cssMapGet;
    _this->getLength = &cssMapGetLength;
    _this->remove = &cssMapRemove;
    
    cssSystemLog("init map %lld", (long long)_this);
    return _this;
}

cssCreateFuncImpl(cssMap)

