#include "sx_memmap.h"
#include "sx_syscall.h"
#include <errno.h>

void *sx_mmap(void *addr, sx_size_t len, int prot, int flags, int fd, sx_off_t offset) {

	sx_word ret = sx_syscall6(
		(sx_word)SYS_mmap,
		(sx_word)addr,
		(sx_word)len,
		(sx_word)prot,
		(sx_word)flags,
		(sx_word)fd,
		(sx_word)offset
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (void*)ret;

}

int sx_munmap(void *addr, sx_size_t length) {

	sx_word ret = sx_syscall2(
		(sx_word)SYS_munmap,
		(sx_word)addr,
		(sx_word)length
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (int)ret;
}
