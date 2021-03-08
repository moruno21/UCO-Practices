//Programa que envía al hijo una señal cada segundo (hasta 5 señales)

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

void tratarSennal(){
  printf("Mensaje para mi papá \n");
}


int main(){
  
  int status;
  pid_t id;
  id = fork();

  switch(id){
    
    case -1:
      printf("Error en la creación del hijo \n");
    exit(EXIT_FAILURE);


    case 0:
      signal(SIGUSR1, tratarSennal); //Cuando reciba una señal de tipo SIGUSR1, ejecutara tratarSennal
      for(int i=0; i<5; i++){
        pause(); //It shall suspend the calling thread until delivery of a signal whose action is either to execute a signal-catching function or to terminate the process.
      }
      sleep(1);
    exit(EXIT_SUCCESS);

    default:
      printf("Esperando a que mi hijo acabe \n");
      for (int i = 0; i<5; i++){
          sleep(1);
          kill(id, SIGUSR1); //En id se ha guardado el pid del hijo (así funciona el fork)
          // Cuando llamamos a kill, manda a id la señal SIGUSR1
      }

      sleep(1);//Si quitamos este sleep, matamos al proceso hijo antes de que le de tiempo a imprimir el mensaje numero 5
      kill(id, SIGKILL); //Mandamos a id (proceso hijo) la señal SIGKILL para que la casque
      sleep(10);//Si ponemos este sleep, el proceso hijo se queda en modo zombie esperando a ser recogido por el padre
      wait(&status);
      printf("Hijo finalizado con código de salida %d \n", WEXITSTATUS(status));
  }

return 0;
}