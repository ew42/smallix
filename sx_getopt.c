#include "sx_getopt.h"

int optopt;
char *optarg;

int optind = 1;
static int optpos = 0;

int sx_getopt(int argc, char * const argv[], const char *optstring) {
	/*
	 * state:
	 * - optind, marks the index of the next element to be processed in argv
	 * - optpos, marks the index of the next char to be processed in argv[optind] | optpos == 0, means that "I haven't looked at this element"
	 *
	 * initial state:
	 * - optind = 1
	 * - optpos = 0
	 *
	 * transitions (one per getopt() call):
	 * T1 - should you look at this element? (only ask on new elements)
	 * 	guard: optpos == 0
	 * 	if optind >= argc -> return -1
	 * 	if *argv[optind] != '-' -> return -1
	 * 	if argv[optind] is exactly '-' -> return -1
	 * 	if argv[optind] is exactly '--' -> return -1
	 * 	else -> optpos++;
	 *
	 * T2 - read the option char at optpos
	 * 	c = argv[optind][optpos]
	 * 	optpos++
	 *     if argv[optind][optpos] == '\0'
	 *	    optind++;
	 *	    optpos = 0;
	 *	   if *(argv[optind] + optpos) not in optstring -> return '?' set optopt
	 *	   if *(argv[optind] + optpos) in optstring -> return that char
	 *	   if *(argv[optind] + optpos) in optstring with colon
	 *		if optind + 1 < argc -> return char and set optarg
	 *		else return ? and set optopt (missing arg)
	 *
	 * invariants:
	 * optind <= argc
	 * optpos < strlen(argv[optind]) 
	 * 
	 */
	
	// T1
	if (optpos == 0) {
		if (optind >= argc) {
			return -1;
		}
		else if (argv[optind][optpos] != '-') {
			return -1;
		}
		else if (argv[optind][optpos + 1] == '\0') {
			return -1;
		}
		else if (argv[optind][optpos + 1] == '-' && argv[optind][optpos + 2] == '\0') {
			optind++;
			return -1;
		}
		else {
			optpos++;
		}
	}
	
	// T2
	int c = argv[optind][optpos];
	optpos++;
	if (argv[optind][optpos] == '\0') {
		optind++;
		optpos = 0;
	}
	const char *p = optstring;
	while (*p && *p != c) p++; // p == '\0' if not in optstring, p == c if in optstring
	if (c == *p) { // if in optstring
		if (*(p+1) == ':') { // takes an arg
			if (optpos > 0) { // the arg is glued to the option
				optarg = &argv[optind][optpos];
				optind++;
				optpos = 0;
				return c;
			}
			else if (optind < argc) { // the arg is the next index
				optarg = argv[optind];
				optind++;
				return c;
			}
			else { // no arg was given
				optopt = c;
				return '?';
			}
		}
		else {
			return c;
		}
	}
	else { // not in optstring
		optopt = c;
		return '?';
	}
}
