#pragma once

#include <chibi-base/std.h>

inline uint8_t asm_in8(uint16_t port)
{
    uint8_t data;
    asm volatile("inb %1, %0"
                 : "=a"(data)
                 : "d"(port));
    return data;
}

inline void asm_out8(uint16_t port, uint8_t data)
{
    asm volatile("outb %0, %1"
                 :
                 : "a"(data), "d"(port));
}

inline void asm_hlt(void)
{
    asm volatile("hlt");
}

inline void asm_cli(void)
{
    asm volatile("cli");
}

inline void asm_sti(void)
{
    asm volatile("sti");
}
