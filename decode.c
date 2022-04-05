#include "decode.h"

#include "fastpbkdf2.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>

int hmac_sha1_vector(const u8 *key, size_t key_len, size_t num_elem,
		     const u8 *addr[], const size_t *len, u8 *mac);

void decode(decode_t *input, unsigned char *password, size_t password_len)
{

	u8 pbk[32];
	u8 out[20];
	u8 *key_data[3] = {(unsigned char *)"PMK Name", input->ap, input->st};
	size_t len[3] = {8, 6, 6};
	fastpbkdf2_hmac_sha1(password, password_len, input->ssid, input->ssid_len, 4096, pbk, 32);
	hmac_sha1_vector(pbk, 32, 3, key_data, len, out);
	if(!cmppkid(out, input->target_pkid)) {
		printf("found password: |%s|\n", password);
		printhex("PKID1:", out, 16);
		printhex("PKID2:", input->target_pkid, 16);
		exit(0);
	}
	//printhex(out, 16);

}
		
