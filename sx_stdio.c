#include "sx_stdio.h"
#include <stdio.h>
#include <stdarg.h>

int sx_printf(const char *buf, ...) {
	va_list ap;
	va_start(ap, buf);
	int ret = vprintf(buf, ap);
	va_end(ap);
	return ret;
}

int sx_utoa(unsigned long n, char *buf) {
	char tmp[20]; // max digit length of a unsigned long
	int i = 0;
	if (n == 0) tmp[i++] = '0';
	while (n > 0) {
		tmp[i++] = '0' + (n % 10);
		n /= 10;
	}
	int len = i;
	for (int j = 0; j < len; j++) buf[j] = tmp[len - 1 - j];
	return len; // return len, put str representation into buf
}

unsigned long sx_strlen(const char *s) {
    const char *p = s;
    while (*p) p++;
    return p - s;
}
