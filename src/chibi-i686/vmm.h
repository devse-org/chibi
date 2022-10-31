#pragma once

#include <chibi-base/std.h>

typedef uint32_t pml_t;

#define PML_PRESENT (1 << 0)
#define PML_WRITE (1 << 1)
#define PML_USER (1 << 2)
#define PML_WRITE_THROUGH (1 << 3)
#define PML_CACHE_DISABLE (1 << 4)
#define PML_ACCESSED (1 << 5)
#define PML_DIRTY (1 << 6)
#define PML_SIZE (1 << 7)
#define PML_GLOBAL (1 << 8)
#define PML_FRAME 0xFFFFF000
