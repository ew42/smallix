#include "sx_file_descriptors.h"

#define BUFSIZE 8192

int cat_fd(int fd) {
	char buf[BUFSIZE];
	int n = 1;
	int ret;
	while ((n = sx_read(fd, buf, BUFSIZE)) > 0) {
		ret = sx_write_all(1, buf, n);
		if (ret < 0) return ret;
	}

}

int cat_file(char *pathname) {
	int fd = sx_open(pathname, SX_O_RDONLY);
	if (fd < 0) return fd;
	else {
		int ret = cat_fd(fd);
		sx_close(fd);
		return ret;
	}
}

int main(int argc, char *argv[]) {
	if (argc == 1) return cat_fd(0);
	for (int i = 1; i < argc; i++) {
		int ret = (argv[i][0] == '-' && argv[i][1] == '\0') ? cat_fd(0) : cat_file(argv[i]);
		if (ret < 0) return ret;
	}

	return 0;
}
