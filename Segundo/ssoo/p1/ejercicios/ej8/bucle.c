#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>



void printid(){
  printf("Mi id es: %d\n", getpid());
}

int main(){
  signal(SIGUSR1, printid);
  printf("Mi id es: %d\n", getpid());
  
  while (1){
    pause();
  }
  
  return EXIT_SUCCESS;
}