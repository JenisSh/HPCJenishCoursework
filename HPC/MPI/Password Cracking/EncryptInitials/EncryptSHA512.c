#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <mpi.h>



#define SALT "$6$KB$"

int main(int argc, char *argv[]){
  
  printf("%s\n", crypt(argv[1], SALT));

  return 0;
}
