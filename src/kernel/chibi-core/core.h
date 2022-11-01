#pragma once

#include <handover/handover.h>

void chibi_main(uint64_t magic, HandoverPayload const *payload);

void chibi_panic(char const *fmt, ...);