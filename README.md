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
            - [x] sx_pipe
        - [x] Processes
            - [x] sx_exit
            - [x] sx_fork
            - [x] sx_execve
            - [x] sx_waitpid
        - [ ] Files and paths
            - [x] sx_stat
            - [x] sx_fstat
            - [ ] sx_lstat
            - [ ] sx_unlink
            - [x] sx_mkdir
            - [x] sx_rmdir
            - [x] sx_chdir
            - [x] sx_getcwd
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

### Milestone 4, Filesystem Operations 

- [x] create a directory -> chdir into it -> getcwd gives correct location
- [x] mount a filesystem -> unmount it
- [x] pivot_root swaps root filesystem

In order to implement those, we need:

- [x] sx_mkdir
- [x] sx_chdir
- [x] sx_getcwd
- [x] sx_mount
- [x] sx_umount2
- [x] sx_pivot_root

### Milestone 5, Namespace Isolation

Goal: fork a child into new PID and UTS namespaces, PID 1 and unique hostname

- [x] `./sx-isolate /bin/bash`, child runs in a new namespace
- [x] `echo $$`, in child prints 1
- [x] hostname in child prints 'sx-container'
- [x] host PID table and hostname unaffected

In order to implement those, we need:

- [x] sx_clone with `CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWUTS`
- [x] sx_sethostname

### Milestone 6, Filesystem Isolation

Goal: give the contained process its own root filesystem

- [x] `./sx-contain ./alpine-rootfs /bin/sh` drops into isolated shell
- [x] `ls /` shows Alpine filesystem
- [x] `ps` shows only shell (PID 1) and ps itself
- [x] no way to reach host filesystem

In order to implement those, we need:

- [x] bind-mount rootfs to a mount point
- [x] sx_pivot_root to swap it in as new root
- [x] `chdir("/")`
- [x] sx_umount2 old root with MNT_DETACH
- [x] sx_mount proc filesystem so /proc works inside

### Milestone 7, Resource Limits

Goal: enforce a memory ceiling on the contained process

- [x] `./sx-contain -m 64 ./alpine-roofs /bin/sh`, 64MB memory limit
- [x] process that allocates 128MB inside container gets OOM-killed
- [x] host cgroup pseudo-file confirms limit is set

In order to implement those, we need:

- [x] `mkdir /sys/fs/cgroup/sx-container`
- [x] sx_pipe, to prevent a race condition between child/parent
- [x] sx_rmdir, to cleanup after creating the cgroup
