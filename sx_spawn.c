#include "sx_process.h"
#include "sx_stdio.h"
#include <errno.h>
#include <string.h>







int main(int argc, char *argv[]) {
	sx_pid_t pid;
	if ((pid = sx_fork()) == 0) {
		char *args[argc];
		for (int i = 1; i < argc; i++) {
			args[i-1] = argv[i];
		}
		args[argc-1] = 0;
		sx_execve(args[0], args, 0);

		sx_printf("%s", strerror(errno));
	}
	else {
		int status;
		sx_waitpid(pid, &status, 0);
		int exit = (status >> 8) && 0xFF;
		sx_printf("Exit status: %d\n", exit);
	}
}
