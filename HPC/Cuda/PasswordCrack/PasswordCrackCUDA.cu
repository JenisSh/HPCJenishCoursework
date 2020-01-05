#include <time.h>
#include <stdio.h>
#include <cuda_runtime_api.h>

__device__ int is_a_match(char *attempt) {
  char password1[] = "AB1111";
  char password2[] = "AB9999";
  char password3[] = "AB6666";
  char password4[] = "AB1966";

  char *j = attempt;
  char *e = attempt;
  char *n = attempt;
  char *i = attempt;
  char *pass1 = password1;
  char *pass2 = password2;
  char *pass3 = password3;
  char *pass4 = password4;

  while(*j == *pass1) {
   if(*j == '\0')
    {
    printf("Found password: %s\n",password1);
      break;
    }

    j++;
    pass1++;
  }
    
  while(*e == *pass2) {
   if(*e == '\0')
    {
    printf("Found password: %s\n",password2);
      break;
}

    e++;
    pass2++;
  }

  while(*n == *pass3) {
   if(*n == '\0')
    {
    printf("Found password: %s\n",password3);
      break;
    }

    n++;
    pass3++;
  }

  while(*i == *pass4) {
   if(*i == '\0')
    {
    printf("Found password: %s\n",password4);
      return 1;
    }

    i++;
    pass4++;
  }
  return 0;

}

__global__ void  kernel() {
char a,b,c,d;
 
  char password[7];
  password[6] = '\0';

int x = blockIdx.x+65;
int y = threadIdx.x+65;
char firstValue = x;
char secondValue = y;
    
password[0] = firstValue;
password[1] = secondValue;
    for(a='0'; a<='9'; a++){
      for(b='0'; b<='9'; b++){
        for(c='0';c<='9';c++){
          for(d='0';d<='9';d++){
            password[2] = a;
            password[3] = b;
            password[4]= c;
            password[5]=d;
          if(is_a_match(password)) {
        //printf("Success");
          }
             else {
         //printf("tried: %s\n", password);          
            }
          }
        } 
      }
   }
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


int main() {

  struct  timespec start, finish;
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

kernel <<<26,26>>>();
  cudaThreadSynchronize();

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9));
  return 0;
}



