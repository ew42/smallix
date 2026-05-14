#include "sx_file_descriptors.h"
#include "sx_syscall.h"


// Explanations for stuff I didn't write
#include <stdarg.h> // enables handling of variadic function arguments, needed for mode bits
#include <errno.h> // gives the errno global var, where we set error status
#include <fcntl.h> // somewhat of a crutch, fnctl defines all of the macros for flags
#include <sys/stat.h> // for the mode_t type and struct stat
#include <stdio.h>

int sx_openat(int fd, const char *pathname, int flags, ...) {

	mode_t mode = 0;

	if (O_CREAT & flags) {
		va_list ap;
		va_start(ap, flags);
		mode = va_arg(ap, mode_t);
		va_end(ap);
	}

	sx_word ret = sx_syscall4(
			(sx_word)SYS_openat,
			(sx_word)fd,
			(sx_word)pathname,
			(sx_word)flags,
			(sx_word)mode
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (int)ret;
}

sx_ssize_t sx_read(int fd, void *buf, sx_size_t n) {
	sx_word ret = sx_syscall3(
			(sx_word)SYS_read,
			(sx_word)fd,
			(sx_word)buf,
			(sx_word)n
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (int)ret;
}

sx_ssize_t sx_write(int fd, const char *buf, sx_size_t n) {
	sx_word ret = sx_syscall3(
			(sx_word)SYS_write,
			(sx_word)fd,
			(sx_word)buf,
			(sx_word)n
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (int)ret;
}

sx_ssize_t sx_write_all(int fd, const char *buf, sx_size_t n) {
	sx_ssize_t n_written;
	sx_size_t n_left = n;

	while (n_left > 0) {
		if (n_written = sx_write(fd, buf, n_left) <= 0) {
			if (errno == EINTR) // if interrupted by a signal handler, restart
				n_written = 0;
			else
				return -1;
		}
		n_left -= n_written;
		buf += n_written;
	}
	return n;
}

int sx_close(int fd) {
	sx_word ret = sx_syscall1(
			(sx_word)SYS_close,
			(sx_word)fd
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (int)ret;
}

int sx_fstat(int fd, struct sx_stat *buf) {
	sx_word ret = sx_syscall2(
			(sx_word)SYS_fstat,
			(sx_word)fd,
			(sx_word)buf
	);

	if ((long)ret < 0) {
		errno = -(int)ret;
		ret = -1;
	}

	return (int)ret;
}

void exit(int status) {
	sx_syscall1(SYS_exit_group, status); // exit_group, man 2 exit_group: "terminates all threads in the calling process's thread group"
	__builtin_unreachable(); // tells compiler that this shouldn't be reachable
}


