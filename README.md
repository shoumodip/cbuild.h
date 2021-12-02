# Cbuild
Self building C program.

## Explanation
Recompiles the C program automatically if the last modification time of the
source code is later than the binary.

**NOTE: Only works on C projects with one source file**

## Quick Start
```console
$ cc -o cbuild cbuild.c
```

## Usage
Copy the `cbuild.h` file into your project and use it.

```c
#include "cbuild.h"

int main(int argc, char **argv)
{
    rebuild(argc, argv); // Rebuild the source code if necessary

    // ...

    return 0;
}
```

## Use Cases
None.

```console
$ make
```
