#define HANDOVER_INCLUDE_UTILITES

#include <handover/handover.h>
#include <stddef.h>

#include "limine.h"

void limine_entry(void);

struct limine_entry_point_request entry_point = {
    .id = LIMINE_ENTRY_POINT_REQUEST,
    .entry = limine_entry,
};

struct limine_memmap_request mmap = {
    .id = LIMINE_MEMMAP_REQUEST,
};

void limine_entry(void) {
}