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
}

sx_pid_t sx_waitpid(sx_pid_t pid, int *statusp, int options) {
	sx_pid_t ret = sx_syscall4(
		(sx_word)SYS_wait4,
		(sx_word)pid,
		(sx_word)statusp,
		(sx_word)options,
		(sx_word)0
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (sx_pid_t)ret;
}

int sx_dup2(int oldfd, int newfd) {
	sx_word ret = sx_syscall2(
		(sx_word)SYS_dup2,
		(sx_word)oldfd,
		(sx_word)newfd
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (sx_pid_t)ret;

}
