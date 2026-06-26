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
            - [x] sx_dup2
            - [ ] sx_pipe
        - [ ] Processes
            - [x] sx_exit
            - [x] sx_fork
            - [x] sx_execve
            - [x] sx_waitpid
        - [ ] Files and paths
            - [x] sx_stat
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
    - [x] cat
    - [x] wc
    - [x] cp (no directories/symlinks, handles for copy-on-self)
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

- [x] cat
- [x] wc
- [x] cp (no directories/symlinks, handles for copy-on-self)

In order to implement those, we need

- [x] sx_read
- [x] sx_write
- [x] sx_write_all
- [x] sx_openat
- [x] sx_open
- [x] sx_close
- [x] sx_exit
- [x] sx_fstat

### Milestone 2, Memory Foundations

Goal: Write a minimal bump allocator so future milestone can call sx\_malloc and receive usable outputs

- [x] sx_malloc (4MB static arena bump allocator)
- [x] sx_free

In order to implement those, we need

- nothing, as mmap/munmap aren't needed in the simple allocator described

### Milestone 3, Process Lifecycle

Goal: fork a child, exec a program in it, wait for it to finish

- [x] `./sx-spawn /bin/echo hello`, forks, execs, parent waits, and prints exit status

In order to implement those, we need

- [x] sx_fork
- [x] sx_execve
- [x] sx_waitpid
- [x] sx_dup2
