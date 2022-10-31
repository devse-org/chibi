#include <chibi-base/io.h>
#include <handover/handover.h>
#include <stdint.h>

#include "arch.h"

void chibi_main([[maybe_unused]] uint64_t magic, [[maybe_unused]] HandoverPayload const *payload) {
    chibi_print("Hello, Chibi !");
    for (;;)
        ;
}