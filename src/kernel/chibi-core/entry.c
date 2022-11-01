#include <chibi-base/io.h>
#include <chibi-core/core.h>
#include <handover/handover.h>

#include "arch.h"

void chibi_main(uint64_t magic, [[maybe_unused]] HandoverPayload const *payload)
{
    if (magic != HANDOVER_MAGIC)
    {
        chibi_panic("invalid handover magic");
    }

    chibi_println("Hello, chibi!");
    chibi_stop();
}
