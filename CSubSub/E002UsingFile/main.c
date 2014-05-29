//
//  main.c
//  E002UsingFile
//
//  Created by plter on 14-5-20.
//  Copyright (c) 2014年 plter. All rights reserved.
//

#include <stdio.h>
#include "css.h"

int main(int argc, const char * argv[])
{

    cssCall(cssSystemGetInstance(), logOn);
    cssString * str = cssStringCreateWithCString("/Users/plter/Work/gitroot/github/CSubSub/CSubSub/Data.txt");
    cssFile * f = cssFileCreate(str);
    cssCallA(f, open, "r");
    
    printf("File Content : %s\n",f->getStringContent(f)->_cstr);
    
    cssCall(cssSystemGetInstance(), gc);
    return 0;
}

