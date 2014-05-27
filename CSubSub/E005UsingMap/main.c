//
//  main.c
//  E005UsingMap
//
//  Created by plter on 14-5-25.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include <stdio.h>
#include "css.h"

int main(int argc, const char * argv[])
{
    cssCall(cssSystemGetInstance(), logOn);
    cssMap * map = cssMapCreate();
    
    cssCallA(map, put, "haha",cssAs(cssObject*, cssStringCreateWithCString("Haha")));
    cssMapPutD(map, "hello", cssStringCreateWithCString("Hello"));
    map->put(map,"world",cssAs(cssObject*, cssStringCreateWithCString("World")));
    
    printf("%ld\n",cssCall(map,getLength));
    printf("%s\n",cssCallRTA(cssString*, map, get,"hello")->_cstr);
    cssSystemLog("%s", cssCallRTA(cssString*, map, get,"haha")->_cstr);
    
    cssCallA(map, remove, "hello");
    
    printf("%ld\n",cssCall(map,getLength));
    
    cssCall(cssSystemGetInstance(), gc);
    return 0;
}

