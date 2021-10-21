#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>



int main(int argc, char **argv) {
        struct servent *serv;
		  char servicio[20];
		  int puerto;


        serv = getservbyname("telnet", "tcp");
        if (serv == NULL) {
                fprintf(stderr, "Problema con la localizacińo del servicio\n");
                return 0;
        }
		  
		  printf("%s %d %s \n", serv->s_name, ntohs(serv->s_port), serv->s_proto);
		  
        
				
       return 0;
}

