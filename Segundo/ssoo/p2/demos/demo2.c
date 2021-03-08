#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>	

void * hebra(void *x_void_ptr)
{
	//incrementar x hasta 100
	int *x_ptr = (int *)x_void_ptr; 
   
	printf("Soy la hebra hija, incrementando x, cuyo valor es %d\n", *x_ptr);

	while(*x_ptr < 100)
	{
	   *x_ptr=*x_ptr+1;
	} 

	printf("Soy la hebra hija, incremento de x finalizado\n");
 
	return NULL; //O pthread_exit(NULL)
}

int main()
{
	int x = 0, y = 0;

	//Declaración de una hebra, NO CREACION
	pthread_t hebra_incr;

	printf("Soy la hebra principal, valor de variable x: %d\n", x);
   	printf("Soy la hebra principal, valor de variable y: %d\n", y);
	
	//Creación de la hebra
	if(pthread_create(&hebra_incr, NULL, (void *) hebra, (void*) &x)) 
	{
	  fprintf(stderr, "Error creating thread\n");//Da error si devuelve algo distinto a 0
	  exit(EXIT_FAILURE); 
	}
   
   printf("Soy la hebra principal, incrementando y, cuyo valor es %d\n", y);
	//Incremetar y hasta 100
	while(y < 100)
	{
	   y=y+1;
	}

	printf("Soy la hebra principal, incremento de y finalizado\n");

	//Espera de la hebra
	if(pthread_join(hebra_incr, NULL)) 
	{
	  fprintf(stderr, "Error joining thread\n");
	  exit(EXIT_FAILURE);  
	}

	printf("Soy la hebra principal, valor de x: %d\n",x);
	printf("Soy la hebra principal, valor de y: %d\n",y);
	exit(EXIT_SUCCESS);



}


