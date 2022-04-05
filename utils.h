#ifndef __UTILS_H__
#define __UTILS_H__ 1

#include "os.h"

void banner(void);
void credits(void);
int cmppkid(u8 *pkid1, u8 *pkid2);
void printhex(const char *s, u8 *buf, int len);
void macbin(u8 *mb, char *s, size_t check_len);

#endif /* __UTILS_H__ */
