CSubSub
=======

C语言面向对象库

#为什么要使用C--
1. C--完全使用C语言开发，高效、快速
2. C++越来越复杂，概念越来越多，给人的感觉就像是一个天生有病的人，在后天又用各种方式去治疗，导致这个病人伤痕累累、体无完肤，好像说得有点儿过了，但是事实上是因为C++概念太多，用法太多，学起来太不人性了，爱因斯坦说过，这个世界上任何看似复杂的存在，都有一个简单的解释，那么按这一原则来说，C++设计得太逆天了
3. 用C--可以写出完美的面向对象的程序
4. 一起来拥抱简洁完美的C语言吧


#HelloWorld示例代码如下：
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