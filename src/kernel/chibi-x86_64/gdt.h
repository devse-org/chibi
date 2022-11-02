#pragma once

#include <chibi-base/macro.h>
#include <stdint.h>

#define GDT_SEGMENT (0b00010000)
#define GDT_PRESENT (0b10000000)
#define GDT_USER (0b01100000)
#define GDT_EXECUTABLE (0b00001000)
#define GDT_READWRITE (0b00000010)
#define GDT_LONG_MODE_GRANULARITY (0b0010)
#define GDT_FLAGS (0b1100)

typedef enum
{
    GDT_NULL,
    GDT_KERNEL_CODE,
    GDT_KERNEL_DATA,
    GDT_USER_DATA,
    GDT_USER_CODE,

    GDT_ENTRY_COUNT
} GdtIndex;

typedef struct packed
{
    uint16_t limit0_15;
    uint16_t base0_15;
    uint8_t base16_23;
    uint8_t flags;
    uint8_t limit16_19 : 4;
    uint8_t granularity : 4;
    uint8_t base24_31;
} GdtEntry;

typedef struct packed
{
    uint16_t limit;
    uint64_t base;
} GdtPointer;

typedef struct packed
{
    GdtEntry entries[GDT_ENTRY_COUNT];
} Gdt;

void gdt_init(void);
void gdt_push(uintptr_t pointer);