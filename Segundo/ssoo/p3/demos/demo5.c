/*
Este programa muestra la implementación del problema lectores-escritores donde hay 2 lectores
y 2 escritores   (prioridad   a   los   lectores) y  un   buffer   con   un   solo   dato
que   se   va   incrementando.

Este programa no posee el adecuado control de errores a partir de la documentación
disponible en OpenGroup. Se deja para el lector la ampliación del ejercicio para mejorar
el control de errores.
*/

#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h>

#define DATOS_A_ESCRIBIR_LEER 5  //Simula las veces que cada lector y escritor intentaran leer y escribir
#define NUM_LECTORES 2 // Numero de lectores
#define NUM_ESCRITORES 2 //Numero de escritores

int dato = 0; /* Esta es la variable de la que no se puede leer y escribir a la vez */
int n_lectores = 0; /* numero de lectores */
sem_t sem_lec; /* semaforo para controlar el acceso n_lectores */
sem_t mutex; /* semaforo para controlar el acceso a dato */


void * Lector(void * arg) 
{
    //Complete el manejo de errores
    //....
    int i=0;
    for(i=0; i < DATOS_A_ESCRIBIR_LEER; i++ ) 
    {
        sem_wait(&sem_lec); 
        
        n_lectores = n_lectores + 1; 
        if (n_lectores == 1)
            sem_wait(&mutex); 
        
        sem_post(&sem_lec);
        
        
        printf("Lector %lu, valor leido = %d\n", (unsigned long)pthread_self(), dato); /* leer dato */
        
        
        sem_wait(&sem_lec); 
        
        n_lectores = n_lectores - 1; 
        if (n_lectores == 0) 
            sem_post(&mutex); 
        
        sem_post(&sem_lec);
        
    }  
  
    pthread_exit(NULL); 
}

void * Escritor(void * arg) 
{
    //Complete el manejo de errores
    //....
    int i=0;
    for(i=0; i < DATOS_A_ESCRIBIR_LEER; i++ ) 
    {
        sem_wait(&mutex); //No más de un escritor a la vez
        
        dato = dato + 1; /* modificar el recurso */
        printf("Escritor %lu, incrementando a valor = %d\n", (unsigned long) pthread_self(), dato); 
        
        sem_post(&mutex);
    }
    pthread_exit(NULL); 
}


int main(void) 
{
    //Complete el manejo de errores
    int i;
    pthread_t thlectores[NUM_LECTORES], thescritores[NUM_ESCRITORES];
    sem_init(&mutex, 0, 1);   //Para proteger el dato que se lee o se escribe
    sem_init(&sem_lec, 0, 1); //Para actualizar correctamente el numero de lectores que hay
    
    for(i=0; i < NUM_LECTORES; i++ ) 
        pthread_create(&thlectores[i], NULL, Lector, NULL); 
    for(i=0; i < NUM_ESCRITORES; i++ ) 
        pthread_create(&thescritores[i], NULL, Escritor, NULL); 
    
    for(i=0; i < NUM_LECTORES; i++ )
        pthread_join(thlectores[i], NULL);
    for(i=0; i < NUM_ESCRITORES; i++ ) 
        pthread_join(thescritores[i], NULL);
    
    /* eliminar todos los semaforos */ 
    sem_destroy(&mutex); 
    sem_destroy(&sem_lec);
}
