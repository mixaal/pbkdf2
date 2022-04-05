#include <stdio.h>
#include <sys/types.h>
#include <time.h>

#include "decode.h"
#include "gen.h"
#include "utils.h"


int main(void)
{
	banner();
	credits();
	char *charsets[10] = {
		"bouvwxyz",
		"bouvwxyz",
		"bouvwxyz",
		"bouvwxyz",
		"bouvwxyz",
		"bouvwxyz",
		"bouvwxyz",
		"bouvwxyz",
		"0123456789",
		"0123456789"
	};

	decode_t input;
	macbin(input.ap, "888888888888", 6);
	macbin(input.st, "c022c0c0c0c0", 6);
	macbin(input.target_pkid, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 16);

        input.ssid=(unsigned char *)"xxxxxxx";
	input.ssid_len = 7;


	gen(charsets, 10, &input);
}
