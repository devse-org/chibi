#include <chibi-core/arch.h>

void hlt(void)
{
    asm volatile("hlt");
}

void cli(void)
{
    asm volatile("cli");
}

void sti(void)
{
    asm volatile("sti");
}