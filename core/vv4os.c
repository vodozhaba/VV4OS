/******************************************************************************
 * File:       /vv4os/core/vv4os.c                                            *
 * Author:     velikiyv4                                                      *
 * Created on: Aug 20, 2016                                                   *
 * Purpose:    The main file of the project, connects all the modules.        *
 ******************************************************************************/

#include <stdbool.h>
#include <stddef.h>
#include "boot/multiboot/multiboot.h"
#include "dt/desc_tables.h"
#include "io/disk/disk.h"
#include "io/pci.h"
#include "io/vga_terminal.h"
#include "mem/phys_mem_mgr.h"
#include "mem/virt_mem_mgr.h"
#include "stdlib/stdio.h"
#include "stdlib/stdlib.h"
#include "stdlib/string.h"

#define MAX_CONF_SIZE 4096
#define CONF_SIGNATURE "notjunk"

size_t available_ram;

char config[MAX_CONF_SIZE];

bool ParseConfig() {
	config[strlen(CONF_SIGNATURE)] = '\0';
	return strcmp(config, CONF_SIGNATURE) == 0;
}

void main(MultibootInformation* mi) {
    available_ram = (mi->mem_upper + 1024) << 10;
    VgaTerminalInit();
    printf("Initialized VGA terminal\n");
    if(mi->mods_count != 1) {
    	VgaTerminalSwitchColorScheme(err_color_scheme);
    	printf("Something's wrong with the boot modules. Aborting");
    	exit(1);
    }
    MultibootModuleStructure conf = ((MultibootModuleStructure*) mi->mods_addr)[0];
    size_t conf_size = conf.mod_end - conf.mod_start;
    memcpy(config, (void*) conf.mod_start, conf_size > MAX_CONF_SIZE ? MAX_CONF_SIZE : conf_size);
    DescTablesInit();
    printf("Initialized processor descriptor tables\n");
    printf("Detected %dMiB of RAM\n", available_ram / 1048576);
    PhysMemMgrInit(available_ram);
    printf("Initialized physical memory manager\n");
    VirtMemMgrInit();
    printf("Initialized virtual memory manager\n");
    PciInit();
    printf("Initialized PCI driver\n");
    if(ParseConfig())
    	printf("Parsed the boot config successfully\n");
    else {
    	VgaTerminalSwitchColorScheme(err_color_scheme);
    	printf("Cannot parse the boot config. Is there a valid /sys/vv4os/boot.cfg?\n");
    	exit(1);
    }
    DiskSubsystemInit();
    while(true);
}
