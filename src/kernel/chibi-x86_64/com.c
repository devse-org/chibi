#include <chibi-base/io.h>
#include <stdbool.h>

#include "asm.h"
#include "com.h"

static bool com_initialized = false;

void chibi_putc(char c)
{
    if (!com_initialized)
    {
        const uint8_t div_low = COM_BAUD_DIV & 0xff;
        const uint8_t div_high = COM_BAUD_DIV >> 8;

        asm_out8(SERIAL_PORT + COM_REGS_INTERRUPT, 0x00);
        asm_out8(SERIAL_PORT + COM_REGS_LINE_CONTROL, 0x80);
        asm_out8(SERIAL_PORT + COM_REGS_BAUD_RATE_LOW, div_low);
        asm_out8(SERIAL_PORT + COM_REGS_BAUD_RATE_HIGH, div_high);
        asm_out8(SERIAL_PORT + COM_REGS_LINE_CONTROL, 0x03);
        asm_out8(SERIAL_PORT + COM_REGS_FIFO_CONTROLLER, 0xc7);
        asm_out8(SERIAL_PORT + COM_REGS_MODEM_CONTROL, 0x0b);

        com_initialized = true;
    }

    while ((asm_in8(SERIAL_PORT + COM_REGS_LINE_STATUS) & 0x20) == 0)
        ;

    asm_out8(SERIAL_PORT + COM_REGS_DATA, c);
}