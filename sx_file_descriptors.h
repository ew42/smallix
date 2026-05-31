#ifndef SX_FILE_DESCRIPTORS
#define SX_FILE_DESCRIPTORS

#define PATH_MAX 4096 // found by testing on a Linux x86-64 machine
#define SX_AT_FDCWD -100 // found by testing on a Linux x86-64 machine

#define SX_O_DIRECTORY (1 << 4)
#define SX_O_RDONLY 0
#define SX_O_WRONLY 1
#define SX_O_RDWR (1 << 1)

typedef unsigned long sx_size_t;
typedef long sx_ssize_t;

typedef struct sx_stat {
	/*
	 * Byte sizes and signs verified by testing on a x86-64 Linux machine
	 *
	 * Byte layout needs to be correct in order for the fstat syscall
	 * to write to the buffer correctly
	 */
	unsigned long st_dev;
	unsigned long st_ino;
	unsigned int st_mode;
	unsigned long st_nlink;
	unsigned int st_uid;
	unsigned int st_gid;
	unsigned long st_rdev;
	long st_size;
	long st_blksize;
	long st_blocks;
	long sx_atime;
	long sx_mtime;
	long sx_ctime;
} sx_stat;

int sx_openat(int fd, const char *pathname, int flags, ...);
int sx_open(const char *pathname, int flags, ...);
sx_ssize_t sx_read(int fd, void *buf, sx_size_t n);
sx_ssize_t sx_write(int fd, const char *buf, sx_size_t n);
sx_ssize_t sx_write_all(int fd, const char *buf, sx_size_t n);
int sx_close(int fd);
int sx_fstat(int fd, struct sx_stat *buf);
void sx_exit(int status);

#endif
