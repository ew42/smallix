#ifndef SX_PROCESS
#define SX_PROCESS

#define SX_CLONE_NEWNS (1 << 17)
#define SX_CLONE_NEWUTS (1 << 26)
#define SX_CLONE_NEWPID (1 << 29)
#define SX_SIGCHLD 0x11

#define SX_WIFEXITED(s) (((s) & 0x7f) == 0)
#define SX_WEXITSTATUS(s) (((s) >> 8) & 0xff)
#define SX_WIFSIGNALED(s) (((s) & 0x7f) != 0 && ((s) & 0x7f) != 0x7f)
#define SX_WTERMSIG(s) ((s) & 0x7f)

#include "sx_types.h" 

extern char **sx_environ;

typedef int sx_pid_t;

sx_pid_t sx_fork(void);
int sx_execve(const char *pathname, char *const argv[], char *const envp[]);
sx_pid_t sx_waitpid(sx_pid_t pid, int *statusp, int options);
int sx_dup2(int oldfd, int newfd);
int sx_clone(unsigned long flags, void *stack, int *parent_tid, int *child_tid, unsigned long tls);
int sx_sethostname(const char *name, sx_size_t len);
int sx_pipe(int pipefd[2]);

#endif
