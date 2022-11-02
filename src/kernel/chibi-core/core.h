#pragma once

#include <chibi-base/macro.h>
#include <handover/handover.h>

noreturn void chibi_main(uint64_t magic, HandoverPayload const *payload);

noreturn void chibi_panic(char const *fmt, ...);