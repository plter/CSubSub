//
//  cssString.c
//  CSubSub
//
//  Created by plter on 14-5-20.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include "cssString.h"
#include "cssSystem.h"


static long cssFuncImpl(cssString*,cssStringGetLength){
	return _this->_length;
}

static char* cssFuncImpl(cssString*,cssStringGetCString){
	return _this->_cstr;
}

static void cssFuncImpl(cssString*,cssStringOnDelloc){
    
    cssSystemLog("delloc string %s", _this->_cstr);
    
	free(_this->_cstr);
    
	_this->_onCssObjectDelloc(_this);
}

static cssString* cssFuncImplA(cssString*,cssStringAddCString,char * _other){
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

static cssString* cssFuncImplA(cssString*,cssStringAddCssString,cssString * _other){
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
	_this->_onCssObjectDelloc = _this->onDelloc;
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
    
    cssSystemLog("init string %s", cstr);
	return _this;
}

cssString* cssStringCreateWithCString(char * cstr){
    
    cssString * _ins = cssStringInitWithCString(cssAlloc(cssString),cstr);
    _ins->autorelease(_ins);
	return _ins;
}

cssString* cssStringCreate(){
    return cssStringCreateWithCString("");
}
