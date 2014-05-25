//
//  cssList.c
//  CSubSub
//
//  Created by plter on 14-5-20.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include "cssList.h"
#include "cssLog.h"

static struct _cssListItem* createAndInitCssListItem(){
	struct _cssListItem * i = malloc(sizeof(struct _cssListItem));
	i->next = NULL;
	i->pre = NULL;
	i->value = NULL;
	return i;
}

static void cssListRemoveListItem(cssList * _this,struct _cssListItem * item){
    if (_this->_length<=0) {
        return;
    }
    
    item->next->pre = item->pre;
    if (item->pre!=NULL) {
        item->pre->next = item->next;
    }else{//pre is NULL means this item is _begin
        _this->_begin = item->next;
    }
    
    item->value->release(item->value);
    _this->_length--;
    
    free(item);
    
    if (_this->_length<=0) {//if _length is 0,we must reset _begin to NULL
        _this->_begin = NULL;
    }
}


static void cssListAddListItemBefore(cssList * _this,struct _cssListItem * itemForAdd,struct _cssListItem * item){
    
    itemForAdd->pre = item->pre;
    itemForAdd->next = item;
    item->pre = itemForAdd;
    
    if (itemForAdd->pre!=NULL) {
        itemForAdd->pre->next = itemForAdd;
    }else{
        _this->_begin = itemForAdd;
    }
    
    _this->_length++;
}


static void cssListAddObjectBefore(cssList * _this,cssObject * objForAdd,struct _cssListItem * item){
    struct _cssListItem * newItem = createAndInitCssListItem();
    newItem->value = objForAdd;
    objForAdd->retain(objForAdd);
    cssListAddListItemBefore(_this, newItem, item);
}


static long cssListGetLength(cssList * _this){
	return _this->_length;
}

static struct _cssListItem * cssListGetListItem(cssList * _this,long index){
    if (index<0||index>=_this->_length) {
		cssLogOut("%s","cssListGet:index out of bounds");
		return NULL;
	}
    
	struct _cssListItem * tmp = NULL;
	long i = 0;
	if (index<_this->_length/2) {
        tmp = _this->_begin;
		for (i = 0; i < index; ++i) {
			tmp = tmp->next;
		}
	}else{
        tmp = _this->_end;
		for (i = _this->_length-1; i <= index; ++i) {
			tmp = tmp->pre;
		}
	}
    
    return tmp;
}

static cssObject * cssListGet(cssList * _this,long index){
	return cssListGetListItem(_this,index)->value;
}

static void cssListAddAt(cssList * _this,cssObject * obj,long index){
    
	if (index<0||index>_this->_length) {
		cssLogOut("%s","cssListAddAt:index out of bounds");
		return;
	}
    
    if (_this->_length==0||_this->_length==index) {
        cssListAddObjectBefore(_this, obj, _this->_end);
    }else if(index==0){
        cssListAddObjectBefore(_this, obj, _this->_begin);
    }else{
        cssListAddObjectBefore(_this, obj, cssListGetListItem(_this,index));
    }
}

static void cssListAddAtLast(cssList * _this,cssObject * obj){
	cssListAddAt(_this,obj,cssListGetLength(_this));
}

static void cssListAddAtFirst(cssList * _this,cssObject * obj){
	cssListAddAt(_this,obj,0);
}

static void cssListRemoveAt(cssList * _this,long index){
    
	if (index<0||index>=_this->_length||_this->_length<=0) {
		cssLogOut("%s","cssListRemoveAt:index out of bounds");
		return;
	}
    
	struct _cssListItem * tmp = NULL;
	long i=0;
    
    if (index<_this->_length/2) {
        tmp = _this->_begin;
        for (i = 0; i < index; ++i) {
            tmp = tmp->next;
        }
    }else{
        tmp = _this->_end;
        for (i = _this->_length-1; i >=index; --i) {
            tmp=tmp->pre;
        }
    }
    
    cssListRemoveListItem(_this, tmp);
}

static void cssListRemoveFirst(cssList * _this){
	cssListRemoveAt(_this,0);
}

static void cssListRemoveLast(cssList * _this){
	cssListRemoveAt(_this,cssListGetLength(_this)-1);
}

//TODO
static void cssListRemove(cssList * _this,cssObject * obj){
    
    if (_this->_length<=0) {
        return;
    }
    
    struct _cssListItem * item = _this->_begin;
    struct _cssListItem * tmp = NULL;
    while (item!=_this->_end) {
        if (item->value == obj) {
            tmp = item;
            item = item->next;
            cssListRemoveListItem(_this, tmp);
            break;
        }else{
            item = item->next;
        }
    }
    
}

static void cssListClear(cssList * _this){
    while(_this->_length){
		cssListRemoveAt(_this,0);
	}
}

static void cssListOnDelloc(cssList * _this){
    
	cssListClear(_this);
    
	free(_this->_end);
    
	_this->_onCssObjectDelloc(_this);
}

cssList* cssListInit(cssList * _this){
    
	cssObjectInit(cssAs(cssObject*,_this));
    
	_this->_begin = NULL;
    _this->_end = createAndInitCssListItem();
    
	_this->_length = 0;
	_this->getLength = &cssListGetLength;
    
	_this->addAtLast = &cssListAddAtLast;
	_this->addAtFirst = &cssListAddAtFirst;
	_this->addAt = &cssListAddAt;
	_this->removeAt = &cssListRemoveAt;
	_this->removeFirst = &cssListRemoveFirst;
	_this->removeLast = &cssListRemoveLast;
	_this->remove = &cssListRemove;
    _this->removeListItem = &cssListRemoveListItem;
	_this->get = &cssListGet;
    _this->clear = &cssListClear;
    
	_this->_onCssObjectDelloc = _this->onDelloc;
	_this->onDelloc = &cssListOnDelloc;
	return _this;
}

cssCreateFuncImpl(cssList)
