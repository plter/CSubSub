//
//  main.c
//  E004UsingArray
//
//  Created by plter on 14-5-21.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include <stdio.h>
#include "css.h"

int main(int argc, const char * argv[])
{
    cssCall(cssSystemGetInstance(), logOn);
    cssArray* arr = cssArrayCreate();
    cssString * str;
    
    for (int i=0; i<200; i++) {
        str = cssStringCreateWithCString("Item ");
        str->addInt(str,i);
        arr->add(arr,cssAs(cssObject*, str));
    }
    
    str = cssStringCreateWithCString("HelloWorld");
    arr->addAt(arr,cssAs(cssObject*, str),3);
    
    cssArrayEach(arr, cssString*, item, {
        printf("%s\n",item->_cstr);
    })

    cssCall(cssSystemGetInstance(), gc);
    return 0;
}

