#ifndef SMALLIX_SX_SYSCALL
#define SMALLIX_SX_SYSCALL

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
