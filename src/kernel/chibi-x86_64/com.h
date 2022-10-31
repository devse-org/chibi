#pragma once

#include <chibi-base/io.h>

#define SERIAL_PORT 0x3f8

#define COM_BAUD_RATE (9600)
#define COM_BAUD_DIV (115200 / COM_BAUD_RATE)

#define COM_REGS_DATA (0)
#define COM_REGS_BAUD_RATE_LOW (0)
#define COM_REGS_BAUD_RATE_HIGH (1)
#define COM_REGS_INTERRUPT (1)
#define COM_REGS_FIFO_CONTROLLER (2)
#define COM_REGS_LINE_CONTROL (3)
#define COM_REGS_MODEM_CONTROL (4)
#define COM_REGS_LINE_STATUS (5)