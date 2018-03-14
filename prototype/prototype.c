#include "kern.h"

const char *foo = "hello world\n";

int run()
{
    putstr(foo);
    return 0;
}

