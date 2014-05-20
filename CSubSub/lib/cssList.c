//
//  cssList.c
//  CSubSub
//
//  Created by plter on 14-5-20.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include "cssList.h"

static cssListItem* createAndInitCssListItem(){
	cssListItem * i = cssAlloc(cssListItem);
	i->next = NULL;
	i->pre = NULL;
	i->value = NULL;
	return i;
}

static long cssListGetLength(cssList * _this){
	return _this->_length;
}

static cssObject * cssListGet(cssList * _this,long index){
    
	if (index<0||index>=_this->_length) {
		logOut("cssListGet:index out of bounds");
		return NULL;
	}
    
	cssListItem * tmp = _this->_begin;
	long i = 0;
	if (index<_this->_length/2) {
		for (i = 0; i < index; ++i) {
			tmp = tmp->next;
		}
	}else{
		for (i = _this->_length-1; i <= index; ++i) {
			tmp = tmp->pre;
		}
	}
    
	return tmp->value;
}

static void cssListAddAt(cssList * _this,cssObject * obj,long index){
    
	if (index<0||index>_this->_length) {
		logOut("cssListAddAt:index out of bounds");
		return;
	}
    
	if (_this->_begin->value!=NULL) {
		cssListItem * newItem = createAndInitCssListItem();
        
		if (index==_this->_length) {
			newItem->value = obj;
			newItem->pre = _this->_begin->pre;
			newItem->next = _this->_begin;
		}else if (index==0) {
			//switch value with begin
			newItem->value = _this->_begin->value;
			_this->_begin->value = obj;
			//add after begin
			newItem->pre = _this->_begin;
			newItem->next = _this->_begin->next;
		}else{
			cssListItem * tmp = _this->_begin;
			long i = 0;
			if (index<_this->_length/2) {
				for (i = 0; i < index; ++i) {
					tmp=tmp->next;
				}
			}else{
				for (i = _this->_length-1; i >= index; --i) {
					tmp=tmp->pre;
				}
			}
			newItem->next = tmp;
			newItem->pre = tmp->pre;
		}
		//insert new item
		newItem->pre->next = newItem;
		newItem->next->pre = newItem;
	}else{
		_this->_begin->value = obj;
	}
    
	obj->retain(obj);
	_this->_length++;
}

static void cssListAddAtLast(cssList * _this,cssObject * obj){
	cssListAddAt(_this,obj,cssListGetLength(_this));
}

static void cssListAddAtFirst(cssList * _this,cssObject * obj){
	cssListAddAt(_this,obj,0);
}

static void cssListRemoveAt(cssList * _this,long index){
    
	if (index<0||index>=_this->_length||_this->_length<=0) {
		logOut("cssListRemoveAt:index out of bounds");
		return;
	}
    
	cssListItem * tmp = _this->_begin;
	long i=0;
    
    if (index!=0) {
        if (index<_this->_length/2) {
            for (i = 0; i < index; ++i) {
                tmp = tmp->next;
            }
        }else{
            for (i = _this->_length-1; i >=index; --i) {
                tmp=tmp->pre;
            }
        }
        
        tmp->next->pre = tmp->pre;
        tmp->pre->next = tmp->next;
        
        tmp->value->release(tmp->value);
        
        cssDelloc(tmp);
    }else{
        
        _this->_begin->value->release(_this->_begin->value);
        
        //second
        tmp = _this->_begin->next;
        
        if (tmp!=_this->_begin) {
            _this->_begin->value = tmp->value;
            _this->_begin->next = tmp->next;
            _this->_begin->next->pre = _this->_begin;
            
            cssDelloc(tmp);
        }else{
            _this->_begin->value = NULL;
        }
    }
    
    _this->_length--;
}

static void cssListRemoveFirst(cssList * _this){
	cssListRemoveAt(_this,0);
}

static void cssListRemoveLast(cssList * _this){
	cssListRemoveAt(_this,cssListGetLength(_this)-1);
}

static void cssListRemove(cssList * _this,cssObject * obj){
    
	cssListItem * item = _this->_begin;
	cssListItem * tmp = NULL;
    
	while(1){
		if (item->value==obj) {
			obj->release(obj);
            
			item->next->pre = item->pre;
			item->pre->next = item->next;
            
			tmp = item;
			item = item->next;
			cssDelloc(tmp);
			break;
		}
        
		if (item==_this->_begin->pre) {
			break;
		}
        
		item = item->next;
	}
}

static void cssListClear(cssList * _this){
    while(_this->_length){
		cssListRemoveAt(_this,0);
	}
}

static void cssListOnDelloc(cssList * _this){
    
    logOut("destory cssList");
    
	cssListClear(_this);
    
	cssDelloc(_this->_begin);
    
	_this->onCssObjectDelloc(_this);
}

cssList* cssListInit(cssList * _this){
	cssObjectInit(cssAs(cssObject*,_this));
    
	_this->_begin = createAndInitCssListItem();
	_this->_begin->next = _this->_begin;
	_this->_begin->pre = _this->_begin;
    
	_this->_length = 0;
	_this->getLength = &cssListGetLength;
    
	_this->addAtLast = &cssListAddAtLast;
	_this->addAtFirst = &cssListAddAtFirst;
	_this->addAt = &cssListAddAt;
	_this->removeAt = &cssListRemoveAt;
	_this->removeFirst = &cssListRemoveFirst;
	_this->removeLast = &cssListRemoveLast;
	_this->remove = &cssListRemove;
	_this->get = &cssListGet;
    _this->clear = &cssListClear;
    
	_this->onCssObjectDelloc = _this->onDelloc;
	_this->onDelloc = &cssListOnDelloc;
    
    logOut("init cssList");
	return _this;
}

cssList * cssListCreate(){
	return cssListInit(cssAlloc(cssList));
}
