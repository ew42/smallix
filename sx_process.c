#include "sx_process.h"
#include "sx_syscall.h"
#include "sx_types.h"
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

sx_pid_t sx_clone(unsigned long flags, void *stack, int *parent_tid, int *child_tid, unsigned long tls) {
	sx_word ret = sx_syscall5(
		(sx_word)SYS_clone,
		(sx_word)flags,
		(sx_word)stack,
		(sx_word)parent_tid,
		(sx_word)child_tid,
		(sx_word)tls
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (sx_pid_t)ret;
}

int sx_sethostname(const char *name, sx_size_t len) {
	sx_word ret = sx_syscall2(
		(sx_word)SYS_sethostname,
		(sx_word)name,
		(sx_word)len
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (int)ret;

}

int sx_pipe(int pipefd[2]) {
	sx_word ret = sx_syscall1(
		(sx_word)SYS_pipe,
		(sx_word)pipefd
	);

	if ((long)ret < 0) {
		errno = (int)-ret;
		ret = -1;
	}

	return (int)ret;
}
