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
		: "r" (n), "r" (rdi)
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


int main() {

	printf("\nsx_syscall0 tests:\n\n");
	
	printf("getpid() result: %ld\n", getpid());
	printf("sx_syscall0(0x27) result: %ld\n\n", sx_syscall0(0x27));


	for (int i = 0; i < 15; i++) printf("-");

	
	printf("\n\nsx_syscall1 tests:\n\n");

	struct sysinfo sip, sip2;

	sx_syscall1(0x63, &sip);
	sysinfo(&sip2);

	printf("sx_syscall1 uptime: %ld\n", sip.uptime);
	printf("sysinfo uptime: %ld\n\n", sip2.uptime);


	for (int i = 0; i < 15; i++) printf("-");


	printf("\n\nsx_syscall2 tests:\n\n");

	if (sx_syscall2(0x3e, getpid(), 0) != 0) printf("sx_syscall2 error!\n");
	else printf("sx_syscall2 ran kill successfully!\n");


	for (int i = 0; i < 15; i++) printf("-");


	printf("\n\nsx_syscall3 tests:\n\n");
	sx_syscall3(0x01, 1, "sx_syscall3 write successful!\n", 30);


	for (int i = 0; i < 15; i++) printf("-");


	printf("\n\nsx_syscall4 tests:\n\n");

	sx_word fd = sx_syscall4(0x101, -100, (sx_word)"tmp_syscall_test.txt", 01 | 0100 | 01000, 0600);

	printf("openat raw fd: %ld\n", fd);

	sx_syscall3(0x01, fd, "writing to file", 15);
	sx_syscall1(0x03, fd);

	void *p = sx_syscall6(0x09, NULL, 4096, 0x1 | 0x2, 0x02 | 0x20, -1, 0);
	if (p < 0) printf("error :(\n");
	else {
		sx_syscall2(0x0b, p, 4096);
	}

	return 0;
}
