#ifndef SX_FILESYSTEM
#define SX_FILESYSTEM

#include "sx_types.h"

/*
 * Mount flags at /usr/include/linux/mount.h
 */

#define SX_MS_BIND 4096
#define SX_MS_REC 16384
#define SX_MS_PRIVATE (1<<18)

int sx_mkdir(const char *path, sx_mode_t mode);
int sx_chdir(const char *path);
char *sx_getcwd(char *buf, sx_size_t size);
int sx_mount(const char *source, const char *target, const char *filesystemtype, unsigned long mountflags, const void *data);
int sx_umount2(const char *target, int flags);
int sx_pivot_root(const char *new_root, const char *put_old);


#endif
