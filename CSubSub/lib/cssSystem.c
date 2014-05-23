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
    
    cssListEach(l, cssObject*, o, { o->release(o); });
    
    l->clear(l);
}

static void cssSystemOnDelloc(cssSystem * _this){
    _this->_pendingReleaseList->release(_this->_pendingReleaseList);
    
    _this->_onObjectDelloc(_this);
}


static cssSystem * cssSystemInit(cssSystem * _this){
    
    logOut(">>>>> init cssSystem >>>>>");
    
    cssObjectInit(cssAs(cssObject*, _this));
    
    _this->_pendingReleaseList = cssListInit(cssAlloc(cssList));
    _this->gc = &cssSystemGc;
    
    _this->_onObjectDelloc = _this->onDelloc;
    _this->onDelloc = &cssSystemOnDelloc;
    
    logOut("<<<<< init cssSystem <<<<<");
    
    return _this;
}

cssSystem * cssSystemGetInstance(){
    static cssSystem * __ins = NULL;
    
    if (__ins==NULL) {
        __ins = cssSystemInit(cssAlloc(cssSystem));
    }
    
    return __ins;
}