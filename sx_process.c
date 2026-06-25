#include "sx_process.h"
#include "sx_syscall.h"
#include <errno.h>

sx_pid_t sx_fork(void) {
	sx_pid_t ret = (sx_pid_t)sx_syscall0(
		(sx_word)SYS_fork
	);
	return ret;
}

int sx_execve(const char *pathname, char *const argv[], char *const envp[]) {
	sx_word ret = sx_syscall3(
		(sx_word)SYS_execve,
		(sx_word)pathname,
		(sx_word)argv,
		(sx_word)envp
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (int)ret;
	return ret;
}
