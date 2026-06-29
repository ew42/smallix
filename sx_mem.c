#include "sx_mem.h"
#include "sx_file_descriptors.h"
#include "sx_types.h"

static _Alignas(8) char heap[4096 * 1024];
static sx_size_t offset = 0;

void *sx_malloc(sx_size_t size) {
	size = (size + 7) & ~7;
	if (offset + size > sizeof(heap)) return NULL;
	void *p = heap + offset;
	offset += size;
	return p;
}

void sx_free(void *p) {
	(void)p;
}

// void *sx_realloc(void *p, sx_size_t size) {
// 	p = sx_malloc(size);
// }
//
