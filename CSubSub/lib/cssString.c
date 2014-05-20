//
//  cssString.c
//  CSubSub
//
//  Created by plter on 14-5-20.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include "cssString.h"


static long cssStringGetLength(cssString *_this){
	return _this->_length;
}

static char* cssStringGetCString(cssString * _this){
	return _this->_cstr;
}

static void cssStringOnDelloc(cssString * _this){
	free(_this->_cstr);
    
	logOut("Destroy cssString");
    
	_this->onCssObjectDelloc(_this);
}

static cssString* cssStringAddCString(cssString * _this,char * _other){
	char * tmp = _this->_cstr;
	_this->_length+=strlen(_other);
	_this->_cstr = malloc(_this->_length+1);
    _this->_cstr[0] = '\0';
	strcat(_this->_cstr,tmp);
	strcat(_this->_cstr,_other);
    _this->_cstr[_this->_length] = '\0';
	free(tmp);
    
    return _this;
}

static cssString* cssStringAddCssString(cssString * _this,cssString * _other){
	cssStringAddCString(_this,cssAs(cssString*,_other)->getCString(_other));
    return _this;
}

static cssString* cssStringAddInt(cssString * _this,int value){
    
    char buf[20];
    memset(buf, 0, 20);
    sprintf(buf, "%d",value);
    
    cssStringAddCString(_this, buf);
    
    return _this;
}

static cssString* cssStringAddLong(cssString * _this,long value){
    
    char buf[20];
    memset(buf, 0, 20);
    sprintf(buf, "%ld",value);
    
    cssStringAddCString(_this, buf);
    
    return _this;
}

static cssString* cssStringAddFloat(cssString * _this,float value){
    
    char buf[20];
    memset(buf, 0, 20);
    sprintf(buf, "%f",value);
    
    cssStringAddCString(_this, buf);
    return _this;
}

static char cssStringGetChar(cssString * _this,long index){
    return _this->_cstr[index];
}

cssString* cssStringInitWithCString(cssString * _this,char * cstr){
	cssObjectInit(cssAs(cssObject*,_this));
    
	//config Delloc functions >>>
	_this->onCssObjectDelloc = _this->onDelloc;
	_this->onDelloc = &cssStringOnDelloc;
    
	//config related c string
	_this->_length = strlen(cstr);
	_this->_cstr = malloc(_this->_length+1);
	memset(_this->_cstr,0,_this->_length+1);
	strcpy(_this->_cstr,cstr);
    
	_this->getLength = &cssStringGetLength;
	_this->getCString = &cssStringGetCString;
	_this->addCString = &cssStringAddCString;
	_this->addCssString = &cssStringAddCssString;
    _this->addInt = &cssStringAddInt;
    _this->addLong = &cssStringAddLong;
    _this->addFloat = &cssStringAddFloat;
    _this->getChar = &cssStringGetChar;
    
	logOut("init cssString");
	return _this;
}

cssString* cssStringCreateWithCString(char * cstr){
	return cssStringInitWithCString(cssAlloc(cssString),cstr);
}

cssString* cssStringCreate(){
    return cssStringCreateWithCString("");
}
