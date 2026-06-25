#ifndef SX_PROCESS
#define SX_PROCESS

extern char **sx_environ;

typedef int sx_pid_t;

sx_pid_t sx_fork(void);
int sx_execve(const char *pathname, char *const argv[], char *const envp[]);


#endif
