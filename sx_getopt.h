#ifndef SX_GETOPT
#define SX_GETOPT

extern int optind;
extern char *optarg;
extern int optopt;

int sx_getopt(int argc, char * const argv[], const char *optstring);

#endif
