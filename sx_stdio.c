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
