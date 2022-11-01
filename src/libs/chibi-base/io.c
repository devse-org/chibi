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

void chibi_itoa(int64_t value, char *str, uint64_t base, size_t buf_size) {
    size_t len = 0;

    if (value) {
        do {
            const char digit = (char)(value % base);
            str[len++] = digit < 10 ? '0' + digit : 'a' + digit - 10;
            value /= base;
        } while (value && (len < buf_size));

        chibi_cstrrev(str);
    } else {
        *str = '0';
    }
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
                char buffer[32] = {0};
                chibi_itoa(number, buffer, 10, 32);
                chibi_puts(buffer);

            } else if (*fmt == 'x') {
                int number = va_arg(va, int);
                char buffer[32] = {0};
                chibi_itoa(number, buffer, 16, 32);
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
