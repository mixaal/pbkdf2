#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
#include "gen.h"
#include "decode.h"
#include "utils.h"

void gen(char **charset, int length, decode_t *input)
{
	size_t l[length];
	for(int i=0;i<length;i++) {
		printf("i=%d ch[i]=%s\n", i, charset[i]);
       		l[i] = strlen(charset[i]);
	}
	unsigned long powers[length];


	double dt = 1;
	unsigned long t = 1;

	unsigned long total = 0;
	for(int i=0; i<length; i++) {
		powers[length-i-1] = t;
		t *= l[length-i-1];
		dt *= l[length-i-1];
		//printf("dt=%lf t=%ld\n", dt, t);
		if(dt > (double)ULONG_MAX) {
			fprintf(stderr, "too many combinations!");
			exit(-1);
		}

	}
	//for(int i=0; i<length; i++) {
	//	printf("powers[%d]=%ld\n", i, powers[i]);
	//}
	total = (unsigned long)dt;

        time_t start = time(NULL);
	time_t now;
	long elapsed;
	long cracked = 0;
	float left;
	float progress;
#pragma omp parallel for
	for(unsigned long j=0; j<total; j++) {
		long lastbreak =0;
	        unsigned char passwd[length+1];
	        passwd[length]='\0';
		for(int i=0; i<length; i++) {
			unsigned long frac = j / powers[i];
			unsigned long res = frac % l[i];
			passwd[i] = charset[i][res];
				
		}
	        if((cracked%100000)==0) {
		      char timebuf[256];
		      now = time(NULL);
		      elapsed = now - start;
		      if(lastbreak==0) lastbreak = start;
		      long duration = now - lastbreak;
		      if(duration>3600) {
			      printf("\nTime to rest for 4mins\n");
			      sleep(240);
			      lastbreak = now;
		      }
		      progress = (float)cracked/total;
		      left = (float)elapsed/progress;
		      format_time(&left, timebuf, 256);
		      printf("%ld: %s, speed: %f progress: %.3f  left: %s                         \r", j, passwd, (float)cracked/elapsed, progress, timebuf);
		  
		      fflush(stdout);
		}
		cracked++;
		//printf("P:%s\n", passwd);
		decode(input, passwd, length);
	}
}
