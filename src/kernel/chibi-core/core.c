#include <chibi-base/io.h>

#include "arch.h"

void chibi_panic(char const *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    chibi_puts("panic: ");
    chibi_printva(fmt, va);
    chibi_puts("\nhalting\n");
    va_end(va);
    chibi_stop();
}
