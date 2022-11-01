#pragma once

#include <chibi-base/std.h>

void chibi_putc(char c);

void chibi_puts(char const *s);

void chibi_printva(const char *fmt, va_list va);

void chibi_print(char const *fmt, ...);

void chibi_println(const char *fmt, ...);
