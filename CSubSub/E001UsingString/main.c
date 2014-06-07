//
//  main.c
//  E001UsingString
//
//  Created by plter on 14-5-19.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include <stdio.h>
#include "css.h"

int main(int argc, const char * argv[])
{
    
    cssCall(cssSystemGetInstance(), logOn);
    
    cssString * str = cssStringCreateWithCString("Hello World");
    
    // insert code here...
    printf("%s\n",cssCall(str, getCString));
    
    cssCall(cssSystemGetInstance(), gc);
    return 0;
}

