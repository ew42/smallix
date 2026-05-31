#include "sx_syscall.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <unistd.h>

sx_word sx_syscall0(sx_word n) {
	sx_word ret;

	register sx_word rax __asm__ ("rax") = n;

	__asm__ volatile (
		"syscall \n  "
		: "=a" (ret)
		: "r" (rax)
		: "rcx", "r11", "memory"
	);

	return ret;
}


sx_word sx_syscall1(sx_word n, sx_word arg1) {
	sx_word ret;

	register sx_word rax __asm__ ("rax") = n;
	register sx_word rdi __asm__ ("rdi") = arg1;

	__asm__ volatile (
		"syscall \n  "
		: "=a" (ret)
		: "r" (rax), "r" (rdi)
		: "rcx", "r11", "memory"
	);

	return ret;
}

sx_word sx_syscall2(sx_word n, sx_word arg1, sx_word arg2) {
	sx_word ret;

	register sx_word rax __asm__ ("rax") = n;
	register sx_word rdi __asm__ ("rdi") = arg1;
	register sx_word rsi __asm__ ("rsi") = arg2;

	__asm__ volatile (
		"syscall \n  "
		: "=a" (ret)
		: "r" (rax), "r" (rdi), "r" (rsi)
		: "rcx", "r11", "memory"
   );

	return ret;
}

sx_word sx_syscall3(sx_word n, sx_word arg1, sx_word arg2, sx_word arg3) {
	sx_word ret;

	register sx_word rax __asm__ ("rax") = n;
	register sx_word rdi __asm__ ("rdi") = arg1;
	register sx_word rsi __asm__ ("rsi") = arg2;
	register sx_word rdx __asm__ ("rdx") = arg3;

	__asm__ volatile (
		"syscall \n  "
		: "=a" (ret)
		: "r" (rax), "r" (rdi), "r" (rsi), "r" (rdx)
		: "rcx", "r11", "memory"
   );

	return ret;
}

sx_word sx_syscall4(sx_word n, sx_word arg1, sx_word arg2, sx_word arg3,
					sx_word arg4) {
	sx_word ret;

	register sx_word rax __asm__ ("rax") = n;
	register sx_word rdi __asm__ ("rdi") = arg1;
	register sx_word rsi __asm__ ("rsi") = arg2;
	register sx_word rdx __asm__ ("rdx") = arg3;
	register sx_word r10 __asm__ ("r10") = arg4;

	__asm__ volatile (
		"syscall \n  "
		: "=a" (ret)
		: "r" (rax), "r" (rdi), "r" (rsi), "r" (rdx), "r" (r10)
		: "rcx", "r11", "memory"
   );

	return ret;
}

sx_word sx_syscall5(sx_word n, sx_word arg1, sx_word arg2, sx_word arg3,
					sx_word arg4, sx_word arg5) {
	sx_word ret;

	register sx_word rax __asm__ ("rax") = n;
	register sx_word rdi __asm__ ("rdi") = arg1;
	register sx_word rsi __asm__ ("rsi") = arg2;
	register sx_word rdx __asm__ ("rdx") = arg3;
	register sx_word r10 __asm__ ("r10") = arg4;
	register sx_word r8 __asm__ ("r8") = arg5;

	__asm__ volatile (
		"syscall \n  "
		: "=a" (ret)
		: "r" (rax), "r" (rdi), "r" (rsi), "r" (rdx), "r" (r10), "r" (r8)
		: "rcx", "r11", "memory"
   );

	return ret;
}

sx_word sx_syscall6(sx_word n, sx_word arg1, sx_word arg2, sx_word arg3,
					sx_word arg4, sx_word arg5, sx_word arg6) {
	sx_word ret;

	register sx_word rax __asm__ ("rax") = n;
	register sx_word rdi __asm__ ("rdi") = arg1;
	register sx_word rsi __asm__ ("rsi") = arg2;
	register sx_word rdx __asm__ ("rdx") = arg3;
	register sx_word r10 __asm__ ("r10") = arg4;
	register sx_word r8 __asm__ ("r8") = arg5;
	register sx_word r9 __asm__ ("r9") = arg6;

	__asm__ volatile (
		"syscall \n  "
		: "=a" (ret)
		: "r" (rax), "r" (rdi), "r" (rsi), "r" (rdx), "r" (r10), "r" (r8), "r" (r9)
		: "rcx", "r11", "memory"
   );

	return ret;
}

