#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h>

void *thread(void *vargp) 
{ 
    int error = 0; 

   /*En cuanto se haga el pthread_detach() se eliminará el estado de esta hebra. 
     Hacer un join() de esta hebra puede  provocar estados impredecibles*/ 
   error = pthread_detach(pthread_self()); 
   /* Manejar el error */ 
   //...	 
   sleep(2);   

   printf("Hebra que ha llamado a pthread_detach()\n"); 
   pthread_exit(NULL); 
} 

int main() 
{ 
   pthread_t tid; 

   pthread_create(&tid, NULL, thread, NULL); 
   
   pthread_exit(NULL); 
}
