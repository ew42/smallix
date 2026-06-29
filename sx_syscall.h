#ifndef SX_SYSCALL
#define SX_SYSCALL

#define SYS_openat 0x101
#define SYS_read 0x00
#define SYS_write 0x01
#define SYS_close 0x03
#define SYS_stat 0x04
#define SYS_fstat 0x05
#define SYS_dup2 0x21
#define SYS_fork 0x39
#define SYS_execve 0x3b
#define SYS_wait4 0x3d
#define SYS_getcwd 0x4f
#define SYS_chdir 0x50
#define SYS_mkdir 0x53
#define SYS_pivot_root 0x9b
#define SYS_mount 0xa5
#define SYS_umount2 0xa6
#define SYS_exit_group 0xe7

typedef long sx_word;

sx_word sx_syscall0(sx_word n);
sx_word sx_syscall1(sx_word n, sx_word arg1);
sx_word sx_syscall2(sx_word n, sx_word arg1, sx_word arg2);
sx_word sx_syscall3(sx_word n, sx_word arg1, sx_word arg2, sx_word arg3);
sx_word sx_syscall4(sx_word n, sx_word arg1, sx_word arg2, sx_word arg3,
					sx_word arg4);
sx_word sx_syscall5(sx_word n, sx_word arg1, sx_word arg2, sx_word arg3,
					sx_word arg4, sx_word arg5);
sx_word sx_syscall6(sx_word n, sx_word arg1, sx_word arg2, sx_word arg3,
					sx_word arg4, sx_word arg5, sx_word arg6);

#endif 
