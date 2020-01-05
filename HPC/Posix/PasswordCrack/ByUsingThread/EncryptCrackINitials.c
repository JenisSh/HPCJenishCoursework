#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>

int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$Ql84w9ekQYO/rUUJ8kDAM39ShDJ84imLj7DhoHutDfUkwnpfl35xw5LMDfukYOYM5BjhGihIFQQCkQNW1SWWY/",
  "$6$KB$jCd1c/KVgpaD3Kr9QNKRFqtV4CM22zQxwoCuscXrWzOKz8LU3pBM9c4yU0rZFxGtAjgyqEKMn2Q73A95rHfu11",
  "$6$KB$6/x6JXWEoeegl1E88QsIYmAnSXnj2DEnsJ.JcNy43n4vmJ9zOIq6ftJ0oql6xztcAFgeh4.96.qZbNcQrC8HC0",
  "$6$KB$iMbefPEIWxYr8Q1WBDCx2zTwkXkp1r9XpZS.wnymcqiLDObhmWCJRya6qGC9zn9imLSHdkHJO..ok/xwAWkSo."
};



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void crackpassone(char *salt_and_encrypted){
  int j, x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[8];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);


for(j='A'; j<='M'; j++){
  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%c%02d", j, x, y, z);
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
}
  printf("%d solution explored  \n", count);
}


void crackpasstwo(char *salt_and_encrypted){
  int j, x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[8];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);


for(j='N'; j<='Z'; j++){
  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%c%02d", j, x, y, z);
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
}
  printf("%d solution explored  \n", count);
}



int time_difference(struct timespec *start,
                    struct timespec *finish,
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

  pthread_t firstthread, secondthread;
  int j;

  struct timespec start, finish;
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

   for(j=0;j<n_passwords;j<j++)
   {

    pthread_create(&firstthread, NULL, (void*) crackpassone, encrypted_passwords[j]);
    pthread_create(&secondthread, NULL, (void*) crackpasstwo, encrypted_passwords[j]);
    pthread_join(firstthread, NULL);
    pthread_join(secondthread, NULL);
   }
    clock_gettime(CLOCK_MONOTONIC, &finish);
    time_difference(&start, &finish, &time_elapsed);
    printf("Time elapsed %lldns or %0.9lfs\n", time_elapsed,
                                         (time_elapsed/1.0e9));
  return 0;
}


