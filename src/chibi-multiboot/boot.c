#include <chibi-base/io.h>
#include <chibi-core/arch.h>

#include "multiboot.h"

void kmain(multiboot_info_t *, unsigned int) {
    chibi_puts("Hello, world!\r");
}