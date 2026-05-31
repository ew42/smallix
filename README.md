# Smallix
A small posix-style userland designed for Linux x86-64 in C.

## Outline

- [ ] Runtime
    - [ ] Syscall wrappers
        - [ ] File Descriptors
            - [x] sx_read
            - [x] sx_write
            - [x] sx_write_all
            - [x] sx_openat
            - [x] sx_open
            - [x] sx_close
            - [ ] sx_dup2
            - [ ] sx_pipe
        - [ ] Processes
            - [x] sx_exit
            - [ ] sx_fork
            - [ ] sx_execve
            - [ ] sx_waitpid
        - [ ] Files and paths
            - [ ] sx_stat
            - [x] sx_fstat
            - [ ] sx_lstat
            - [ ] sx_unlink
            - [ ] sx_mkdir
            - [ ] sx_rmdir
            - [ ] sx_chdir
            - [ ] sx_getcwd
        - [ ] Memory Mapping
            - [ ] sx_mmap
            - [ ] sx_munmap
    - [ ] Allocator
        - [ ] sx_malloc
        - [ ] sx_free
        - [ ] sx_realloc
        - [ ] sx_calloc
        - [ ] sx_heap_check
- [ ] coreutils
    - [ ] cat
    - [ ] wc
    - [ ] cp
    - [ ] rm 
    - [ ] mkdir
    - [ ] pwd
    - [ ] env
- [ ] Shell

## Milestones

We're going to structure milestones based off an end-goal and what we need to implement in order to get there.

### Milestone 0, Linux x86-64 Syscall Bridge

Goal: Create C wrappers for Linux syscalls

- [x] \__sx_syscall0
- [x] \__sx_syscall1
- [x] \__sx_syscall2
- [x] \__sx_syscall3
- [x] \__sx_syscall4
- [x] \__sx_syscall5
- [x] \__sx_syscall6

### Milestone 1, Simple Utils

- [ ] cat
- [ ] wc
- [ ] cp (content-only for now, we'll do metadata later)

In order to implement those, we need

- [x] sx_read
- [x] sx_write
- [x] sx_write_all
- [x] sx_openat
- [x] sx_open
- [x] sx_close
- [x] sx_exit
- [x] sx_fstat

### Milestone 2, Process Runtime + Command Execution

Goal: run external commands from the shell

Shell features:

- [ ] prompt/read loop
- [ ] parse whitespace-separated argv
- [ ] execute absolute/relative paths
- [ ] wait for foreground command
- [ ] record child command's exit status

we need

- [ ] sx_fork
- [ ] sx_execve
- [ ] sx_waitpid
