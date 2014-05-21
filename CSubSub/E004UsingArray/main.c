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
    
    logOn();
    
    cssArray* arr = cssArrayCreate();
    cssString * str;
    
    for (int i=0; i<5; i++) {
        str = cssStringCreateWithCString("Item ");
        str->addInt(str,i);
        arr->add(arr,cssAs(cssObject*, str));
        str->release(str);
    }
    
    str = cssStringCreateWithCString("HelloWorld");
    arr->addAt(arr,cssAs(cssObject*, str),3);
    str->release(str);
    
    cssArrayEach(arr, cssString*, item, {
        printf("%s\n",item->_cstr);
    })
    
    arr->release(arr);

    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

