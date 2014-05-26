//
//  cssSystem.c
//  CSubSub
//
//  Created by plter on 14-5-23.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include "cssSystem.h"


static void cssSystemGc(){
    cssList * l = cssSystemGetInstance()->_pendingReleaseList;
    
    cssObject * obj =NULL;
    while (l->_length) {
        obj = l->get(l,0);
        obj->release(obj);
        l->removeAt(l,0);
    }
}

static void cssSystemOnDelloc(cssSystem * _this){
    _this->_pendingReleaseList->release(_this->_pendingReleaseList);
    
    _this->_onObjectDelloc(_this);
}

static void cssSystemLogOn(){
    cssSystemGetInstance()->_isLogOn = true;
}

static void cssSystemLogOff(){
    cssSystemGetInstance()->_isLogOn = false;
}

static bool cssSystemIsLogOn(){
    return cssSystemGetInstance()->_isLogOn;
}

static cssSystem * cssSystemInit(cssSystem * _this){
    
    cssObjectInit(cssAs(cssObject*, _this));
    
    _this->_isLogOn = false;
    _this->_pendingReleaseList = cssListInit(cssAlloc(cssList));
    _this->gc = &cssSystemGc;
    
    _this->_onObjectDelloc = _this->onDelloc;
    _this->onDelloc = &cssSystemOnDelloc;
    _this->logOff = &cssSystemLogOff;
    _this->logOn = &cssSystemLogOn;
    _this->isLogOn = &cssSystemIsLogOn;
    
    return _this;
}

cssSystem * cssSystemGetInstance(){
    static cssSystem * __ins = NULL;
    
    if (__ins==NULL) {
        __ins = cssSystemInit(cssAlloc(cssSystem));
    }
    
    return __ins;
}