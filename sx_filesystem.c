#include "sx_filesystem.h"
#include "sx_syscall.h"
#include "sx_types.h"
#include "sx_mem.h"
#include <errno.h>

int sx_mkdir(const char *path, sx_mode_t mode) {
	sx_word ret = sx_syscall2(
		(sx_word)SYS_mkdir,
		(sx_word)path,
		(sx_word)mode
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (int)ret;
}

int sx_chdir(const char *path) {
	sx_word ret = sx_syscall1(
		(sx_word)SYS_chdir,
		(sx_word)path
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (int)ret;
}

char *sx_getcwd(char *buf, sx_size_t size) {
	sx_word ret = sx_syscall2(
		(sx_word)SYS_getcwd,
		(sx_word)buf,
		(sx_word)size
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = 0;
	}

	return buf;
}

int sx_mount(const char *source, const char *target, const char *filesystemtype,
			 unsigned long mountflags, const void *data) {
	sx_word ret = sx_syscall5(
		(sx_word)SYS_mount,
		(sx_word)source,
		(sx_word)target,
		(sx_word)filesystemtype,
		(sx_word)mountflags,
		(sx_word)data
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (int)ret;
}

int sx_umount2(const char *target, int flags) {
	sx_word ret = sx_syscall2(
		(sx_word)SYS_umount2,
		(sx_word)target,
		(sx_word)flags
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (int)ret;
}

int sx_pivot_root(const char *new_root, const char *put_old) {
	sx_word ret = sx_syscall2(
		(sx_word)SYS_pivot_root,
		(sx_word)new_root,
		(sx_word)put_old
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (int)ret;
}
