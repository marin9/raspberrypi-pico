#include "lib.h"

int isalnum(int c) {
	if (c >= 'A' && c <= 'Z')
		return 1;

	if (c >= 'a' && c <= 'z')
		return 1;

	if (c >= '0' && c <= '9')
		return 1;

	return 0;
}

int isalpha(int c) {
	if (c >= 'A' && c <= 'Z')
		return 1;

	if (c >= 'a' && c <= 'z')
		return 1;

	return 0;
}

int iscntrl(int c) {
	if (c >= 0 && c <= 31)
		return 1;

	if (c == 127)
		return 1;

	return 0;
}

int isdigit(int c) {
	if (c >= '0' && c<= '9')
		return 1;
	else
		return 0;
}

int isgraph(int c) {
	if (isalnum(c) || ispunct(c))
		return 1;
	else
		return 0;
}

int islower(int c) {
	if (c >= 'a' && c <= 'z')
		return 1;
	else
		return 0;
}

int isprint(int c) {
	if (isalnum(c))
		return 1;

	if(ispunct(c))
		return 1;

	if(isspace(c))
		return 1;

	return 0;
}

int ispunct(int c) {
	if (c >= 33 && c <= 47)
		return 1;

	if (c >= 58 && c <= 64)
		return 1;

	if (c >= 91 && c <= 96)
		return 1;

	if (c >= 123 && c <= 126)
		return 1;

	return 0;
}

int isspace(int c) {
	if (c == ' ' || c == '\t')
		return 1;
	else
		return 0;
}

int isupper(int c) {
	if (c >= 'A' && c <= 'Z')
		return 1;
	else
		return 0;
}

int isxdigit(int c) {
	if (c >= '0' && c <= '9')
		return 1;

	if (c >= 'A' && c <= 'F')
		return 1;

	if (c >= 'a' && c <= 'f')
		return 1;

	return 0;
}

int tolower(int c) {
	if (c >= 'A' && c <= 'Z')
		return c-'A'+'a';
	else
		return c;
}

int toupper(int c) {
	if (c >= 'a' && c <= 'z')
		return c-'a'+'A';
	else
		return c;
}
