#include "sx_filesystem.h"
#include "sx_process.h"
#include "sx_file_descriptors.h"
#include "sx_stdio.h"
#include "sx_types.h"
#include "sx_getopt.h"

int main(int argc, char *argv[]) {

	if (argc < 2) {
		sx_printf("Usage: %s <filesystem path> [command]\n", argv[0]);
		return 1;
	}

	char *memlim = "64M";
	unsigned long memlen = 3;
	int opt;
	while ((opt = sx_getopt(argc, argv, "m:")) != -1) {
		switch (opt) {
			case 'm':
				memlim = optarg;
				memlen = sx_strlen(memlim);
				break;
		}
	}

	int pipfd[2];
	sx_pipe(pipfd);
	sx_pid_t pid = sx_clone(SX_CLONE_NEWUTS | SX_CLONE_NEWNS | SX_CLONE_NEWPID | SX_SIGCHLD, 0, 0, 0, 0);
	if (pid < 0) {
		sx_printf("Clone failed\n");
		return 1;
	}


	if (pid == 0) {
		sx_close(pipfd[1]);
		char c;
		sx_read(pipfd[0], &c, 1);
		sx_close(pipfd[0]);
		sx_mount(0, "/", 0, SX_MS_REC | SX_MS_PRIVATE, 0);

		char *rootfs = argv[optind];
		char *cmd = argv[optind + 1];

		sx_mount(rootfs, rootfs, 0, SX_MS_BIND, 0);
		sx_chdir(rootfs);
		sx_pivot_root(".", "."); // write down the weird trick used here
		sx_chdir("/");
		sx_umount2(".", SX_MNT_DETACH);
		sx_mount("proc", "/proc", "proc", 0, 0);
		sx_sethostname("sx-container", 12);
		char *args[] = {cmd, 0};
		sx_execve(cmd, args, 0);
		sx_printf("exec failed\n");
		sx_exit(1);
		
	}
	else {
		sx_mkdir("/sys/fs/cgroup/sx-container", 0755);
		int memfd = sx_open("/sys/fs/cgroup/sx-container/memory.max", SX_O_WRONLY);
		sx_write_all(memfd, memlim, memlen);
		sx_close(memfd);
		int enrollfd = sx_open("/sys/fs/cgroup/sx-container/cgroup.procs", SX_O_WRONLY);
		if (enrollfd < 0) { sx_printf("cgroup enroll open failed\n"); sx_exit(1); }
		char buf[20];
		int len = sx_utoa((unsigned long)pid, buf);
		sx_write_all(enrollfd, buf, len);
		sx_close(enrollfd);
		int swapfd = sx_open("/sys/fs/cgroup/sx-container/memory.swap.max", SX_O_WRONLY);
		sx_write_all(swapfd, "0", 1);
		sx_close(swapfd);

		sx_close(pipfd[0]);
		sx_write_all(pipfd[1], "x", 1);
		sx_close(pipfd[1]);

		int status;
		sx_waitpid(pid, &status, 0);

		if (SX_WIFSIGNALED(status)) {
			int sig = SX_WTERMSIG(status);
			sx_printf("child killed by signal %d\n", sig);
		}
		else if (SX_WIFEXITED(status)) {
			sx_printf("child exited with code %d\n", SX_WEXITSTATUS(status));
		}
	}
}
