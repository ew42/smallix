#ifndef SX_FILE_DESCRIPTORS
#define SX_FILE_DESCRIPTORS

#define PATH_MAX 4096 // found by testing on a Linux x86-64 machine
#define SX_AT_FDCWD -100 // found by testing on a Linux x86-64 machine

#define SX_O_DIRECTORY (1 << 4)
#define SX_O_RDONLY 0
#define SX_O_WRONLY 1
#define SX_O_RDWR (1 << 1)
#define SX_O_CREAT (1 << 6)
#define SX_O_TRUNC (1 << 9)

typedef unsigned long sx_size_t;
typedef long sx_ssize_t;
typedef unsigned int sx_mode_t;

struct sx_stat {
	/*
	 * Byte sizes and signs verified by testing on a x86-64 Linux machine
	 *
	 * Byte layout needs to be correct in order for the fstat syscall
	 * to write to the buffer correctly
	 */
	unsigned long sx_dev;
	unsigned long sx_ino;
	unsigned long sx_nlink;
	unsigned int sx_mode;
	unsigned int sx_uid;
	unsigned int sx_gid;
	unsigned int __pad0;
	unsigned long sx_rdev;
	long sx_size;
	long sx_blksize;
	long sx_blocks;
	unsigned long sx_atime;
	unsigned long sx_atime_nsec;
	unsigned long sx_mtime;
	unsigned long sx_mtime_nsec;
	unsigned long sx_ctime;
	unsigned long sx_ctime_nsec;
	long __unused[3];
};

int sx_openat(int fd, const char *pathname, int flags, ...);
int sx_open(const char *pathname, int flags, ...);
sx_ssize_t sx_read(int fd, void *buf, sx_size_t n);
sx_ssize_t sx_write(int fd, const char *buf, sx_size_t n);
sx_ssize_t sx_write_all(int fd, const char *buf, sx_size_t n);
int sx_close(int fd);
int sx_stat(char *pathname, struct sx_stat *buf);
int sx_fstat(int fd, struct sx_stat *buf);
void sx_exit(int status);

#endif
