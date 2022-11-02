#include <chibi-base/io.h>
#include <chibi-base/macro.h>
#include <chibi-core/core.h>
#include <handover/handover.h>

#include "arch.h"

noreturn void chibi_main(uint64_t magic, maybe_unused HandoverPayload const *payload)
{
    if (magic != HANDOVER_MAGIC)
    {
        chibi_panic("invalid handover magic");
    }

    chibi_arch_init();
    chibi_stop();
}
