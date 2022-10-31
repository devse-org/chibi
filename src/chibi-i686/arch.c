#include <chibi-base/io.h>
#include <chibi-core/arch.h>

#include "asm.h"

void chibi_putc(char c) {
    chibi_outb(0xe9, c);
}
