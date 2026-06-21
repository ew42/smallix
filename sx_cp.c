#include "sx_file_descriptors.h"
#include "sx_getopt.h"

#define BUF_SIZE 8192

int main(int argc, char *argv[]) {
	int opt;
	while ((opt = sx_getopt(argc, argv, "")) != -1) {
		continue;
	}
	int source_file = sx_open(argv[optind], SX_O_RDONLY);
	struct sx_stat source_file_stat; 
	sx_fstat(source_file, &source_file_stat);

	
	struct sx_stat target_file_stat; 
	sx_stat(argv[optind+1], &target_file_stat);

	if (source_file_stat.sx_ino == target_file_stat.sx_ino && source_file_stat.sx_dev == target_file_stat.sx_dev) {
		return 1;
	}

	int target_file = sx_open(argv[optind + 1], SX_O_WRONLY | SX_O_CREAT | SX_O_TRUNC, source_file_stat.sx_mode);

	char read_buf[BUF_SIZE];
	unsigned int n_read;
	while ((n_read = sx_read(source_file, read_buf, BUF_SIZE)) != 0) {
		sx_write_all(target_file, read_buf, n_read);
	}

	return 0;
}
