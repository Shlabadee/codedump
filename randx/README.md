# RANDX

An actually useful library. This is not meant for cryptographic purposes, but it could find use in DSP and video games.

This is a modified version that uses an explicit state rather than the implicit state in the original. This way, compilation across units becomes more management if linked as its own library rather than directly compiled from source.

I'd recommend compiling using the `CMakeLists.txt` file. Afterward, copy `librandx.a` and `randx.h` into whatever project you're working on.

## Example Usage

```c
#include <stdio.h>

#include "include/randx.h"

int main()
{
    RXState state;
    initrxstate(&state, get_rxseed());

    for (int i = 0; i < 10; ++i)
    {
        printf("%f\n", randxf(&state));
    }

    return 0;
}
```
