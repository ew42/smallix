#ifndef SX_MEMORY_MANAGEMENT
#define SX_MEMORY_MANAGEMENT

void *sx_malloc(sx_size_t size);
void sx_free(void *p);
// void *sx_realloc(void *p, sx_size_t size); without headers, there's no way to implement
// void *sx_calloc(sx_size_t

#endif
