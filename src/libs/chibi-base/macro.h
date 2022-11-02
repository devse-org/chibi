#pragma once

#define packed [[gnu::packed]]
#define unused [[gnu::unused]]
#define noreturn [[gnu::noreturn]]
#define maybe_unused [[maybe_unused]]
#define alias(name) __attribute__((alias(name)))
#define chibi_noreturn() __builtin_unreachable()