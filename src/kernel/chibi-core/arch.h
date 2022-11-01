#pragma once

#include <handover/handover.h>

void chibi_main(uint64_t magic, HandoverPayload const *payload);

void cli(void);
void sti(void);
void hlt(void);

static inline void chibi_stop(void)
{
    while (true)
    {
        cli();
        hlt();
    }
}