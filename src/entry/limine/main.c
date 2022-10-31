#define HANDOVER_INCLUDE_UTILITES

#include <chibi-base/io.h>
#include <chibi-core/arch.h>
#include <handover/handover.h>
#include <stddef.h>

#include "limine.h"

HandoverPayload *handover = NULL;
HandoverRecord free_record = {0};

volatile struct limine_framebuffer_request framebuffer = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
};

volatile struct limine_memmap_request mmap = {
    .id = LIMINE_MEMMAP_REQUEST,
};

static void parse_framebuffer(HandoverPayload *handover) {
    if (framebuffer.response == NULL) {
        chibi_print("Framebuffer request failed\n");
        chibi_print("Halting\n");

        for (;;)
            ;
    }

    HandoverRecord record = {
        .tag = HANDOVER_FB,
        .flags = 0,
        .start = (uintptr_t)framebuffer.response->framebuffers[0]->address,
        .fb = {
            .width = framebuffer.response->framebuffers[0]->width,
            .height = framebuffer.response->framebuffers[0]->height,
            .pitch = framebuffer.response->framebuffers[0]->pitch,
            .format = HANDOVER_RGBX8888,
        }};

    handover_append(handover, record);
    free_record.start += sizeof(HandoverRecord);
    free_record.size -= sizeof(HandoverRecord);
}

static void parse_mmap(HandoverPayload *handover) {
    if (mmap.response == NULL) {
        chibi_puts("Failed to get memory map\n");
        chibi_puts("Halting\n");

        for (;;)
            ;
    }

    for (size_t i = 0; i < mmap.response->entry_count; i++) {
        struct limine_memmap_entry *entry = mmap.response->entries[i];
        int tag_type = 0;

        switch (entry->type) {
        case LIMINE_MEMMAP_USABLE:
            if (free_record.size == 0) {
                free_record = (HandoverRecord){
                    .tag = HANDOVER_FREE,
                    .flags = 0,
                    .start = entry->base,
                    .size = entry->length,
                };

                handover = (HandoverPayload *)entry->base;
                free_record.size -= sizeof(HandoverPayload);
                free_record.start += sizeof(HandoverPayload);
            } else {
                tag_type = HANDOVER_FREE;
            }
            break;

        case LIMINE_MEMMAP_ACPI_NVS:
        case LIMINE_MEMMAP_RESERVED:
        case LIMINE_MEMMAP_BAD_MEMORY:
            tag_type = HANDOVER_RESERVED;
            break;

        case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
        case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
            tag_type = HANDOVER_LOADER;
            break;

        case LIMINE_MEMMAP_KERNEL_AND_MODULES:
            tag_type = HANDOVER_KERNEL;
            break;

        case LIMINE_MEMMAP_FRAMEBUFFER:
            break;
        }

        if (tag_type) {
            HandoverRecord record = {
                .tag = tag_type,
                .flags = 0,
                .start = entry->base,
                .size = entry->length,
            };

            handover_append(handover, record);

            free_record.start += sizeof(HandoverRecord);
            free_record.size -= sizeof(HandoverRecord);
        }
    }
}

void _kstart(void) {
    chibi_print("Booting with Limine...\n");

    parse_mmap(handover);
    parse_framebuffer(handover);

    free_record.start += sizeof(HandoverPayload);
    free_record.size -= sizeof(HandoverPayload);

    handover_append(handover, free_record);

    chibi_main(HANDOVER_COOLBOOT, handover);
}
