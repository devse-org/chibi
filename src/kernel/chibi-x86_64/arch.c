#include <chibi-core/arch.h>

#include "asm.h"

void chibi_disable_interrupts(void)
{
    asm_cli();
}

void chibi_enable_interrupts(void)
{
    asm_sti();
}

void chibi_halt(void)
{
    asm_hlt();
}

void chibi_stop(void)
{
    while (1)
    {
        asm_cli();
        asm_hlt();
    }
}
