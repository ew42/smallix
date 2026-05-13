#ifndef SX_FILE_DESCRIPTORS
#define SX_FILE_DESCRIPTORS

typedef unsigned long sx_size_t;
typedef long sx_ssize_t;

int sx_openat(int fd, const char *pathname, int flags, ...);
sx_ssize_t sx_read(int fd, void *buf, sx_size_t n);
sx_ssize_t sx_write(int fd, const char *buf, sx_size_t n);
int sx_close(int fd);

#endif
