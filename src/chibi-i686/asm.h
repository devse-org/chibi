#pragma once

#include <chibi-base/std.h>

void chibi_outb(uint16_t port, uint8_t data) {
    asm volatile("outb %0, %1"
                 :
                 : "a"(data), "Nd"(port));
}

uint8_t chibi_inb(uint16_t port) {
    uint8_t data;
    asm volatile("inb %1, %0"
                 : "=a"(data)
                 : "Nd"(port));
    return data;
}