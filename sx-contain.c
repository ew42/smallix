#include "sx_filesystem.h"
#include "sx_process.h"
#include "sx_stdio.h"
#include "sx_types.h"

int main(int argc, char *argv[]) {

	if (argc < 2) {
		sx_printf("Usage: %s <filesystem path> [command]\n", argv[0]);
		return 1;
	}

	sx_pid_t pid = sx_clone(SX_CLONE_NEWUTS | SX_CLONE_NEWNS | SX_CLONE_NEWPID | SX_SIGCHLD, 0, 0, 0, 0);
	if (pid < 0) {
		sx_printf("Clone failed\n");
		return 1;
	}

	if (pid == 0) {
		sx_mount(0, "/", 0, SX_MS_REC | SX_MS_PRIVATE, 0);
		sx_mount(argv[1], argv[1], 0, SX_MS_BIND, 0);
		sx_chdir(argv[1]);
		sx_pivot_root(".", "."); // would this put it at /old-root?
		sx_chdir("/");
		sx_umount2(".", SX_MNT_DETACH);
		sx_mount("proc", "/proc", "proc", 0, 0);

		sx_sethostname("sx-container", 12);
		char *args[] = {"/bin/sh", 0};
		sx_execve("/bin/sh", args, 0);
		
	}
	else {
		sx_waitpid(pid, 0, 0);
	}
}
