//
//  cssObject.c
//  CSubSub
//
//  Created by plter on 14-5-20.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include "cssObject.h"


static int _isLogOn = 0;

void logOff(){
	_isLogOn = 0;
}
void logOn(){
	_isLogOn = 1;
}
void logOut(char * msg){
	if (_isLogOn) {
		time_t t = time(NULL);
		struct tm* tm = localtime(&t);
		printf("[%d:%d:%d]%s\n",tm->tm_hour,tm->tm_min,tm->tm_sec,msg);
	}
}


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

static int cssObjectRetainCount(cssObject *_this){
	return _this->_retainCount;
}

static void cssObjectOnDelloc(cssObject *_this){
	logOut("Destroy cssObject");
}


cssObject* cssObjectInit(cssObject *_this){
	_this->_retainCount = 1;
	_this->onDelloc = &cssObjectOnDelloc;
	_this->release = &cssObjectRelease;
	_this->retain = &cssObjectRetain;
	_this->retainCount = &cssObjectRetainCount;
    
	logOut("init cssObject");
	return _this;
}

