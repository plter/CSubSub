CSubSub
=======

C语言面向对象库

示例代码如下：
```c

#include <stdio.h>
#include "css.h"

int main(int argc, const char * argv[])
{

//    logOn();
    
    cssString * str = cssStringCreateWithCString("Hello World");
    
    // insert code here...
    printf("%s\n",str->getCString(str));
    
    str->release(str);
    return 0;
}

```