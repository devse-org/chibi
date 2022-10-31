#pragma once

#include <chibi-base/std.h>

struct Tss {
    uint32_t prev_tss;
    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint16_t trap;
    uint16_t iomap_base;
};

struct gdt_entry {
    uint16_t limit0_15;
    uint16_t base0_15;
    uint8_t base16_23;
    uint8_t access;
    uint8_t limit16_19 : 4;
    uint8_t flags : 4;
    uint8_t base24_31;
};

struct gdt_desc {
    uint16_t size;
    uint32_t offset;
};

struct idt_entry {
    uint16_t offset0_15; // offset bits 0..15
    uint16_t selector;   // a code segment selector in GDT or LDT
    uint8_t zero;
    uint8_t type_attr;    // type and attributes
    uint16_t offset16_31; // offset bits 16..31
};

struct idt_desc {
    uint16_t size;
    uint32_t offset;
};