//
//  main.c
//  E003UsingList
//
//  Created by plter on 14-5-20.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include <stdio.h>
#include "css.h"

int main(int argc, const char * argv[])
{

    logOn();
    
    cssList * l = cssListCreate();
    
    cssString * str;
    for (int i=0; i<5; i++) {
        str = cssStringCreateWithCString("Item ");
        str->addInt(str,i);
        l->addAtLast(l,cssAs(cssObject*, str));
        str->release(str);
    }
    
    cssListEach(l, cssString*, s, {
        printf("%s\n",s->getCString(s));
    });
    
    l->release(l);
    
    return 0;
}

