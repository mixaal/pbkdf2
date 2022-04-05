#ifndef __DECODE_H__
#define __DECODE_H__ 1

#include "os.h"

typedef struct {
	u8 ap[6];
        u8 st[6];
	unsigned char *ssid;
	size_t ssid_len;
	u8 target_pkid[16];
} decode_t;

void decode(decode_t *input, unsigned char *password, size_t password_len);

#endif /* __DECODE_H__ */
