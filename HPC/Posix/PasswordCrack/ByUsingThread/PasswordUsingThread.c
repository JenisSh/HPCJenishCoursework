#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <pthread.h>
#include <time.h>



int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$H8s0k9/1RQ783G9gF69Xkn.MI.Dq5Ox0va/dFlkknNjO7trgekVOjTv1BKCb.nm3vqxmtO2mOplhmFkwZXecz0",
  "$6$KB$VDUCASt5S88l82JzexhKDQLeUJ5zfxr16VhlVwNOs0YLiLYDciLDmN3QYAE80UIzfryYmpR.NFmbZvAGNoaHW.",
  "$6$KB$LIQ21WOW2T678MQ//wddYygf4uuWaMWVM8vG9Pj9O.7sDQ1GVgmw8KqqNfjjU6BtBgJvE5nXbborTU/uwrnVz1",
  "$6$KB$cU/6LrcqQGvsvRGllyfGDU1Wuvd1roXp.IEr3UYKQjBbT1sdP1PZPrZKrTGfFuRqD97EsgDalOwwn3OedIIjn0"
};




void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void Jenish(char *salt_and_encrypted){
  int x, y, z;     
  char salt[7];    
  char plain[8];   
  char *enc;       
  int count = 0;   

  substr(salt, salt_and_encrypted, 0, 6);


  for(x='A'; x<='M'; x++){
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



void Jenish2(char *salt_and_encrypted){
  int x, y, z;     
  char salt[7];    
  char plain[8];   
  char *enc;       
  int count = 0;   

  substr(salt, salt_and_encrypted, 0, 6);


  for(x='N'; x<='Z'; x++){
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


int main(){
int j;
  
  pthread_t th_read1, th_read2;

 struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);

  for(j=0;j<n_passwords;j<j++) {
    
  pthread_create(&th_read1, NULL,(void *)Jenish,encrypted_passwords[j]);
  pthread_create(&th_read2, NULL,(void *)Jenish2,encrypted_passwords[j]);
  
  pthread_join(th_read1, NULL);
  pthread_join(th_read2, NULL);
  }

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9)); 
  
  return 0;
}
