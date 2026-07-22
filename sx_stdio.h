#ifndef SX_STDIO
#define SX_STDIO

int sx_printf(const char *buf, ...);
int sx_utoa(unsigned long n, char *buf);
unsigned long sx_strlen(const char *s);

#endif
