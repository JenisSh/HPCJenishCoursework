

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <crypt.h>
#include <mpi.h>

/

int n_passwords = 4;
pthread_t t1, t2;
char *encrypted_passwords[] = {
  "$6$KB$sl22ZaAfqOFudnKP6DKkTZOyZe1EaCbquYEzI2dgAE2/ngaDDWrP2t4qinJYOyABjxMddoPksNymjZz77xW0p/",
  "$6$KB$e.vPYwXC7GsQiPK1l1Gg47wPMYMdAWQ4xv1rEjel4.nyQkmneaFPsX9d3TdCrb.TzM9p7IBcYsQoFlA//dXif0",
  "$6$KB$u7qkLJwzC4hWyKZ6IHJNUII2fputzL1AWCnLho9ocWA//3WGdLa/yM/dSs/vskBL0.JPi2m7MUQK5tv8BbSx21",
  "$6$KB$DBLVZDgnpvKpeKWAm0JsktYclPexSHAqJefT1OKYQIGnGjfZB6Hx0zYa6KkvzGlarBnribA0PDqebfI/D8gmi/"
};

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}
  
void Jenish(char *salt_and_encrypted){
  int x, y, z;       char salt[7];    

  char plain[7];   
  char *enc;       
  int count = 0;   

  substr(salt, salt_and_encrypted, 0, 6);
  
  for(x='A'; x<='M'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=9999; z++){
	printf("Instance number 1:");
	sprintf(plain, "%c%c%04d",x, y, z);
	enc = (char *) crypt(plain, salt);
	count++;
	if(strcmp(salt_and_encrypted, enc) == 0){
	  printf("#%-8d%s %s\n", count, plain, enc);
	} else {
	 
	}
      }
    }
  }
  printf("%d solutions explored\n", count);
}
void Jenish2(char *salt_and_encrypted){
  int x, y, z;     
  char salt[7];    

  char plain[7];   
  char *enc;       
  int count = 0;   

  substr(salt, salt_and_encrypted, 0, 6);
  
  for(x='N'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=9999; z++){
	printf("Instance number 2:");
	sprintf(plain, "%c%c%04d",x, y, z);
	enc = (char *) crypt(plain, salt);
	count++;
	if(strcmp(salt_and_encrypted, enc) == 0){
	  printf("#%-8d%s %s\n", count, plain, enc);
	} else {
	 
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

int main(int argc, char** argv) {
 struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);

 
  int size, rank;
  int j;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(size != 3) {
    if(rank == 0) {
      printf("This program needs to run on exactly 3 processes\n");
    }
  } else {
    if(rank ==0){

      int x;
    
      MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      MPI_Send(&x, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);


 
    } else if(rank==1){
      int number;
      MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, 
                         MPI_STATUS_IGNORE);
        for(j=0;j<n_passwords;j<j++) {
          Jenish(encrypted_passwords[j]);
        }
      }
      else{
      int number;
      MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, 
                         MPI_STATUS_IGNORE);
        for(j=0;j<n_passwords;j<j++) {
          Jenish2(encrypted_passwords[j]);
        }
      }
    }
    MPI_Finalize(); 
 clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9)); 

  return 0;
}
