//
//  cssArray.c
//  CSubSub
//
//  Created by plter on 14-5-21.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include "cssArray.h"
#include "cssSystem.h"


static long cssArrayGetLength(cssArray* _this){
    return _this->_length;
}


static long cssArrayGetCap(cssArray * _this){
    return _this->_cap;
}


static void cssArrayAddAt(cssArray * _this,cssObject * obj,long index){
    
    if (index<0||index>_this->_length) {
        cssSystemLog("%s","cssArrayAddAt:Error, Array index out of bounds");
        return;
    }
    
    if (_this->_length>=_this->_cap) {
        cssObject** tmp = _this->_arr;
        
        _this->_cap*=2;
        _this->_arr = malloc(sizeof(cssObject*)*_this->_cap);
        
        for (long i=0; i<_this->_length; i++) {
            _this->_arr[i] = tmp[i];
        }
        
        free(tmp);
    }
    
    for (long i =_this->_length-1 ; i>=index; i--) {
        _this->_arr[i+1] = _this->_arr[i];
    }
    
    _this->_arr[index] = obj;
    _this->_length++;
    obj->retain(obj);
}

static void cssArrayAdd(cssArray * _this,cssObject * obj){
    cssArrayAddAt(_this, obj, _this->_length);
}

static void cssArrayRemoveAt(cssArray * _this,long index){
    
    if (index<0||index>=_this->_length) {
        cssSystemLog("%s","cssArrayAddAt:Error, Array index out of bounds");
        return;
    }
    
    cssObject * obj = _this->_arr[index];
    
    _this->_length--;
    
    for (long i = index; i<_this->_length; i++) {
        _this->_arr[i] = _this->_arr[i+1];
    }
    
    obj->release(obj);
}

static void cssArrayRemove(cssArray * _this,cssObject * obj){
    for (long i =0; i<_this->_length; i++) {
        if (_this->_arr[i]==obj) {
            cssArrayRemoveAt(_this, i);
            break;
        }
    }
}


static cssObject* cssArrayGet(cssArray * _this,long index){
    if (index<0||index>=_this->_length) {
        cssSystemLog("%s","cssArrayAddAt:Error, Array index out of bounds");
        return NULL;
    }
    
    return _this->_arr[index];
}

static void cssArrayClear(cssArray * _this){
    cssObject * item;
    for (long i = 0; i <_this->_length; i++) {
        item = _this->_arr[i];
        item->release(item);
    }
    _this->_length = 0;
}

static void cssArrayOnDelloc(cssArray * _this){
    
    cssArrayClear(_this);
    
    free(_this->_arr);
    _this->_onCssObjectDelloc(_this);
}


cssArray* cssArrayInitWithCap(cssArray* _this,long cap){
    cssObjectInit(cssAs(cssObject*, _this));
    
    _this->_cap = cap;
    _this->_length = 0;
    _this->_arr = malloc(sizeof(cssObject*)*_this->_cap);
    
    _this->getLength = &cssArrayGetLength;
    _this->getCap = &cssArrayGetCap;
    _this->addAt = &cssArrayAddAt;
    _this->add = &cssArrayAdd;
    _this->removeAt = &cssArrayRemoveAt;
    _this->remove = &cssArrayRemove;
    _this->get = &cssArrayGet;
    _this->_onCssObjectDelloc = _this->onDelloc;
    _this->onDelloc = &cssArrayOnDelloc;
    _this->clear = &cssArrayClear;
    
    return _this;
}


cssArray* cssArrayCreateWithCap(long cap){
    cssArray * _ins = cssArrayInitWithCap(cssAlloc(cssArray), cap);
    _ins->autorelease(_ins);
    return _ins;
}

cssArray* cssArrayCreate(){
    return cssArrayCreateWithCap(64);
}