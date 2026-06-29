/*
 * State-machine view of wc
 *
 * state:
 * bytes, lines, words -- counters for each
 * in_word -- whether pointer is inside a word
 *
 * initial state:
 * bytes, lines, words = 0
 * in_word = 0
 *
 * transitions:
 * T1, char is whitespace:
 * guard: c == ' ' | c == '\n' | c == '\t' | c == '\v' | c == '\f' | c == '\r'
 * bytes++
 * if c == '\n' -> lines++
 * in_word = 0
 *
 * T2, char isn't whitespace
 * guard: c != ' ' | c != '\n' | c != '\t' | c != '\v' | c != '\f' | c != '\r'
 * bytes++
 * if !in_word
 * 	words++
 *  in_word = 1
 *
 * terminal state:
 * 	terminate when no more input
 *
 * invariants:
 * bytes == how many bytes seen so far
 * lines == how many '\n's seen so far
 * words == how many whitespace -> non-whitespace transitions
 *
 */

#include "sx_file_descriptors.h"
#include "sx_stdio.h"
#include "sx_getopt.h"
#include "sx_types.h"

#define WC_BYTES 1
#define WC_CHARS (1 << 1)
#define WC_LINES (1 << 2)
#define WC_WORDS (1 << 3)

#define BUF_SIZE 8192

typedef struct wc_count {
	/*
	 * Output order is:
	 * lines, words, bytes/chars
	 */
	long lines;
	long words;
	long bytes;
	int in_word; // only used as a 0/1 bool
} wc_count;

static void count(wc_count *counts, int c) {
	if (c == ' ' | c == '\n' | c == '\t' | c == '\v' | c == '\f' | c == '\r') {
		if (c == '\n') counts->lines++;
		counts->in_word = 0;
	}
	else {
		if (!counts->in_word) {
			counts->words++;
			counts->in_word = 1;
		}
	}
	counts->bytes++;
}

int main(int argc, char *argv[]) {
	int opt;
	int flags = 0;
	while ((opt = sx_getopt(argc, argv, "clmw")) != -1) {
		switch (opt) {
			case 'c': flags |= WC_BYTES; break;
			case 'l': flags |= WC_LINES; break;
			case 'm': flags |= WC_CHARS; break;
			case 'w': flags |= WC_WORDS; break;
		}
	}

	wc_count total_count = {0};
	wc_count file_count = {0};

	char read_buf[BUF_SIZE];
	int fd;
	sx_ssize_t n_read;

	for (int i = optind; i < argc; i++) {
		fd = sx_open(argv[i], SX_O_RDONLY);
		while ((n_read = sx_read(fd, read_buf, BUF_SIZE)) != 0) {
			for (int j = 0; j < n_read; j++) {
				count(&file_count, read_buf[j]);
			}
		}
		total_count.lines += file_count.lines;
		total_count.words += file_count.words;
		total_count.bytes += file_count.bytes;
		if (!flags) {
			sx_printf("%lu ", file_count.lines);
			sx_printf("%lu ", file_count.words);
			sx_printf("%lu ", file_count.bytes);
		}
		else {
			if (flags & WC_LINES) sx_printf("%lu ", file_count.lines);
			if (flags & WC_WORDS) sx_printf("%lu ", file_count.words);
			if (flags & WC_CHARS) sx_printf("%lu ", file_count.bytes);
			if (flags & WC_BYTES) sx_printf("%lu", file_count.bytes);
		}
		sx_printf(" %s\n", argv[i]);
		file_count = (wc_count){0};
	}
	if (argc - optind > 1) {
		if (!flags) {
			sx_printf("%lu ", file_count.lines);
			sx_printf("%lu ", file_count.words);
			sx_printf("%lu ", file_count.bytes);
		}
		else {
			if (flags & WC_LINES) sx_printf("%lu ", file_count.lines);
			if (flags & WC_WORDS) sx_printf("%lu ", file_count.words);
			if (flags & WC_CHARS) sx_printf("%lu ", file_count.bytes);
			if (flags & WC_BYTES) sx_printf("%lu", file_count.bytes);
		}
		sx_printf("total\n");
	}
}
