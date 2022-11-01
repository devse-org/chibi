#define HANDOVER_INCLUDE_UTILITES

#include <chibi-base/io.h>
#include <chibi-core/arch.h>
#include <handover/handover.h>
#include <stddef.h>

#include "limine.h"

static uint8_t handover_buffer[16 * 1024] = {};
static HandoverPayload *handover = (HandoverPayload *)handover_buffer;

volatile struct limine_framebuffer_request framebuffer = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
};

volatile struct limine_memmap_request mmap = {
    .id = LIMINE_MEMMAP_REQUEST,
};

static void parse_framebuffer(void)
{
    if (framebuffer.response == NULL)
    {
        chibi_print("Framebuffer request failed\n");
        chibi_print("Halting\n");
        chibi_stop();
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
}

static void parse_mmap(void)
{
    if (mmap.response == NULL)
    {
        chibi_puts("Failed to get memory map\n");
        chibi_puts("Halting\n");
        chibi_stop();
    }

    for (size_t i = 0; i < mmap.response->entry_count; i++)
    {
        struct limine_memmap_entry *entry = mmap.response->entries[i];
        int tag_type = 0;

        switch (entry->type)
        {
        case LIMINE_MEMMAP_USABLE:
            tag_type = HANDOVER_FREE;
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

        if (tag_type)
        {
            HandoverRecord record = {
                .tag = tag_type,
                .flags = 0,
                .start = entry->base,
                .size = entry->length,
            };

            handover_append(handover, record);
        }
    }
}

void _kstart(void)
{
    chibi_print("Booting with Limine...\n");

    handover->size = 16 * 1024;

    parse_mmap();
    parse_framebuffer();

    chibi_main(HANDOVER_COOLBOOT, handover);
}
