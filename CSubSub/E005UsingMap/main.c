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
    
    cssMap * map = cssMapCreate();
    
    map->put(map,"hello",cssAs(cssObject*, cssStringCreateWithCString("Hello")));
    map->put(map,"world",cssAs(cssObject*, cssStringCreateWithCString("World")));
    
    printf("%ld\n",map->getLength(map));
    printf("%s\n",cssAs(cssString*, map->get(map,"world"))->_cstr);
    
    map->remove(map,"hello");
    
    cssSystemGetInstance()->gc();
    return 0;
}

