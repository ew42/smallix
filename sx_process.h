#ifndef SX_PROCESS
#define SX_PROCESS

extern char **sx_environ;

typedef int sx_pid_t;

sx_pid_t sx_fork(void);
int sx_execve(const char *pathname, char *const argv[], char *const envp[]);
sx_pid_t sx_waitpid(sx_pid_t pid, int *statusp, int options);
int sx_dup2(int oldfd, int newfd);


#endif
