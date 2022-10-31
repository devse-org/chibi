// simple printf implementation that supports %s %d %x %p

#include <chibi-base/io.h>
#include <chibi-base/std.h>

size_t chibi_cstrlen(const char *str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

void chibi_cstrrev(char s[]) {
    for (int i = 0, j = chibi_cstrlen(s) - 1; i < j; i++, j--) {
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void chibi_itoa(int n, char s[], int base) {
    int i, sign;

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % base + '0';
    } while ((n /= base) > 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    chibi_cstrrev(s);
}

void chibi_puts(const char *s) {
    while (*s) {
        chibi_putc(*s);
        s++;
    }
}

void chibi_print(const char *fmt, ...) {
    va_list va;
    va_start(va, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;

            if (*fmt == 's') {
                chibi_puts(va_arg(va, const char *));
            } else if (*fmt == 'd') {
                int number = va_arg(va, int);
                char buffer[32];
                chibi_itoa(number, buffer, 10);
                chibi_puts(buffer);

            } else if (*fmt == 'x') {
                int number = va_arg(va, int);
                char buffer[32];
                chibi_itoa(number, buffer, 16);
                chibi_puts(buffer);
            } else if (*fmt == '%') {
                chibi_putc('%');
            }
        } else {
            chibi_putc(*fmt);
        }

        fmt++;
    }

    va_end(va);
}
