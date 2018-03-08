#include "kern.h"

const char *foo = "hello world";

int run()
{
    putstr(foo);
    putstr(foo);
    putstr(foo);
    putstr(foo);
    putstr(foo);
    putstr(foo);
    return 0;
}

