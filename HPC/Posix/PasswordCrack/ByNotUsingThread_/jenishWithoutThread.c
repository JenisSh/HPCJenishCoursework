#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>


int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$m2B3050XukGk1Lfcb6mpyFyd9/i6EStSQJJgjHxJzgX2xYoLLcXrFW0YWszdPDOofKqWiFmmCX5ymoVPymd10.",
  "$6$KB$GTxjUa4D.rWcJXMr4k0pRNqPOfnleX5iYbVnFq.qh0dnmFxSdPUx9eItbF7kEzo.m3T4xEtBBshTCoEdI4.dG0",
  "$6$KB$6ZZ8YzjQPKuA87yBVX5k7yeMCTJNRIrQ29Px.tkIv1PYUjvUz8oc4NlrTxksO2k9RmpGKehIurIZnrGershFE/",
  "$6$KB$PDGItWv3Zc2.SqLtjFJDRerFSSdHncNsmbQjL8KtdpgzUo8mV/p6A9gLhb8WH98OcBOwYkrnOKgME5ISyAzrd/"
};


void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void Jenish(char *salt_and_encrypted){
  int x, y, z;     
  char salt[7];    
  char plain[7];   
  char *enc;       
  int count = 0;   

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}

int time_difference(struct timespec *start, struct timespec *finish,
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}


int main(int argc, char *argv[]){
  int j;
  struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  for(j=0;j<n_passwords;j<j++) {
    Jenish(encrypted_passwords[j]);
  }
	
     clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9)); 

  return 0;
}
