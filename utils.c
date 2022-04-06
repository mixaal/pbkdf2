#include "utils.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static _Bool is_color(void)
{
	char *term = getenv("TERM");
	if(term==NULL) return 0;
	return strstr(term, "color")!=NULL;
}

static _Bool is_redirected(void)
{
	int foo;
	return ioctl(STDIN_FILENO, FIONREAD, &foo) == -1;
}


static void red(void)
{
	if(is_color() && !is_redirected()) puts("\e[31m");
}
static void blue(void)
{
	if(is_color() && !is_redirected()) puts("\e[34m");
}


static void reset(void)
{
	if(is_color() && !is_redirected()) puts("\e[0m");
}

static void cls(void)
{
	if(!is_redirected()) puts("\e[2J\e[1;1H");
}


void banner(void)
{
	int scroll = (is_redirected()) ? 0 : 10;
	for(int i=scroll; i>=0; i--) {
	cls();
		for(int j=0;j<i;j++) puts(" ");
	red();
	puts(" ███▄ ▄███▓ ██▓ ██ ▄█▀ ▄████▄      ██▓███    ██████▓██   ██▓ ▄████▄   ██░ ██  ▒█████     ▄▄▄█████▓ ██▓ ▄████▄");
	puts("▓██▒▀█▀ ██▒▓██▒ ██▄█▒ ▒██▀ ▀█     ▓██░  ██▒▒██    ▒ ▒██  ██▒▒██▀ ▀█  ▓██░ ██▒▒██▒  ██▒   ▓  ██▒ ▓▒▓██▒▒██▀ ▀█");
	puts("▓██    ▓██░▒██▒▓███▄░ ▒▓█    ▄    ▓██░ ██▓▒░ ▓██▄    ▒██ ██░▒▓█    ▄ ▒██▀▀██░▒██░  ██▒   ▒ ▓██░ ▒░▒██▒▒▓█    ▄");
	puts("▒██    ▒██ ░██░▓██ █▄ ▒▓▓▄ ▄██▒   ▒██▄█▓▒ ▒  ▒   ██▒ ░ ▐██▓░▒▓▓▄ ▄██▒░▓█ ░██ ▒██   ██░   ░ ▓██▓ ░ ░██░▒▓▓▄ ▄██▒");
	puts("▒██▒   ░██▒░██░▒██▒ █▄▒ ▓███▀ ░   ▒██▒ ░  ░▒██████▒▒ ░ ██▒▓░▒ ▓███▀ ░░▓█▒░██▓░ ████▓▒░     ▒██▒ ░ ░██░▒ ▓███▀ ░");
	puts("░ ▒░   ░  ░░▓  ▒ ▒▒ ▓▒░ ░▒ ▒  ░   ▒▓▒░ ░  ░▒ ▒▓▒ ▒ ░  ██▒▒▒ ░ ░▒ ▒  ░ ▒ ░░▒░▒░ ▒░▒░▒░      ▒ ░░   ░▓  ░ ░▒ ▒  ░");
	puts("░  ░      ░ ▒ ░░ ░▒ ▒░  ░  ▒      ░▒ ░     ░ ░▒  ░ ░▓██ ░▒░   ░  ▒    ▒ ░▒░ ░  ░ ▒ ▒░        ░     ▒ ░  ░  ▒");
	puts("░      ░    ▒ ░░ ░░ ░ ░           ░░       ░  ░  ░  ▒ ▒ ░░  ░         ░  ░░ ░░ ░ ░ ▒       ░       ▒ ░░");
	puts("       ░    ░  ░  ░   ░ ░                        ░  ░ ░     ░ ░       ░  ░  ░    ░ ░               ░  ░ ░");
	puts("                      ░                             ░ ░     ░                                         ░");
	usleep(30000L);
	}
	reset();
}

void credits(void)
{
	blue();
	puts("                                                | (_)  _                     _         ");
	puts("  ____ ___   ____ _____     ____  ____ _____  __| |_ _| |_  ___ _     ____ _| |_ _____ ");
	puts(" / ___) _ \\ / ___) ___ |   / ___)/ ___) ___ |/ _  | (_   _)/___|_)   / ___|_   _|___  )");
	puts("( (__| |_| | |   | ____|  ( (___| |   | ____( (_| | | | |_|___ |_   ( (___  | |_ / __/ ");
	puts(" \\____)___/|_|   |_____)   \\____)_|   |_____)\\____|_|  \\__|___/(_)   \\____)  \\__|_____)");
	reset();
	puts(" --- for super-fast pbkdf2 x64 implementation");
	puts(" ---  https://github.com/ctz/fastpbkdf2");
}

void printhex(const char *s, u8 *buf, int len)
{
	printf("%s", s);
	for(int i=0; i<len; i++) {
		printf("%02x", buf[i]);
	}
	printf("\n");
}

static char convert(char c)
{
	if (c>='0' && c<='9') return  c-'0';
        if (c>='a' && c<='f') return 10 + c - 'a';
        if (c>='A' && c<='F') return 10 + c - 'A';
	return -1;
}

int cmppkid(u8 *pkid1, u8 *pkid2)
{
	for(int i=0; i<16; i++) {
		if(pkid1[i]!=pkid2[i]) return 1;
	}
	return 0;
}

void macbin(u8 *mb, char *s, size_t check_len)
{
	size_t l2 = strlen(s) / 2;
	if(l2!=check_len) {
		fprintf(stderr, "check len failed: check_len=%ld l2=%ld\n", check_len, l2);
		exit(-1);
	}
	for(int i=0; i<l2; i++) {
		//printf("%c   %c\n", s[2*i], s[2*i+1]);
		u8 hn = convert(s[2*i]); 
		u8 ln = convert(s[2*i+1]);
		//printf("---> %d %d\n", hn, ln);
		mb[i] = 16*hn + ln;
		//printf("%02x\n", mb[i]);
	}
	printf("\n");
}

void format_time(float *secs, char *buf, size_t len)
{
	int h = *secs  / 3600;
	int days = h / 24;
	h -= 24*days;
	int mins = (long)*secs % 3600;
	mins /= 60;
	snprintf(buf, len, "%dd %02dh %02dm", days, h, mins); 
}

