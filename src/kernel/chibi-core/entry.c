#include <chibi-base/io.h>
#include <handover/handover.h>
#include <stdint.h>

#include "arch.h"

void chibi_main(uint64_t magic, [[maybe_unused]] HandoverPayload const *payload)
{
    if (magic != 0)
    {
        chibi_puts("Invalid handover magic\n");
        chibi_puts("Halting\n");
        chibi_stop();
    }

    chibi_stop();
}