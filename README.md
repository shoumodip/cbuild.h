# Cbuild
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

### `CC`
The C compiler used. It defaults to `cc`.

```c
#define CC "clang" // This must be placed BEFORE the include
#include "cbuild.h"
```

### `CFLAGS`
The compilation flags used. It defaults to `-Wall -Werror -std=c11 -pedantic`.

```c
#define CFLAGS "-Wall", "-Wextra" // Don't be pedantic, the C standard is for boomers!
#include "cbuild.h"
```

## Use Cases
None.

```console
$ make
```
