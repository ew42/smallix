#include "sx_process.h"
#include "sx_stdio.h"
#include "sx_file_descriptors.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		sx_printf("Usage: %s <command> [args...]\n", argv[0]);
		return 1;
	}

	sx_pid_t pid = sx_clone(SX_CLONE_NEWUTS | SX_CLONE_NEWNS | SX_CLONE_NEWPID | SX_SIGCHLD, 0, 0, 0, 0);

	if (pid < 0) {
		sx_printf("Clone failed\n");
		return 1;
	}

	if (pid == 0) {
		sx_sethostname("sx-container", 12);
		sx_execve(argv[1], &argv[1], 0);
		sx_printf("execve %s failed\n", argv[1]);
		sx_exit(1);
	}
	else {
		int status = 0;
		sx_waitpid(pid, &status, 0);
		return (status >> 8) & 0xFF;
	}


}
