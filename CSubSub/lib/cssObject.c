//
//  cssObject.c
//  CSubSub
//
//  Created by plter on 14-5-20.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include "cssObject.h"
#include "cssSystem.h"


static void cssFuncImpl(cssObject*,cssObjectRetain){
	_this->_retainCount++;
}

static void cssFuncImpl(cssObject*,cssObjectRelease){
	_this->_retainCount--;
	if (_this->_retainCount<=0) {
		_this->onDelloc(_this);
		cssDelloc(_this);
	}
}

static cssObject * cssFuncImpl(cssObject*,cssObjectAutoRelease){
    cssList * l = cssSystemGetInstance()->_pendingReleaseList;
    l->addAtLast(l,_this);
    return _this;
}

static int cssFuncImpl(cssObject*,cssObjectRetainCount){
	return _this->_retainCount;
}

static void cssFuncImpl(cssObject*,cssObjectOnDelloc){
    //
}


cssObject* cssFuncImpl(cssObject*,cssObjectInit){
    
	_this->_retainCount = 1;
	_this->onDelloc = &cssObjectOnDelloc;
	_this->release = &cssObjectRelease;
    _this->autorelease = &cssObjectAutoRelease;
	_this->retain = &cssObjectRetain;
	_this->retainCount = &cssObjectRetainCount;
    
	return _this;
}

