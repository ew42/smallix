#ifndef MEMMAP
#define MEMMAP

#include "sx_types.h"

// mmap prot arg
#define SX_PROT_NONE 0x00
#define SX_PROT_READ 0x01
#define SX_PROT_WRITE 0x02
#define SX_PROT_EXEC 0x04

// mmap flags arg
#define SX_MAP_PRIVATE 0x02
#define SX_MAP_ANONYMOUS 0x20

// mmap returns on failure
#define SX_MMAP_FAILED ((void*)-1)

void *sx_mmap(void *addr, sx_size_t len, int prot, int flags, int fd, sx_off_t offset);
int sx_munmap(void *addr, sx_size_t length);






#endif
