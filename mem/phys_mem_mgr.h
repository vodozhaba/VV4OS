/******************************************************************************
 * File:       /vv4os/mem/phys_mem_mgr.c                                      *
 * Author:     velikiyv4                                                      *
 * Created on: Sep 30, 2016                                                   *
 * Purpose:    Aliases physical memory managers for different architectures.  *
 ******************************************************************************/

#include <stddef.h>

void X86PhysMemMgrInit(size_t ram_size);
void* X86PhysAllocateFrame();
void X86PhysFreeFrame(void* ptr);


#if !defined(__X86__)
#error "Cannot determine target architecture"
#endif

static inline void PhysMemMgrInit(size_t ram_size) {
#if defined(__X86__)
    X86PhysMemMgrInit(ram_size);
#endif
}

static inline void* PhysAllocateFrame() {
#if defined(__X86__)
    return X86PhysAllocateFrame();
#endif
}

static inline void PhysFreeFrame(void* ptr) {
#if defined(__X86__)
    X86PhysFreeFrame(ptr);
#endif
}