#include "sx_mem.h"
#include "sx_file_descriptors.h"
#include "sx_types.h"
#include "sx_stdio.h"

#define HEADER 8UL
#define FOOTER 8UL
#define REGION_OVERHEAD 40UL
#define MIN_BLOCK 32UL
#define PAGE_SIZE 4096UL

#define MIN_REGION (64UL * 1024UL)

enum {
	FREE = 1,
	MMAPPED = 2
};

typedef struct block {
	unsigned long size;
	struct block *next;
	struct block *prev;
} block;

typedef struct region {
	struct region *next;
	unsigned long size;
} region;

static block *free_list = {0};
static region *regions = {0};

static inline void *payload(block *blk) {
	return (char *)blk + HEADER;
}

static inline block *header_of(void *payload) {
	return (block *)((char *)payload - HEADER);
}

static inline unsigned long blk_size(block *blk) {
	return blk->size & ~0xFUL;
}

static inline int blk_free(block *blk) {
	return blk->size & FREE;
}

static inline int blk_mmapped(block *blk) {
	return blk->size & MMAPPED;
}

static inline unsigned long *blk_footer(block *blk) {
	return (unsigned long *) ((char *)blk + blk_size(blk) - FOOTER);
}

static inline block *blk_next(block *blk) {
	return (block *) ((char *)blk + blk_size(blk));
}

static inline block *blk_prev(block *blk) {
	unsigned long *prev_footer = (unsigned long *)((char *)blk - FOOTER);
	return (block *) ((char *)blk - (*prev_footer & ~0xFUL));
}

static inline unsigned long round_up_to_page(unsigned long n) {
	return (n + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
}

static void freelist_insert(block *blk) {
	blk->prev = (block*)0;
	blk->next = free_list;
	if (free_list) free_list->prev = blk;
	free_list = blk;
}

static void freelist_remove(block *blk) {
	if (blk->prev) blk->prev->next = blk->next;
	else free_list = blk->next;
	if (blk->next) blk->next->prev = blk->prev;
}

static unsigned long align16(unsigned long n) {
	return (n + 15UL) & ~15UL;
}

void heap_dump(void) {
	/*
	 * heap_dump walks the implicit list and prints each block's address, size, and free bit
	*/
	long free_count = 0;
	sx_printf("Implicit list region walk:\n");
	for (region *r = regions; r != (region*)0; r = r->next) {
		char *r_end = (char*)r + r->size;
		sx_printf("Region %p, size = %lu\n, [%p .. %p)\n", (void*)r, r->size, (void*)r, (void*)r_end);

		block *prologue = (block *)((char*)r + 24);
		for (block *b = prologue; blk_size(b) != 0; b = blk_next(b)) {
			unsigned long ftr = *blk_footer(b);
			sx_printf("  %p size %lu(%lu) free %d(%d)%s%s\n",
					(void*)b,
					blk_size(b), ftr & ~0xFUL,
					blk_free(b), (int)(ftr & FREE),
					(b = prologue) ? "  [prologue]" : "",
					(blk_size(b) != (ftr & ~0xFUL)) || (blk_free(b) != (int)(ftr & FREE)) ? "<-- C2 MISMATCH" : "");
					// add C5 check here
			if (blk_free(b)) free_count++;
			if (blk_size(b) == 0) sx_printf("  %p  [epilogue]%s\n",
					(void*)b,
					((char*)b + HEADER == r_end) ? "": "  <-- C1 NOT AT REGION END");
		}
	}

	sx_printf("Free list walk:\n");
	for (block *b = free_list; b != (block*)0; b = b->next) {
		
		if (!blk_free(b)) sx_printf("Non-free block on the explicit free list!\n");
		else free_count--;

		unsigned long ftr = *blk_footer(b);
		sx_printf("  %p size %lu(%lu) free %d(%d)%s\n",
				(void*)b,
				blk_size(b), ftr & ~0xFUL,
				blk_free(b), (int)(ftr & FREE),
				(blk_size(b) != (ftr & ~0xFUL)) || (blk_free(b) != (int)(ftr & FREE)) ? "<--MISMATCH" : "");
	}
	
	if (free_count != 0) sx_printf("C4 FAIL, # of free blocks in implicit vs. free-list differ by: %ld\n", free_count);
}

static region *grow(unsigned long need) {
	// region (16 bytes)
	// padding (8 bytes) -- all block payloads need to start on 16 byte aligned addresses
	// prologue (16 bytes) -- header/footer
	// block header (8 bytes)
	// block payload (cum. 48 byte offset)
	// ... 8 byte epilogue "header" at end

	unsigned long len = round_up_to_page(REGION_OVERHEAD + need + HEADER); // epilogue is just a header
	if (len < MIN_REGION) len = MIN_REGION;
	void *base = sx_mmap(0, len, SX_PROT_READ | SX_PROT_WRITE, SX_MAP_PRIVATE | SX_MAP_ANONYMOUS, -1, 0);
	if (base == SX_MMAP_FAILED) return (region*)0;

	region *r = (region*)base;
	r->size = len;
	r->next = regions;
	regions = r;

	block *pro = (block*)((char*)r + 24);
	pro->size = 16;
	*blk_footer(pro) = 16;

	block *first = blk_next(pro);
	unsigned long usable = len - REGION_OVERHEAD - HEADER;
	usable &= ~0xFUL; // force 16-byte align (should already be)
	first->size = usable | FREE;
	*blk_footer(first) = first->size;

	block *epi = (block*)((char*)r + len - HEADER);
	epi->size = 0;

	freelist_insert(first);

	return r;
}

static void split(block *blk, unsigned long need) {
	unsigned long total = blk_size(blk);

	if (total - need < MIN_BLOCK) return; // if the remainder is too small, don't split

	blk->size = need;
	*blk_footer(blk) = blk->size;

	block *rem = blk_next(blk);
	rem->size = (total - need) | FREE;
	*blk_footer(rem) = rem->size;
	freelist_insert(rem);
}

void *sx_malloc(sx_size_t size) {
	if (size == 0) {
		return (void*)0; // return null
	}
	unsigned long need = align16(size) + HEADER + FOOTER;
	if (need < MIN_BLOCK) need = MIN_BLOCK;

	block *curr = free_list;
	while (curr) {
		if (need <= blk_size(curr)) {
			freelist_remove(curr);
			curr->size &= ~1UL; // clear free bit
			split(curr, need);
			*blk_footer(curr) = curr->size;
			return payload(curr);
		}
		else {
			curr = curr->next;
		}
	}

	if(!grow(need)) return (void*)0;
	void *ret = sx_malloc(size);

	return ret;
}

void sx_free(void *p) {
	if (!p) return;
	
	block *blk = header_of(p);
	blk->size |= 1UL;
	*blk_footer(blk) = blk->size;
	freelist_insert(blk);
}
