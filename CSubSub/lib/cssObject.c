//
//  cssObject.c
//  CSubSub
//
//  Created by plter on 14-5-20.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include "cssObject.h"
#include "cssSystem.h"


static void cssObjectRetain(cssObject *_this){
	_this->_retainCount++;
}

static void cssObjectRelease(cssObject *_this){
	_this->_retainCount--;
	if (_this->_retainCount<=0) {
		_this->onDelloc(_this);
		cssDelloc(_this);
	}
}

static cssObject * cssObjectAutoRelease(cssObject * _this){
    cssList * l = cssSystemGetInstance()->_pendingReleaseList;
    l->addAtLast(l,_this);
    return _this;
}

static int cssObjectRetainCount(cssObject *_this){
	return _this->_retainCount;
}

static void cssObjectOnDelloc(cssObject *_this){
    //
}


cssObject* cssObjectInit(cssObject *_this){
    
	_this->_retainCount = 1;
	_this->onDelloc = &cssObjectOnDelloc;
	_this->release = &cssObjectRelease;
    _this->autorelease = &cssObjectAutoRelease;
	_this->retain = &cssObjectRetain;
	_this->retainCount = &cssObjectRetainCount;
    
	return _this;
}

