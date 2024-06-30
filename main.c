#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
	MOD_NONE  = 1>>1,

	MOD_LOWER = 1>>0,
	MOD_UPPER = 1<<1,
	MOD_PUNCT = 1<<2,
	MOD_NUMS  = 1<<3,
} mod_t;

static char const lower[] = "abcdefghijklmnopqrstuvwxyz";
static char const upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static char const punct[] = "',./=\\\"<>?+|`~!@#$%^&*()[]{};:";

char
rand_lower(void)
	/* VOID */
{
	return lower[rand()%(sizeof(lower)-1)];
};

char
rand_upper(void)
	/* VOID */
{
	return upper[rand()%(sizeof(upper)-1)];
};

char
rand_punct(void)
	/* VOID */
{
	return punct[rand()%(sizeof(punct)-1)];
};

char rand_nums(void)
	/* VOID */
{
	return '0'+rand()%10;
};

int
main(argc, argv)
	int argc;
	char *argv[argc];
{
	size_t len = 0;
	mod_t  mod = 0;
	char * ptr = 0;
	char (*funcs[4])(void) = {0};
	char i = 0;

	if (argc != 3) {
		fprintf(stderr, "ERR: Usage: %s <len> <mode>\n", *argv);
		return -1;
	};

	if (!sscanf(argv[1], "%zu", &len)) {
		fputs("ERR: Lenght must be unsgned integer\n", stderr);
		return -1;
	};

	if (len == 0) {
		fputs("ERR: Lenght can't be 0\n", stderr);
		return -1;
	};

	ptr = argv[2];
loop:
	switch (*ptr++) {
	case 0:
		break;
	case 'L':
	case 'l':
		if (mod & MOD_LOWER) {
		already_set:
			fprintf(stderr, "ERR: mode %c is already set\n", ptr[-1]);
			return -1;
		}

		mod |= MOD_LOWER;
		funcs[i++] = rand_lower;
		goto loop;
	case 'U':
	case 'u':
		if (mod & MOD_UPPER)
			goto already_set;

		mod |= MOD_UPPER;
		funcs[i++] = rand_upper;
		goto loop;
	case 'P':
	case 'p':
		if (mod & MOD_PUNCT)
			goto already_set;

		mod |= MOD_PUNCT;
		funcs[i++] = rand_punct;
		goto loop;
	case 'N':
	case 'n':
		if (mod & MOD_NUMS)
			goto already_set;

		mod |= MOD_NUMS;
		funcs[i++] = rand_nums;
		goto loop;
	default:
		fprintf(stderr, "ERR: What's that mode?: %c\n", ptr[-1]);
		return -1;
	};


	if (mod == 0) {
		fputs("ERR: You can't declare empty mode\n", stderr);
		return -1;
	};

	srand(time(NULL));
	ptr = calloc(1, len+1);
	for (size_t j = 0; j < len; ++j)
		ptr[j] = funcs[rand()%i]();
	puts(ptr);
	free(ptr);
};
