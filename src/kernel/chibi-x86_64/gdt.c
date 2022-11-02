#include <chibi-base/io.h>

#include <chibi-x86_64/gdt.h>

static Gdt gdt = {};

static GdtPointer gdt_ptr = {
    .limit = sizeof(Gdt) - 1,
    .base = (uintptr_t)&gdt,
};

static GdtEntry gdt_create_entry(uint32_t base, uint32_t limit, uint8_t granularity, uint8_t flags)
{
    return (GdtEntry){
        .limit0_15 = (uint16_t)((limit)&0xffff),
        .base0_15 = (uint16_t)((base)&0xffff),
        .base16_23 = (uint8_t)(((base) >> 16) & 0xff),
        .flags = (flags),
        .limit16_19 = ((limit) >> 16) & 0x0f,
        .granularity = (granularity),
        .base24_31 = (uint8_t)(((base) >> 24) & 0xff),
    };
}

void gdt_init(void)
{
    gdt.entries[GDT_NULL] = gdt_create_entry(0, 0, 0, 0);

    gdt.entries[GDT_KERNEL_CODE] = gdt_create_entry(0, 0, GDT_PRESENT | GDT_SEGMENT | GDT_READWRITE | GDT_EXECUTABLE, GDT_LONG_MODE_GRANULARITY);
    gdt.entries[GDT_KERNEL_DATA] = gdt_create_entry(0, 0, GDT_PRESENT | GDT_SEGMENT | GDT_READWRITE, 0);

    gdt.entries[GDT_USER_DATA] = gdt_create_entry(0, 0, GDT_PRESENT | GDT_SEGMENT | GDT_READWRITE | GDT_USER, 0);
    gdt.entries[GDT_USER_CODE] = gdt_create_entry(0, 0, GDT_PRESENT | GDT_SEGMENT | GDT_READWRITE | GDT_EXECUTABLE | GDT_USER, GDT_LONG_MODE_GRANULARITY);

    gdt_push((uintptr_t)&gdt_ptr);

    chibi_success();
}