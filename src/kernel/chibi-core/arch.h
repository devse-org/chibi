#pragma once

#include <chibi-base/macro.h>
#include <handover/handover.h>

void chibi_disable_interrupts(void);

void chibi_enable_interrupts(void);

void chibi_halt(void);

void chibi_arch_init(void);

noreturn void chibi_stop(void);