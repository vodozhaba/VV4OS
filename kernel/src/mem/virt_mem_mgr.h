// File:       mem/virt_mem_mgr.h                                      
// Author:     vodozhaba                                                      
// Created on: Oct 12, 2016                                                   
// Purpose:    Aliases virtual memory managers for different architectures.

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "phys_mem_mgr.h"

void X86VirtMemMgrInit();
void* X86AllocateContiguousVirtualFrames(uint32_t frames, bool kernel);
void X86FreeContiguousVirtualFrames(void* base, uint32_t frames);
void* X86CreateAddressSpace(void* k_base, size_t frames);
void X86SwitchAddressSpace(void* address_space);
void X86DeleteAddressSpace(void* address_space);
void* X86CreateStack(void* address_space, void* top, size_t size);

#if !defined(__X86__)
#error "Cannot determine target architecture"
#endif

static inline void VirtMemMgrInit() {
#if defined(__X86__)
    X86VirtMemMgrInit();
#endif
}

static inline void* AllocateContiguousVirtualFrames(size_t frames, bool kernel) {
#if defined(__X86__)
    return X86AllocateContiguousVirtualFrames(frames, kernel);
#endif
}

static inline void FreeContiguousVirtualFrames(void* base, size_t frames) {
#if defined(__X86__)
    return X86FreeContiguousVirtualFrames(base, frames);
#endif
}

static inline void* CreateAddressSpace(void* k_base, size_t frames) {
#if defined(__X86__)
    return X86CreateAddressSpace(k_base, frames);
#endif
}