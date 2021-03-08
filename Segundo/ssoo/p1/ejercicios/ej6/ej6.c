//Programa que va mostrando cada x tiempo RING en pantalla, y cuando muestra 4 veces, finaliza

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int timb = 0;

void RING(){
    printf("RING \n");
    timb++;

    if( timb == 4 ) kill(getpid(), SIGKILL);

}



int main(){

    signal(SIGALRM, RING);//Cuando nos llegue una señal de tipo SIGALRM, ejecutamos la función RING
    
    alarm(5);//Se inicia una cuenta atrás de 5 segundos y cuando termina se envía a ESTE PROCESO una señal SIGALRM
    //Esa señal se captura arriba y se llama a la función RING 
    pause(); //Se espera a que llegue otra señal

    alarm(3);
    pause();

    while(1){
        alarm(1);
        pause();
    }
    return 0;
}
